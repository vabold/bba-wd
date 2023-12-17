#include <egg/math/eggQuat.h>

#pragma exceptions on


namespace EGG {

void Quatf::set(f32 fw, f32 fx, f32 fy, f32 fz) {
    w = fw;
    vec.x = fx;
    vec.y = fy;
    vec.z = fz;
}

void Quatf::setRPY(const EGG::Vector3f& rpy) {
    const f32 cy = Math<f32>::cos(rpy.z * 0.5f);
    const f32 cp = Math<f32>::cos(rpy.y * 0.5f);
    const f32 cr = Math<f32>::cos(rpy.x * 0.5f);
    const f32 sy = Math<f32>::sin(rpy.z * 0.5f);
    const f32 sp = Math<f32>::sin(rpy.y * 0.5f);
    const f32 sr = Math<f32>::sin(rpy.x * 0.5f);

    const f32 cy_cp = cy * cp;
    const f32 sy_sp = sy * sp;
    const f32 cy_sp = cy * sp;
    const f32 sy_cp = sy * cp;
    
    w = (cy_cp * cr) + (sy_sp * sr);
    vec.x = (cy_cp * sr) - (sy_sp * cr);
    vec.y = (cy_sp * cr) + (sy_cp * sr);
    vec.z = (sy_cp * cr) - (cy_sp * sr);
}

Vector3f Quatf::calcRPY() {
   Vector3f rpy;
    
    const f32 ww = w*w;
    const f32 yy = vec.y*vec.y;
    const f32 xx = vec.x*vec.x;
    const f32 zz = vec.z*vec.z;
    
    const f32 a0 = (ww + xx) - yy - zz;
    const f32 a1 = (vec.x*vec.y + w*vec.z) * 2.0f;
    const f32 a2 = (vec.x*vec.z - w*vec.y) * 2.0f;
    const f32 a3 = (vec.y*vec.z + w*vec.x) * 2.0f;
    const f32 a4 = (ww - xx) - yy + zz;

    const f32 a5 = Math<f32>::abs(a2);

    if (a5 > 0.999999f) {

        f32 t0 = (vec.x*vec.y - w*vec.z)*2.0f;
        f32 t1 = (vec.x*vec.z + w*vec.y)*2.0f;

        rpy.x = 0.0f;
        rpy.y = a2 / a5 * -Math<f32>::pi_half();
        rpy.z = Math<f32>::atan2(-t0, -a2 * t1);
    } else {
        rpy.x = Math<f32>::atan2(a3, a4);
        rpy.y = Math<f32>::asin(-a2);
        rpy.z = Math<f32>::atan2(a1, a0);
    }

    return rpy;
}

void Quatf::setRPY(f32 roll, f32 pitch, f32 yaw) {
    setRPY(Vector3f(roll,pitch,yaw));
}

void Quatf::setAxisRotation(const Vector3f& axis, f32 rot) {
    const f32 half_angle = rot * 0.5f;
    const f32 cos = Math<f32>::cos(half_angle);
    const f32 sin = Math<f32>::sin(half_angle);
    set(cos, sin * axis.x, sin* axis.y, sin * axis.z);
}

// f32 Quatf::norm() {
//     return w*w + vec.dot(vec);
// }

// void Quatf::normalise() {
//     f32 mag = Math<f32>::sqrt(norm());
//     if (mag > 0.0f) {
//         multScalar(Math<f32>::inv(mag));
//     }
// }

Quatf Quatf::conjugate() {
    // force sdata2 odering. Normalise introduces it through Math<f32>::inv
    1.0f;

    Quatf q;
    q.w = w;
    q.vec = -1.0f * vec;
    return q; 
}

Vector3f Quatf::rotateVector(const Vector3f& rot) {
    Quatf conj, mult;
    conj = conjugate();
    mult = *this * rot;
    mult = mult*conj;
    return mult.vec;
}

Quatf operator*(const Quatf& q, const Vector3f& v) {
    Vector3f crossed = q.vec.cross(v);
    Vector3f scaled = q.w*v;
    Quatf ret = Quatf(-q.vec.dot(v), crossed+scaled);
    return ret;
}

void Quatf::slerpTo(const Quatf& q2, f32 t, Quatf& out) const {
    
    f32 dot = vec.x*q2.vec.x + vec.y*q2.vec.y + vec.z*q2.vec.z + w*q2.w;

    if (dot > 1.0f) {
        dot = 1.0f;
    } else if (dot < -1.0f) {
        dot = -1.0f;
    }

    bool lt0;
    if (dot < 0.0) {
        dot = -dot;
        lt0 = true;
    } else {
        lt0 = false;
    }

    const f32 theta_0 = Math<f32>::acos(dot);
    const f32 sin_theta_0 = Math<f32>::sin(theta_0);

    f32 a, b;
    if (Math<f32>::abs(sin_theta_0) < 1e-5f) {
        a = 1.0f-t;
        b = t;
    } else {
        const f32 sin_theta_0_inv  = 1.0f / sin_theta_0;
        const f32 theta = t * theta_0;
        a =  sin_theta_0_inv * Math<f32>::sin(theta_0-theta);
        b =  sin_theta_0_inv * Math<f32>::sin(theta);
    }

    if (lt0) b = -b;

    out.vec.x = a * vec.x + b * q2.vec.x;
    out.vec.y = a * vec.y + b * q2.vec.y;
    out.vec.z = a * vec.z + b * q2.vec.z;
    out.w     = a * w     + b * q2.w;
}

void Quatf::makeVectorRotation(Vector3f& from, Vector3f& to) {
    Vector3f cross = from.cross(to);
    f32 t0 = (from.dot(to) + 1) * 2.0f;

    if (t0 < 0.0f)  t0 = 0.0f;

    t0 = Math<f32>::sqrt(t0);

    if (t0 <= Math<f32>::epsilon()) {
        setUnit();
    } else {
        const f32 inv = 1.0f / t0;
        set(t0*0.5f, cross.x*inv, cross.y*inv, cross.z*inv);
    }
    
}

} // namespace EGG
