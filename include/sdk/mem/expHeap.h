#ifndef MEM_EXPHEAP_H
#define MEM_EXPHEAP_H

#include <sdk/mem/heapCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMiExpBlockHead MEMiExpBlockHead;

typedef struct MEMiExpBlockLink {
    MEMiExpBlockHead *prev;
    MEMiExpBlockHead *next;
} MEMiExpBlockLink;

typedef struct MEMiExpBlockList {
    MEMiExpBlockHead *head;
    MEMiExpBlockHead *tail;
} MEMiExpBlockList;

typedef struct MEMiExpBlockHead {
    u16 signature;
    union {
        u16 val;
        struct {
            u16 direction : 1;
            u16 alignment : 7;
            u16 groupId : 8;
        } fields;
    } attribute;
    u32 size;
    MEMiExpBlockLink link;
} MEMiExpBlockHead;

typedef struct MEMiExpHeapExt {
    MEMiExpBlockList freeBlocks;
    MEMiExpBlockList usedBlocks;
    u16 groupId;
    union {
        u16 val;
        struct {
            u16 _reserved : 15;
            u16 allocMode : 1;
        } fields;
    } attribute;
} MEMiExpHeapExt;

typedef struct MEMiExpHeapHead {
    MEMiHeapHead base;
    MEMiExpHeapExt ext;
} MEMiExpHeapHead;

MEMiHeapHead *MEMCreateExpHeapEx(void *startAddress, size_t size, u16 flag);
void *MEMDestroyExpHeap(MEMiHeapHead *handle);
void *MEMAllocFromExpHeapEx(MEMiHeapHead *handle, u32 size, s32 align);
u32 MEMResizeForMBlockExpHeap(MEMiHeapHead *handle, void *block, u32 size);
void MEMFreeToExpHeap(MEMiHeapHead *handle, void *block);
u32 MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead *handle);
u32 MEMGetAllocatableSizeForExpHeapEx(MEMiHeapHead *handle, s32 align);
u16 MEMSetGroupIDForExpHeap(MEMiHeapHead *handle, u16 groupID);
void MEMVisitAllocatedForExpHeap(MEMiHeapHead *handle, void (*visitor)(void *, MEMiHeapHead *, u32), u32 param);
u32 MEMAdjustExpHeap(MEMiHeapHead *handle);

#ifdef __cplusplus
}
#endif

#endif
