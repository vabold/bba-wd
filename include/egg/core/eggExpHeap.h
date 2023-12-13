#pragma once

#include <egg/core/eggHeap.h>

namespace EGG {

class ExpHeap : public Heap {
public:
    virtual ~ExpHeap();
    virtual eHeapKind getHeapKind() const {
        return HEAP_KIND_EXPANDED;
    }
    virtual void initAllocator(Allocator *allocator, s32 align);
    virtual void *alloc(size_t size, s32 align);
    virtual void free(void *block);
    virtual void destroy();
    virtual u32 resizeForMBlock(void *block, u32 size);
    virtual u32 getAllocatableSize(s32 align);
    virtual u32 adjust();

    u32 getTotalFreeSize();
    u16 setGroupID(u16 groupID);
    void freeAll();
    bool checkForEachMemblock();

    static ExpHeap *create(void *startAddress, size_t size, u16 flag);
    static ExpHeap *create(u32 size, Heap *heap, u16 attr);

private:
    ExpHeap(MEMiHeapHead *handle);
};

} // namespace EGG
