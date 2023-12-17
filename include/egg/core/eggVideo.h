#pragma once

#include <sdk/gx/GXFrameBuf.h>

namespace EGG {

class Video {
public:
    bool isBlack() {
        return !(mFlag & 1);
    }

    u16 getFbWidth() {
        return mObj->fbWidth;
    }

    u16 getEfbHeight() {
        return mObj->efbHeight;
    }

private:
    _GXRenderModeObj *mObj;
    u8 mFlag;
};

} // namespace EGG
