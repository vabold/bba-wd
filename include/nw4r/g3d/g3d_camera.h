#pragma once

namespace nw4r {
namespace g3d {

class Camera {
public:
    void SetScissor(u32 xOrigin, u32 yOrigin, u32 width, u32 height);
    void SetViewport(f32 xOrigin, f32 yOrigin, f32 width, f32 height);
};

} // namespace g3d
} // namespace nw4r
