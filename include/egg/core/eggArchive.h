#pragma once

#include <egg/core/eggDisposer.h>

#include <sdk/arc.h>

namespace EGG {

class Archive : Disposer {
public:
    struct FileInfo {
        u32 mStartOffset;
        u32 mLength;
    };

    virtual ~Archive();

    bool initHandle(void *arcBinary);
    void unmount();
    void *getFile(const char *name, FileInfo *pFileInfo);

    static Archive *findArchive(void *arcBinary);
    static Archive *mount(void *arcBinary, Heap *heap);

    static void appendList(Archive *archive);
    static void removeList(Archive *archive);

private:
    Archive();

    s32 mRefCount;
    ARCHandle mHandle;
    nw4r::ut::Link mLink;

    static nw4r::ut::List sArchiveList;
    static bool sIsArchiveListInitialized;
};

} // namespace EGG
