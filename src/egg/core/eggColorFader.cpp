#include <egg/core/eggColorFader.h>

#include <sdk/gx/GXAttr.h>
#include <sdk/gx/GXBump.h>
#include <sdk/gx/GXGeometry.h>
#include <sdk/gx/GXLight.h>
#include <sdk/gx/GXPixel.h>
#include <sdk/gx/GXTev.h>
#include <sdk/gx/GXTransform.h>
#include <sdk/gx/GXVert.h>

namespace EGG {

ColorFader::ColorFader(f32 left, f32 top, f32 width, f32 height, nw4r::ut::Color color,
        EStatus status)
    : mFrame(20), mFlags(0), mFrameTimer(0), mColor(),
      mRect(left, top, left + width, top + height) {
    setColor(color);
    setStatus(status);
    mFlags |= 2;
}

void ColorFader::setFrame(u16 frame) {
    mFrame = frame;
}

void ColorFader::setColor(nw4r::ut::Color color) {
    mColor.r = color.r;
    mColor.g = color.g;
    mColor.b = color.b;
}

void ColorFader::setStatus(EStatus status) {
    if (status == FADER_STATUS_OPAQUE) {
        mStatus = FADER_STATUS_OPAQUE;
        mColor.a = 255;
    } else if (status == FADER_STATUS_HIDDEN) {
        mStatus = FADER_STATUS_HIDDEN;
        mColor.a = 0;
    }
}

bool ColorFader::fadeIn() {
    bool success = mStatus == FADER_STATUS_OPAQUE;
    if (success) {
        mStatus = FADER_STATUS_FADE_IN;
        mFrameTimer = 0;
    }

    return success;
}

bool ColorFader::fadeOut() {
    bool success = mStatus == FADER_STATUS_HIDDEN;
    if (success) {
        mStatus = FADER_STATUS_FADE_OUT;
        mFrameTimer = 0;
    }

    return success;
}

bool ColorFader::calc() {
    bool finished = false;

    if (mStatus == FADER_STATUS_HIDDEN) {
        mColor.a = 0;
    } else if (mStatus == FADER_STATUS_OPAQUE) {
        mColor.a = 255;
    } else if (mStatus == FADER_STATUS_FADE_IN) {
        u16 timer = mFrameTimer;
        if (mFrameTimer++ > mFrame) {
            mStatus = FADER_STATUS_HIDDEN;
            finished = mFlags & 1;
            timer = mFrame;
        }
        mColor.a = 255 - (timer * 255) / mFrame;
    } else if (mStatus == FADER_STATUS_FADE_OUT) {
        u16 timer = mFrameTimer++;
        if (timer > mFrame) {
            if (timer > mFrame + 1) {
                mStatus = FADER_STATUS_OPAQUE;
                finished = mFlags & 2;
            }
            timer = mFrame;
        }
        mColor.a = (timer * 255) / mFrame;
    }

    return finished;
}

void ColorFader::draw() {
    if (mColor.a == 0) {
        return;
    }

    Mtx44 projection;
    C_MTXOrtho(projection, mRect.top, mRect.bottom, mRect.left, mRect.right, 0.0f, 1.0f);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetViewport(mRect.left, mRect.top, mRect.GetWidth(), mRect.GetHeight(), 0.0f, 1.0f);
    GXSetScissor(mRect.left, mRect.top, mRect.GetWidth(), mRect.GetHeight());

    Mtx mtx;
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanMatColor(GX_COLOR0A0, mColor);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE,
            GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    __GXSetIndirectMask(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

    if (mColor.a == 255) {
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    }

    GXSetColorUpdate(GX_ENABLE);
    GXSetAlphaUpdate(GX_ENABLE);
    GXSetZMode(GX_DISABLE, GX_NEVER, GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(mRect.left, mRect.top, 0.0f);
    GXPosition3f32(mRect.right, mRect.top, 0.0f);
    GXPosition3f32(mRect.right, mRect.bottom, 0.0f);
    GXPosition3f32(mRect.left, mRect.bottom, 0.0f);

    GXEnd();
}

} // namespace EGG
