#pragma once

#include <egg/core/eggHeap.h>

namespace EGG {

class ExpHeap : public Heap {
public:
    static ExpHeap *create(u32 size, Heap *heap, u16 attr);
};

} // namespace EGG
