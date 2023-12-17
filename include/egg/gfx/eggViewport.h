#pragma once

#include <egg/math/eggBoundBox.h>
#include <nw4r/g3d/g3d_camera.h>

namespace EGG {

class Viewport {
public:
    Viewport();

    void set(int left, int up, int right, int down);
    void setLUAndWH(f32 left, f32 up, f32 width, f32 height);
    void calc();

    void setupGXViewport();
    void setDefault();
    void setupGXScissor();
    void setupGX();

    void setG3DCamera(nw4r::g3d::Camera &camera);

private:
    BoundBox2f mBox;
    f32 mScreenWidth;
    f32 mScreenHeight;
    f32 mAspectRatio;
};

} // namespace EGG
