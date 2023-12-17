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


    f32 dot(const Vector3f& r) const {
        return x*r.x+y*r.y+z*r.z;
    }
    
    // TODO: Implement
    Vector3f cross(const Vector3f& rhs) const {
        return Vector3f();
    }

    // TODO: Implement
    Vector3f operator+(const Vector3f& rhs) const {
        return Vector3f();
    };

    Vector3f operator*(f32 f) const { 
        return Vector3f(x*f, y*f, z*f);
    }
    
    // TODO: Implement
    friend Vector3f operator*(f32 f, const Vector3f& vec) { 
        return Vector3f();
    };


    static const Vector3f zero;
    static const Vector3f ex;
    static const Vector3f ey;
    static const Vector3f ez;
};

} // namespace EGG
