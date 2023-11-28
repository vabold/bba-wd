#pragma once

#include <egg/core/eggSystem.h>
#include <egg/core/eggVideo.h>

namespace EGG {

class Display {
public:
    void setBlack(bool) {
        if (BaseSystem::sSystem->getVideo()->isBlack()) {
            return;
        }

        if (!hasFlag(0)) {
            setFlag(0);
        }
    }

private:
    // HACK: Avoid defining TBitFlag for now
    bool hasFlag(u8 idx) volatile {
        return mFlag & 1 << idx;
    }

    // HACK: Avoid defining TBitFlag for now
    void setFlag(u8 idx) volatile {
        mFlag |= (1 << idx);
    }

    u8 _00[0x09 - 0x00];
    u8 mFlag;
};

} // namespace EGG
