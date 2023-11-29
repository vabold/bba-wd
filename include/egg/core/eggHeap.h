#pragma once

#include <egg/core/eggDisposer.h>

namespace EGG {

class Heap : Disposer {
public:
    virtual ~Heap();
    virtual void vf_0c();
    virtual void vf_10();
    virtual void vf_14();
    virtual void vf_18();
    virtual void destroy();

    void becomeCurrentHeap();

    bool tstDisableAllocation() {
        return hasFlag(0);
    }

    void enableAllocation() {
        clearFlag(0);
    }

    void disableAllocation() {
        setFlag(0);
    }

    void appendDisposer(Disposer *disposer) {
        nw4r::ut::List_Append(&mChildren, disposer);
    }

    void removeDisposer(Disposer *disposer) {
        nw4r::ut::List_Remove(&mChildren, disposer);
    }

    static Heap *findContainHeap(void *memBlock);

private:
    // HACK: Avoid defining TBitFlag for now
    bool hasFlag(u8 idx) volatile {
        return mFlags & 1 << idx;
    }

    // HACK: Avoid defining TBitFlag for now
    void setFlag(u8 idx) volatile {
        mFlags |= (1 << idx);
    }

    // HACK: Avoid defining TBitFlag for now
    void clearFlag(u8 idx) volatile {
        mFlags &= ~(1 << idx);
    }

    u8 _10[0x1c - 0x10];
    u16 mFlags;
    u8 _1e[0x28 - 0x1e];
    nw4r::ut::List mChildren;
};

} // namespace EGG
