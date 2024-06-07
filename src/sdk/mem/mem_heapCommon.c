#include <sdk/mem/heapCommon.h>

static MEMList sRootList;
static OSMutex sRootMutex;
static BOOL sRootListInitialized;

static inline uintptr_t GetUIntPtr(const void *ptr) {
    return (uintptr_t)ptr;
}

static inline void SetOptForHeap(MEMiHeapHead *heap, u16 opt) {
    heap->attribute.fields.optFlag = opt;
}

static MEMiHeapHead *FindContainHeap_(MEMList *list, const void *block) {
    MEMiHeapHead *heap = NULL;
    MEMiHeapHead *search;

    while (heap = (MEMiHeapHead *)(MEMGetNextListObject(list, heap))) {
        if (GetUIntPtr(heap->heapStart) > GetUIntPtr(block) ||
                GetUIntPtr(block) >= GetUIntPtr(heap->heapEnd)) {
            continue;
        }

        search = FindContainHeap_(&heap->childList, block);
        if (search != NULL) {
            return search;
        }
        return heap;
    }

    return NULL;
}

static inline MEMList *FindListContainHeap_(MEMiHeapHead *heap) {
    MEMList *list = &sRootList;
    MEMiHeapHead *containHeap = FindContainHeap_(&sRootList, heap);
    if (containHeap) {
        list = &containHeap->childList;
    }

    return list;
}

void MEMiInitHeapHead(MEMiHeapHead *heap, u32 signature, void *heapStart, void *heapEnd, u16 opt) {
    heap->signature = signature;
    heap->heapStart = heapStart;
    heap->heapEnd = heapEnd;
    heap->attribute.val = 0;
    SetOptForHeap(heap, opt);

    MEMInitList(&heap->childList, 4);
    if (!sRootListInitialized) {
        MEMInitList(&sRootList, 4);
        OSInitMutex(&sRootMutex);
        sRootListInitialized = TRUE;
    }

    OSInitMutex(&heap->mutex);
    OSLockMutex(&sRootMutex);
    MEMAppendListObject(FindListContainHeap_(heap), heap);
    OSUnlockMutex(&sRootMutex);
}

void MEMiFinalizeHeap(MEMiHeapHead *heap) {
    OSLockMutex(&sRootMutex);
    MEMRemoveListObject(FindListContainHeap_(heap), heap);
    OSUnlockMutex(&sRootMutex);
    heap->signature = 0;
}

MEMiHeapHead *MEMFindContainHeap(const void *block) {
    return FindContainHeap_(&sRootList, block);
}
