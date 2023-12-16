#pragma once

#include <Common.h>

namespace nw4r {
namespace math {

struct _VEC2 {
    f32 x, y;
};

struct _VEC3 {
    f32 x, y, z;
};

struct VEC2 : public _VEC2 {
    VEC2() {}
    VEC2(f32 _x, f32 _y) {
        x = _x;
        y = _y;
    }
};

struct VEC3 : public _VEC3 {
    VEC3() {}
    VEC3(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};

} // namespace math
} // namespace nw4r
