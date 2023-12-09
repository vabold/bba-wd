#include <egg/core/eggAllocator.h>

namespace EGG {

Allocator::Allocator(Heap *heap, s32 align) : mHeap(heap), mAlign(align) {
    heap->initAllocator(this, align);
}

Allocator::~Allocator() {}

void *Allocator::alloc(size_t size) {
    return Heap::alloc(size, mAlign, mHeap);
}

void Allocator::free(void *block) {
    Heap::free(block, mHeap);
}

} // namespace EGG
