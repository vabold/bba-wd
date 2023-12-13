#include <egg/core/eggExpHeap.h>

#include <egg/core/eggAllocator.h>

#include <sdk/OSError.h>
#include <sdk/mem/expHeap.h>

namespace EGG {

bool _check_for_each = true;

ExpHeap::ExpHeap(MEMiHeapHead *handle) : Heap(handle) {}

ExpHeap::~ExpHeap() {
    dispose();
    MEMDestroyExpHeap(mHeapHandle);
}

ExpHeap *ExpHeap::create(void *startAddress, size_t size, u16 flag) {
    ExpHeap *heap = NULL;
    void *orig = startAddress;

    void *endAddress = (void *)ROUND_DOWN(Heap::addOffset(startAddress, size), 4);
    startAddress = (void *)ROUND_UP(startAddress, 4);

    if (startAddress > endAddress || PTR_SIZE(startAddress, endAddress) < 0x3c) {
        return NULL;
    }

    MEMiHeapHead *handle = MEMCreateExpHeapEx(Heap::addOffset(startAddress, 0x38),
            PTR_SIZE(startAddress, endAddress) - 0x38, flag);
    if (handle) {
        heap = new (startAddress) ExpHeap(handle);
        heap->registerHeapBuffer(orig);
    }

    return heap;
}

ExpHeap *ExpHeap::create(u32 size, Heap *pHeap, u16 attr) {
    ExpHeap *heap = NULL;
    if (!pHeap) {
        pHeap = Heap::sCurrentHeap;
    }

    if (size == -1) {
        size = pHeap->getAllocatableSize(4);
    }

    void *block = pHeap->alloc(size, 4);
    if (block) {
        heap = create(block, size, attr);
        if (heap) {
            heap->mParentHeap = pHeap;
        } else {
            pHeap->free(block);
        }
    }

    return heap;
}

void ExpHeap::destroy() {
    Heap *parent = findParentHeap();
    this->~ExpHeap();
    if (parent) {
        parent->free(this);
    }
}

void *ExpHeap::alloc(size_t size, s32 align) {
    if (tstDisableAllocation()) {
        OSPanic("eggExpHeap.cpp", 168, "DAME DAME\n");
    }

    return MEMAllocFromExpHeapEx(mHeapHandle, size, align);
}

void ExpHeap::free(void *block) {
    MEMFreeToExpHeap(mHeapHandle, block);
}

u32 ExpHeap::resizeForMBlock(void *block, u32 size) {
    return MEMResizeForMBlockExpHeap(mHeapHandle, block, size);
}

u32 ExpHeap::getTotalFreeSize() {
    return MEMGetTotalFreeSizeForExpHeap(mHeapHandle);
}

u32 ExpHeap::getAllocatableSize(s32 align) {
    return MEMGetAllocatableSizeForExpHeapEx(mHeapHandle, align);
}

u16 ExpHeap::setGroupID(u16 groupID) {
    return MEMSetGroupIDForExpHeap(mHeapHandle, groupID);
}

u32 ExpHeap::adjust() {
    u32 size = MEMAdjustExpHeap(mHeapHandle) + 0x38;
    if (size != 0) {
        findParentHeap()->resizeForMBlock(mBlock, size);
    }

    return size;
}

void ExpHeap::initAllocator(Allocator *allocator, s32 align) {
    MEMInitAllocatorForExpHeap(allocator, mHeapHandle, align);
}

namespace {

void free_all_visitor(void *block, MEMiHeapHead *handle, u32) {
    MEMFreeToExpHeap(handle, block);
}

}

void ExpHeap::freeAll() {
    dispose();
    MEMVisitAllocatedForExpHeap(mHeapHandle, free_all_visitor, 0);
}

void check_visitor(void *, MEMiHeapHead *, u32) {}

bool ExpHeap::checkForEachMemblock() {
    _check_for_each = true;
    MEMVisitAllocatedForExpHeap(mHeapHandle, check_visitor, 0);
    return _check_for_each;
}

} // namespace EGG
