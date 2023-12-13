#ifndef MEM_EXPHEAP_H
#define MEM_EXPHEAP_H

#include <sdk/mem/heapCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

MEMiHeapHead *MEMCreateExpHeapEx(void *startAddress, size_t size, u16 flag);
void MEMDestroyExpHeap(MEMiHeapHead *handle);
void *MEMAllocFromExpHeapEx(MEMiHeapHead *handle, u32 size, s32 align);
u32 MEMResizeForMBlockExpHeap(MEMiHeapHead *handle, void *block, u32 size);
void MEMFreeToExpHeap(MEMiHeapHead *handle, void *block);
u32 MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead *handle);
u32 MEMGetAllocatableSizeForExpHeapEx(MEMiHeapHead *handle, s32 align);
u16 MEMSetGroupIDForExpHeap(MEMiHeapHead *handle, u16 groupID);
void MEMVisitAllocatedForExpHeap(MEMiHeapHead *handle, void *callback, u32 param);
u32 MEMAdjustExpHeap(MEMiHeapHead *handle);

#ifdef __cplusplus
}
#endif

#endif
