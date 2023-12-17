#include <egg/math/eggVector.h>

namespace EGG {

struct Quatf {
    Vector3f vec;
    f32 w;

    Quatf() {}
    Quatf(f32 f, Vector3f v) : w(f), vec(v){};
    Quatf(f32 fx, f32 fy, f32 fz, f32 fw){};
    ~Quatf() {}

    void multScalar(f32 s) {
        w *= s;
        vec.x *= s;
        vec.y *= s;
        vec.z *= s;
    }

    void set(f32 fw, f32 fx, f32 fy, f32 fz);
    void setUnit() {
        set(1.0f, 0.0f, 0.0f, 0.0f);
    }

    void setRPY(const EGG::Vector3f &);
    Vector3f calcRPY();
    void setRPY(f32 roll, f32 pitch, f32 yaw);
    void setAxisRotation(const Vector3f &, f32);
    f32 norm();
    void normalise();
    Quatf conjugate();

    Vector3f rotateVector(const Vector3f &);

    friend Quatf operator*(const Quatf &, const Vector3f &);

    // TODO: Implement
    friend Quatf operator*(const Quatf &, const Quatf &) {
        return Quatf();
    };

    void slerpTo(const Quatf &, f32, Quatf &out) const;
    void makeVectorRotation(Vector3f &, Vector3f &);
};

} // namespace EGG
