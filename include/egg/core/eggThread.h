#pragma once

#include <sdk/OSThread.h>

#include <egg/core/eggHeap.h>

namespace EGG {

class Thread {
public:
    Heap *getNewHeap() const {
        return mNewHeap;
    }

    static Thread *findThread(OSThread *thread);

private:
    u8 _00[0x3c - 0x00];
    Heap *mNewHeap;
};

} // namespace EGG
