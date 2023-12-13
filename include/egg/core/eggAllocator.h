#pragma once

#include <egg/core/eggHeap.h>

#include <sdk/mem/allocator.h>

namespace EGG {

class Allocator : public MEMAllocator {
public:
    Allocator(Heap *heap, s32 align);
    virtual ~Allocator();
    virtual void *alloc(size_t size);
    virtual void free(void *block);

private:
    Heap *mHeap;
    s32 mAlign;
};

} // namespace EGG
