#pragma once

#include <egg/core/eggHeap.h>

namespace EGG {

class Video;
class Display;

class BaseSystem {
public:
    virtual Video *getVideo();
    virtual void vf_0c();
    virtual Display *getDisplay();

    u8 _04[0x18 - 0x04];
    Heap *mRootHeapMem1;
    Heap *mRootHeapMem2;

    static BaseSystem *sSystem;
};

} // namespace EGG
