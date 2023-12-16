#pragma once

#include <egg/math/eggMath.h>

#include <nw4r/math/types.h>

namespace EGG {

struct Vector2f : public nw4r::math::VEC2 {
    Vector2f() {}
    Vector2f(f32 _x, f32 _y) : nw4r::math::VEC2(_x, _y) {}

    ~Vector2f() {}

    f32 normalise();

    f32 length() const {
        return Math<f32>::sqrt(squaredLength());
    }

    f32 squaredLength() const {
        return x * x + y * y;
    }

    void set(f32 _x, f32 _y) {
        x = _x;
        y = _y;
    }

    static const Vector2f zero;
    static const Vector2f ex;
    static const Vector2f ey;
};

struct Vector3f : public nw4r::math::VEC3 {
    Vector3f() {}
    Vector3f(f32 _x, f32 _y, f32 _z) : nw4r::math::VEC3(_x, _y, _z) {}

    ~Vector3f() {}

    void test();

    f32 normalise();

    f32 length() const {
        return Math<f32>::sqrt(squaredLength());
    }

    f32 squaredLength() const {
        return x * x + y * y + z * z;
    }

    void set(f32 _x, f32 _y, f32 _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    static const Vector3f zero;
    static const Vector3f ex;
    static const Vector3f ey;
    static const Vector3f ez;
};

} // namespace EGG
