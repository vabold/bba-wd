#include <egg/gfx/eggViewport.h>

#include <egg/core/eggSystem.h>
#include <egg/core/eggVideo.h>
#include <sdk/gx/GXTransform.h>

namespace EGG {

#pragma exceptions on

Viewport::Viewport() : mScreenWidth(0.0f), mScreenHeight(0.0f), mAspectRatio(0.0f) {}

void Viewport::set(int left, int up, int right, int down) {
    mBox.mMin.x = left;
    mBox.mMin.y = up;
    mBox.mMax.x = right;
    mBox.mMax.y = down;

    calc();
}

#pragma exceptions off

void Viewport::setLUAndWH(f32 left, f32 up, f32 width, f32 height) {
    mBox.mMin.x = left;
    mBox.mMin.y = up;
    mBox.mMax.x = left + width;
    mBox.mMax.y = up + height;

    calc();
}

void Viewport::calc() {
    mScreenWidth = mBox.getSizeX();
    mScreenHeight = mBox.getSizeY();
    mAspectRatio = mScreenWidth / mScreenHeight;
}

void Viewport::setupGXViewport() {
    GXSetViewport(mBox.mMin.x, mBox.mMin.y, mScreenWidth, mScreenHeight, 0.0f, 1.0f);
    GXSetScissorBoxOffset(0, 0);
}

#pragma exceptions on

void Viewport::setDefault() {
    set(0, 0, BaseSystem::sSystem->getVideo()->getFbWidth(),
            BaseSystem::sSystem->getVideo()->getEfbHeight());
}

#pragma exceptions off

void Viewport::setupGXScissor() {
    GXSetScissor(mBox.mMin.x, mBox.mMin.y, mScreenWidth, mScreenHeight);
}

#pragma exceptions on

void Viewport::setupGX() {
    setupGXViewport();
    setupGXScissor();
}

void Viewport::setG3DCamera(nw4r::g3d::Camera &camera) {
    f32 xOrigin = mBox.mMin.x;
    f32 yOrigin = mBox.mMin.y;
    f32 width = mScreenWidth;
    f32 height = mScreenHeight;

    camera.SetScissor(xOrigin, yOrigin, width, height);
    camera.SetViewport(xOrigin, yOrigin, width, height);
}

#pragma exceptions off

} // namespace EGG
