#pragma once

#include <nw4r/math/types.h>

namespace EGG {

struct Vector2f : public nw4r::math::VEC2 {
    Vector2f() {}
    Vector2f(f32 _x, f32 _y) : nw4r::math::VEC2(_x, _y) {}

    void set(f32 _x, f32 _y) {
        x = _x;
        y = _y;
    }
};

struct Vector3f : public nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(f32 _x, f32 _y, f32 _z) : nw4r::math::VEC3(_x, _y, _z) {}

    void set(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

} // namespace EGG
