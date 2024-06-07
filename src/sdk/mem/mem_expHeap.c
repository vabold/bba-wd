#include <sdk/mem/expHeap.h>

typedef struct Region {
    void *start;
    void *end;
} Region;

static inline uintptr_t GetUIntPtr(void *ptr) {
    return (uintptr_t)ptr;
}

static inline void *AddU32ToPtr(void *ptr, u32 op) {
    return (void *)(GetUIntPtr(ptr) + op);
}

static inline void *SubU32ToPtr(void *ptr, u32 op) {
    return (void *)(GetUIntPtr(ptr) - op);
}

static inline u32 GetOffsetFromPtr(void *p0, void *p1) {
    return GetUIntPtr(p1) - GetUIntPtr(p0);
}

static inline s32 ComparePtr(void *p0, void *p1) {
    return (uintptr_t)p0 - (uintptr_t)p1;
}

static inline u16 GetOptForHeap(MEMiHeapHead *heap) {
    return heap->attribute.fields.optFlag;
}

static inline void FillAllocMemory(MEMiHeapHead *heap, void *address, u32 size) {
    if (GetOptForHeap(heap) & 1) {
        memset(address, 0, size);
    }
}

static inline void LockHeap(MEMiHeapHead *heap) {
    if (GetOptForHeap(heap) & 4) {
        OSLockMutex(&heap->mutex);
    }
}

static inline void UnlockHeap(MEMiHeapHead *heap) {
    if (GetOptForHeap(heap) & 4) {
        OSUnlockMutex(&heap->mutex);
    }
}

static inline MEMiExpHeapExt *GetExpHeapHeadPtrFromHeapHead_(MEMiHeapHead *heap) {
    return AddU32ToPtr(heap, sizeof(MEMiHeapHead));
}

static inline MEMiExpHeapExt *GetExpHeapHeadPtrFromHandle_(MEMiHeapHead *heap) {
    return GetExpHeapHeadPtrFromHeapHead_(heap);
}

static inline MEMiHeapHead *GetHeapHeadPtrFromExpHeapHead_(MEMiExpHeapExt *ext) {
    return SubU32ToPtr(ext, sizeof(MEMiHeapHead));
}

static inline u16 GetAllocMode_(MEMiExpHeapExt *ext) {
    return ext->attribute.fields.allocMode;
}

static inline void SetAllocMode_(MEMiExpHeapExt *ext, u16 mode) {
    ext->attribute.fields.allocMode = mode;
}

static inline u16 GetAlignmentForMBlock_(MEMiExpBlockHead *block) {
    return block->attribute.fields.alignment;
}

static inline void SetAllocDirForMBlock_(MEMiExpBlockHead *block, u16 direction) {
    block->attribute.fields.direction = direction;
}

static inline void SetAlignmentForMBlock_(MEMiExpBlockHead *block, u16 alignment) {
    block->attribute.fields.alignment = alignment;
}

static inline void SetGroupIDForMBlock_(MEMiExpBlockHead *block, u16 groupId) {
    block->attribute.fields.groupId = groupId;
}

static inline void *GetMemPtrForMBlock_(MEMiExpBlockHead *block) {
    return AddU32ToPtr(block, sizeof(MEMiExpBlockHead));
}

static inline MEMiExpBlockHead *GetMBlockHeadPtr_(void *block) {
    return SubU32ToPtr(block, sizeof(MEMiExpBlockHead));
}

static inline void *GetMBlockEndAddr_(MEMiExpBlockHead *block) {
    return AddU32ToPtr(GetMemPtrForMBlock_(block), block->size);
}

static inline void GetRegionOfMBlock_(Region *region, MEMiExpBlockHead *block) {
    region->start = SubU32ToPtr(block, GetAlignmentForMBlock_(block));
    region->end = GetMBlockEndAddr_(block);
}

static inline MEMiExpBlockHead *RemoveMBlock_(MEMiExpBlockList *list, MEMiExpBlockHead *block) {
    MEMiExpBlockHead *prev = block->link.prev;
    MEMiExpBlockHead *next = block->link.next;

    if (prev) {
        prev->link.next = next;
    } else {
        list->head = next;
    }

    if (next) {
        next->link.prev = prev;
    } else {
        list->tail = prev;
    }

    return prev;
}

static inline MEMiExpBlockHead *InsertMBlock_(MEMiExpBlockList *list, MEMiExpBlockHead *block,
        MEMiExpBlockHead *prev) {
    MEMiExpBlockHead *next;

    block->link.prev = prev;
    if (prev) {
        next = prev->link.next;
        prev->link.next = block;
    } else {
        next = list->head;
        list->head = block;
    }

    block->link.next = next;
    if (next) {
        next->link.prev = block;
    } else {
        list->tail = block;
    }

    return block;
}

static inline MEMiExpBlockHead *AppendMBlock_(MEMiExpBlockList *list, MEMiExpBlockHead *block) {
    return InsertMBlock_(list, block, list->tail);
}

static inline MEMiExpBlockHead *InitMBlock_(Region *region, u16 signature) {
    MEMiExpBlockHead *block = region->start;

    block->signature = signature;
    block->attribute.val = 0;
    block->size = GetOffsetFromPtr(GetMemPtrForMBlock_(block), region->end);
    block->link.prev = NULL;
    block->link.next = NULL;

    return block;
}

static inline MEMiExpBlockHead *InitFreeMBlock_(Region *region) {
    return InitMBlock_(region, 'FR');
}

static inline MEMiHeapHead *InitExpHeap_(MEMiHeapHead *heap, void *end, u16 opt) {
    Region region;
    MEMiExpBlockHead *block;
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHeapHead_(heap);

    MEMiInitHeapHead(heap, 'EXPH', AddU32ToPtr(ext, 0x14), end, opt);
    ext->groupId = 0;
    ext->attribute.val = 0;
    SetAllocMode_(ext, 0);

    region.start = heap->heapStart;
    region.end = heap->heapEnd;
    block = InitFreeMBlock_(&region);

    ext->freeBlocks.head = block;
    ext->freeBlocks.tail = block;
    ext->usedBlocks.head = NULL;
    ext->usedBlocks.tail = NULL;

    return heap;
}

static void *AllocUsedBlockFromFreeBlock_(MEMiExpHeapExt *ext, MEMiExpBlockHead *block,
        void *address, u32 size, s32 direction) {
    Region region0;
    Region region1;
    MEMiExpBlockHead *prev;

    GetRegionOfMBlock_(&region0, block);
    region1.end = region0.end;
    region1.start = AddU32ToPtr(address, size);
    region0.end = SubU32ToPtr(address, sizeof(MEMiExpBlockHead));

    prev = RemoveMBlock_(&ext->freeBlocks, block);

    if (GetOffsetFromPtr(region0.start, region0.end) < 0x14) {
        region0.end = region0.start;
    } else {
        prev = InsertMBlock_(&ext->freeBlocks, InitFreeMBlock_(&region0), prev);
    }

    if (GetOffsetFromPtr(region1.start, region1.end) < 0x14) {
        region1.start = region1.end;
    } else {
        InsertMBlock_(&ext->freeBlocks, InitFreeMBlock_(&region1), prev);
    }

    FillAllocMemory(GetHeapHeadPtrFromExpHeapHead_(ext), region0.end,
            GetOffsetFromPtr(region0.end, region1.start));

    {
        Region region2;
        MEMiExpBlockHead *head;

        region2.start = SubU32ToPtr(address, sizeof(MEMiExpBlockHead));
        region2.end = region1.start;
        head = InitMBlock_(&region2, 'UD');

        SetAllocDirForMBlock_(head, direction);
        SetAlignmentForMBlock_(head, GetOffsetFromPtr(region0.end, head));
        SetGroupIDForMBlock_(head, ext->groupId);
        AppendMBlock_(&ext->usedBlocks, head);
    }

    return address;
}

static void *AllocFromHead_(MEMiHeapHead *heap, u32 size, s32 alignment) {
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHeapHead_(heap);
    BOOL fastAlloc = GetAllocMode_(ext) == 0;
    MEMiExpBlockHead *block = NULL;
    MEMiExpBlockHead *found = NULL;
    u32 blockSize = -1;
    void *bestAddress = NULL;

    for (block = ext->freeBlocks.head; block; block = block->link.next) {
        void *const memptr = GetMemPtrForMBlock_(block);
        void *const address = ROUND_UP_PTR(GetUIntPtr(memptr), alignment);
        u32 offset = GetOffsetFromPtr(memptr, address);
        if (block->size < size + offset) {
            continue;
        }

        if (blockSize <= block->size) {
            continue;
        }

        found = block;
        blockSize = block->size;
        bestAddress = address;

        if (fastAlloc || blockSize == size) {
            break;
        }
    }

    if (!found) {
        return NULL;
    }

    return AllocUsedBlockFromFreeBlock_(ext, found, bestAddress, size, 0);
}

static void *AllocFromTail_(MEMiHeapHead *heap, u32 size, s32 alignment) {
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHeapHead_(heap);
    BOOL fastAlloc = GetAllocMode_(ext) == 0;
    MEMiExpBlockHead *block = NULL;
    MEMiExpBlockHead *found = NULL;
    u32 blockSize = -1;
    void *bestAddress = NULL;

    for (block = ext->freeBlocks.tail; block; block = block->link.prev) {
        void *const start = GetMemPtrForMBlock_(block);
        void *const endAddr = AddU32ToPtr(start, block->size);
        void *const end = ROUND_DOWN_PTR(SubU32ToPtr(endAddr, size), alignment);
        if (ComparePtr(end, start) < 0) {
            continue;
        }

        if (blockSize <= block->size) {
            continue;
        }

        found = block;
        blockSize = block->size;
        bestAddress = end;

        if (fastAlloc || blockSize == size) {
            break;
        }
    }

    if (!found) {
        return NULL;
    }

    return AllocUsedBlockFromFreeBlock_(ext, found, bestAddress, size, 1);
}

static BOOL RecycleRegion_(MEMiExpHeapExt *ext, Region *initialRegion) {
    MEMiExpBlockHead *block = NULL;
    Region region = *initialRegion;
    MEMiExpBlockHead *search;
    for (search = ext->freeBlocks.head; search; search = search->link.next) {
        if (search < initialRegion->start) {
            block = search;
            continue;
        }

        if (search == initialRegion->end) {
            region.end = GetMBlockEndAddr_(search);
            RemoveMBlock_(&ext->freeBlocks, search);
        }
        break;
    }

    if (block && GetMBlockEndAddr_(block) == initialRegion->start) {
        region.start = block;
        block = RemoveMBlock_(&ext->freeBlocks, block);
    }

    if (GetOffsetFromPtr(region.start, region.end) < sizeof(MEMiExpBlockHead)) {
        return FALSE;
    }

    InsertMBlock_(&ext->freeBlocks, InitFreeMBlock_(&region), block);
    return TRUE;
}

MEMiHeapHead *MEMCreateExpHeapEx(void *startAddress, u32 size, u16 opt) {
    void *end = ROUND_DOWN_PTR(GetUIntPtr(AddU32ToPtr(startAddress, size)), 4);
    void *start = ROUND_UP_PTR(GetUIntPtr(startAddress), 4);

    if (GetUIntPtr(start) > GetUIntPtr(end) || GetOffsetFromPtr(start, end) < 0x64) {
        return NULL;
    }

    return InitExpHeap_(start, end, opt);
}

void *MEMDestroyExpHeap(MEMiHeapHead *heap) {
    MEMiFinalizeHeap(heap);
    return heap;
}

void *MEMAllocFromExpHeapEx(MEMiHeapHead *heap, u32 size, s32 alignment) {
    void *block;

    if (size == 0) {
        size = 1;
    }
    size = ROUND_UP(size, 4);

    LockHeap(heap);
    if (alignment >= 0) {
        block = AllocFromHead_(heap, size, alignment);
    } else {
        block = AllocFromTail_(heap, size, -alignment);
    }
    UnlockHeap(heap);
    return block;
}

u32 MEMResizeForMBlockExpHeap(MEMiHeapHead *heap, void *block, u32 size) {
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHandle_(heap);
    MEMiExpBlockHead *head = GetMBlockHeadPtr_(block);

    size = ROUND_UP(size, 4);
    if (size == head->size) {
        return size;
    }

    LockHeap(heap);

    if (size > head->size) {
        void *end = GetMBlockEndAddr_(head);
        MEMiExpBlockHead *search;
        for (search = ext->freeBlocks.head; search; search = search->link.next) {
            if (search == end) {
                break;
            }
        }

        if (!search || size > head->size + search->size + sizeof(MEMiExpBlockHead)) {
            return 0;
        } else {
            Region region;
            MEMiExpBlockHead *prev;
            void *start;

            GetRegionOfMBlock_(&region, search);
            prev = RemoveMBlock_(&ext->freeBlocks, search);
            start = region.start;
            region.start = AddU32ToPtr(block, size);

            if (GetOffsetFromPtr(region.start, region.end) < sizeof(MEMiExpBlockHead)) {
                region.start = region.end;
            }

            head->size = GetOffsetFromPtr(block, region.start);

            if (GetOffsetFromPtr(region.start, region.end) >= sizeof(MEMiExpBlockHead)) {
                InsertMBlock_(&ext->freeBlocks, InitFreeMBlock_(&region), prev);
            }

            FillAllocMemory(heap, start, GetOffsetFromPtr(start, region.start));
        }
    } else {
        Region region;
        u32 origSize = head->size;

        region.start = AddU32ToPtr(block, size);
        region.end = GetMBlockEndAddr_(head);

        head->size = size;

        if (!RecycleRegion_(ext, &region)) {
            head->size = origSize;
        }
    }

    UnlockHeap(heap);
    return head->size;
}

void MEMFreeToExpHeap(MEMiHeapHead *heap, void *block) {
    Region region;
    MEMiExpBlockHead *head;
    MEMiExpHeapExt *ext;

    if (!block) {
        return;
    }

    ext = GetExpHeapHeadPtrFromHandle_(heap);
    head = GetMBlockHeadPtr_(block);
    LockHeap(heap);
    GetRegionOfMBlock_(&region, head);
    RemoveMBlock_(&ext->usedBlocks, head);
    RecycleRegion_(ext, &region);
    UnlockHeap(heap);
}

u32 MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead *heap) {
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHandle_(heap);
    MEMiExpBlockHead *block;
    u32 size = 0;

    LockHeap(heap);
    for (block = ext->freeBlocks.head; block; block = block->link.next) {
        size += block->size;
    }
    UnlockHeap(heap);

    return size;
}

u32 MEMGetAllocatableSizeForExpHeapEx(MEMiHeapHead *heap, s32 alignment) {
    MEMiExpHeapExt *ext;
    MEMiExpBlockHead *block;
    u32 maxSize;
    u32 x;

    alignment = __abs(alignment);
    LockHeap(heap);

    ext = GetExpHeapHeadPtrFromHandle_(heap);
    maxSize = 0;
    x = -1;
    for (block = ext->freeBlocks.head; block; block = block->link.next) {
        void *address = ROUND_UP_PTR(GetUIntPtr(GetMemPtrForMBlock_(block)), alignment);

        if (GetUIntPtr(address) < GetUIntPtr(GetMBlockEndAddr_(block))) {
            u32 size = GetOffsetFromPtr(address, GetMBlockEndAddr_(block));
            u32 offset = GetOffsetFromPtr(GetMemPtrForMBlock_(block), address);

            if (maxSize < size || (maxSize == size && x > offset)) {
                maxSize = size;
                x = offset;
            }
        }
    }

    UnlockHeap(heap);
    return maxSize;
}

u16 MEMSetGroupIDForExpHeap(MEMiHeapHead *heap, u16 groupId) {
    u16 prev;
    BOOL interrupts = OSDisableInterrupts();
    MEMiExpHeapExt *ext = GetExpHeapHeadPtrFromHandle_(heap);

    prev = ext->groupId;
    ext->groupId = groupId;

    OSRestoreInterrupts(interrupts);
    return prev;
}

void MEMVisitAllocatedForExpHeap(MEMiHeapHead *heap, void (*visitor)(void *, MEMiHeapHead *, u32),
        u32 param) {
    MEMiExpBlockHead *block;

    LockHeap(heap);

    for (block = GetExpHeapHeadPtrFromHandle_(heap)->usedBlocks.head; block;) {
        MEMiExpBlockHead *next = block->link.next;
        (*visitor)(GetMemPtrForMBlock_(block), heap, param);
        block = next;
    }

    UnlockHeap(heap);
}

u32 MEMAdjustExpHeap(MEMiHeapHead *heap) {
    MEMiExpHeapExt *ext;
    MEMiExpBlockHead *block;
    u32 newSize;

    LockHeap(heap);

    ext = GetExpHeapHeadPtrFromHandle_(heap);
    block = ext->freeBlocks.tail;
    if (!block) {
        newSize = 0;
    } else if (AddU32ToPtr(GetMemPtrForMBlock_(block), block->size) != heap->heapEnd) {
        newSize = 0;
    } else {
        RemoveMBlock_(&ext->freeBlocks, block);
        heap->heapEnd = SubU32ToPtr(heap->heapEnd, block->size + sizeof(MEMiExpBlockHead));
        newSize = GetOffsetFromPtr(heap, heap->heapEnd);
    }

    UnlockHeap(heap);
    return newSize;
}
