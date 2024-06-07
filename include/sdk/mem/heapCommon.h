#ifndef MEM_HEAP_COMMON_H
#define MEM_HEAP_COMMON_H

#include <sdk/OSMutex.h>
#include <sdk/mem/list.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMiHeapHead {
    u32 signature;
    MEMLink link;
    MEMList childList;
    void *heapStart;
    void *heapEnd;
    OSMutex mutex;
    union {
        u32 val;
        struct {
            u32 _reserved : 24;
            u32 optFlag : 8;
        } fields;
    } attribute;
} MEMiHeapHead;

void MEMiInitHeapHead(MEMiHeapHead *heap, u32 signature, void *heapStart, void *heapEnd, u16 opt);
void MEMiFinalizeHeap(MEMiHeapHead *heap);
MEMiHeapHead *MEMFindContainHeap(const void *block);

inline void *MEMGetHeapEndAddress(MEMiHeapHead *heap) {
    return heap->heapEnd;
}

#ifdef __cplusplus
}
#endif

#endif
