#pragma once

#include <Common.h>

namespace EGG {

class Heap {
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

    u8 _04[0x1c - 0x04];
    u16 mFlags;
};

} // namespace EGG
