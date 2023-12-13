#ifndef MEM_HEAP_COMMON_H
#define MEM_HEAP_COMMON_H

#include <Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMiHeapHead {
    u8 _00[0x1c - 0x00];
    void *heapEnd;
} MEMiHeapHead;

MEMiHeapHead *MEMFindContainHeap(const void *block);

inline void *MEMGetHeapEndAddress(MEMiHeapHead *heap) {
    return heap->heapEnd;
}

#ifdef __cplusplus
}
#endif

#endif
