#pragma once

#include <egg/math/eggVector.h>

namespace EGG {

struct Quatf {
    Quatf() {}
    Quatf(f32 f, Vector3f v) : w(f), v(v) {}

    ~Quatf() {}

    friend Quatf operator*(const Quatf &, const Vector3f &);

    // TODO: Implement
    friend Quatf operator*(const Quatf &, const Quatf &) {
        return Quatf();
    };

    void set(f32 fw, f32 fx, f32 fy, f32 fz);
    void setRPY(const EGG::Vector3f &rpy);
    Vector3f calcRPY();
    void setRPY(f32 roll, f32 pitch, f32 yaw);
    void setAxisRotation(const Vector3f &axis, f32 rot);
    f32 norm();
    void normalise();
    Quatf conjugate();
    Vector3f rotateVector(const Vector3f &vec);
    void slerpTo(const Quatf &q2, f32 t, Quatf &out) const;
    void makeVectorRotation(Vector3f &from, Vector3f &to);

    void multScalar(f32 s) {
        w *= s;
        v.x *= s;
        v.y *= s;
        v.z *= s;
    }
    void setUnit() {
        set(1.0f, 0.0f, 0.0f, 0.0f);
    }

    Vector3f v;
    f32 w;
};

} // namespace EGG
