#include <egg/core/eggArchive.h>

#include <egg/core/eggHeap.h>

namespace EGG {

Archive::Archive() : mRefCount(1) {
    memset(&mHandle, 0, sizeof(ARCHandle));
    if (!sIsArchiveListInitialized) {
        nw4r::ut::List_Init(&sArchiveList, 0x30);
        sIsArchiveListInitialized = true;
    }
    appendList(this);
}

Archive::~Archive() {
    removeList(this);
}

bool Archive::initHandle(void *arcBinary) {
    return ARCInitHandle(arcBinary, &mHandle);
}

Archive *Archive::findArchive(void *arcBinary) {
    Archive *archive = NULL;
    if (sIsArchiveListInitialized) {
        Archive *node = NULL;
        while (node = reinterpret_cast<Archive *>(nw4r::ut::List_GetNext(&sArchiveList, node))) {
            if (node->mHandle.archiveStartAddr == arcBinary) {
                archive = node;
                break;
            }
        }
    }

    return archive;
}

void Archive::appendList(Archive *archive) {
    nw4r::ut::List_Append(&sArchiveList, archive);
}

void Archive::removeList(Archive *archive) {
    nw4r::ut::List_Remove(&sArchiveList, archive);
}

Archive *Archive::mount(void *arcBinary, Heap *heap) {
    Archive *archive = findArchive(arcBinary);
    if (!archive) {
        archive = new (heap, 4) Archive;
        if (!archive->initHandle(arcBinary)) {
            delete archive;
            archive = NULL;
        }
    } else {
        ++archive->mRefCount;
    }

    return archive;
}

void Archive::unmount() {
    if (mRefCount == 0) {
        return;
    }

    if (--mRefCount != 0) {
        return;
    }

    delete this;
}

void *Archive::getFile(const char *name, FileInfo *pFileInfo) {
    ARCFileInfo fileInfo;

    void *file = NULL;
    bool open = ARCOpen(&mHandle, name, &fileInfo);
    if (open) {
        file = ARCGetStartAddrInMem(&fileInfo);
        if (pFileInfo) {
            pFileInfo->mStartOffset = ARCGetStartOffset(&fileInfo);
            pFileInfo->mLength = ARCGetLength(&fileInfo);
        }
    }

    ARCClose(&fileInfo);
    return file;
}

nw4r::ut::List Archive::sArchiveList;
bool Archive::sIsArchiveListInitialized;

} // namespace EGG
