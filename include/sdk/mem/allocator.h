#ifndef MEM_ALLOCATOR_H
#define MEM_ALLOCATOR_H

#include <sdk/mem/heapCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u8 _00[0x10 - 0x00];
} MEMAllocator;

void MEMInitAllocatorForExpHeap(MEMAllocator *allocator, MEMiHeapHead *heap, s32 align);

#ifdef __cplusplus
}
#endif

#endif
