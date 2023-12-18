#pragma once

#include <egg/math/eggMatrix.h>

#include <sdk/gx/GXTransform.h>
#include <sdk/mtx/mtx.h>

#pragma exceptions on

namespace EGG {

void Matrix34f::inverseTo(Matrix34f &to) const {
    PSMTXInverse(m, to.m);
}

void Matrix34f::inverseTransposeTo(Matrix34f &to) const {
    PSMTXInvXpose(m, to.m);
}

void Matrix34f::makeIdentity() {
    // force sdata ordering
    1.0f;
    2.0f;
    makeZero();
    m[2][2] = 1.0f;
    m[1][1] = 1.0f;
    m[0][0] = 1.0f;
}

Matrix34f::Matrix34f(f32 xx, f32 xy, f32 xz, f32 xw, f32 yx, f32 yy, f32 yz, f32 yw, f32 zx, f32 zy,
        f32 zz, f32 zw) {
    m[0][0] = xx;
    m[0][1] = xy;
    m[0][2] = xz;
    m[0][3] = xw;
    m[1][0] = yx;
    m[1][1] = yy;
    m[1][2] = yz;
    m[1][3] = yw;
    m[2][0] = zx;
    m[2][1] = zy;
    m[2][2] = zz;
    m[2][3] = zw;
}

void Matrix34f::makeSRT(const Vector3f &s, const Vector3f &r, const Vector3f &t) {
    const f32 sin[3] = {Math<f32>::sin(r.x), Math<f32>::sin(r.y), Math<f32>::sin(r.z)};
    const f32 cos[3] = {Math<f32>::cos(r.x), Math<f32>::cos(r.y), Math<f32>::cos(r.z)};

    const f32 c0_c2 = cos[0] * cos[2];
    const f32 s0_s1 = sin[0] * sin[1];
    const f32 c0_s2 = cos[0] * sin[2];

    m[0][0] = s.x * (cos[1] * cos[2]);
    m[1][0] = s.x * (cos[1] * sin[2]);
    m[2][0] = s.x * (-sin[1]);

    m[0][1] = s.y * ((s0_s1 * cos[2]) - c0_s2);
    m[1][1] = s.y * ((s0_s1 * sin[2]) + c0_c2);
    m[2][1] = s.y * (sin[0] * cos[1]);

    m[0][2] = s.z * ((c0_c2 * sin[1]) + (sin[0] * sin[2]));
    m[1][2] = s.z * ((c0_s2 * sin[1]) - (sin[0] * cos[2]));
    m[2][2] = s.z * (cos[0] * cos[1]);

    m[0][3] = t.x;
    m[1][3] = t.y;
    m[2][3] = t.z;
}

void Matrix34f::makeRT(const Vector3f &r, const Vector3f &t) {
    const f32 sin[3] = {Math<f32>::sin(r.x), Math<f32>::sin(r.y), Math<f32>::sin(r.z)};
    const f32 cos[3] = {Math<f32>::cos(r.x), Math<f32>::cos(r.y), Math<f32>::cos(r.z)};

    const f32 c0_c2 = cos[0] * cos[2];
    const f32 s0_s1 = sin[0] * sin[1];
    const f32 c0_s2 = cos[0] * sin[2];

    m[0][0] = (cos[1] * cos[2]);
    m[1][0] = (cos[1] * sin[2]);
    m[2][0] = (-sin[1]);

    m[0][1] = (s0_s1 * cos[2]) - c0_s2;
    m[1][1] = (s0_s1 * sin[2]) + c0_c2;
    m[2][1] = (sin[0] * cos[1]);

    m[0][2] = (c0_c2 * sin[1]) + (sin[0] * sin[2]);
    m[1][2] = (c0_s2 * sin[1]) - (sin[0] * cos[2]);
    m[2][2] = (cos[0] * cos[1]);

    m[0][3] = t.x;
    m[1][3] = t.y;
    m[2][3] = t.z;
}

void Matrix34f::makeR(const Vector3f &r) {
    const f32 sin[3] = {Math<f32>::sin(r.x), Math<f32>::sin(r.y), Math<f32>::sin(r.z)};
    const f32 cos[3] = {Math<f32>::cos(r.x), Math<f32>::cos(r.y), Math<f32>::cos(r.z)};

    const f32 c0_c2 = cos[0] * cos[2];
    const f32 s0_s1 = sin[0] * sin[1];
    const f32 c0_s2 = cos[0] * sin[2];

    m[0][0] = (cos[1] * cos[2]);
    m[1][0] = (cos[1] * sin[2]);
    m[2][0] = (-sin[1]);

    m[0][1] = (s0_s1 * cos[2]) - c0_s2;
    m[1][1] = (s0_s1 * sin[2]) + c0_c2;
    m[2][1] = (sin[0] * cos[1]);

    m[0][2] = (c0_c2 * sin[1]) + (sin[0] * sin[2]);
    m[1][2] = (c0_s2 * sin[1]) - (sin[0] * cos[2]);
    m[2][2] = (cos[0] * cos[1]);

    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}

void Matrix34f::makeST(const Vector3f &s, const Vector3f &t) {
    m[0][0] = s.x;
    m[1][0] = 0.0f;
    m[2][0] = 0.0f;
    m[0][1] = 0.0f;
    m[1][1] = s.y;
    m[2][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][2] = 0.0f;
    m[2][2] = s.z;
    m[0][3] = t.x;
    m[1][3] = t.y;
    m[2][3] = t.z;
}

void Matrix34f::makeSQT(const Vector3f &s, const Quatf &q, const Vector3f &t) {
    f32 yy = 2.0f * q.v.y * q.v.y;
    f32 zz = 2.0f * q.v.z * q.v.z;
    f32 xx = 2.0f * q.v.x * q.v.x;
    f32 xy = 2.0f * q.v.x * q.v.y;
    f32 xz = 2.0f * q.v.x * q.v.z;
    f32 yz = 2.0f * q.v.y * q.v.z;
    f32 wz = 2.0f * q.w * q.v.z;
    f32 wx = 2.0f * q.w * q.v.x;
    f32 wy = 2.0f * q.w * q.v.y;

    m[0][0] = s.x * (1.0f - yy - zz);
    m[0][1] = s.y * (xy - wz);
    m[0][2] = s.z * (xz + wy);

    m[1][0] = s.x * (xy + wz);
    m[1][1] = s.y * (1.0f - xx - zz);
    m[1][2] = s.z * (yz - wx);

    m[2][0] = s.x * (xz - wy);
    m[2][1] = s.y * (yz + wx);
    m[2][2] = s.z * (1.0f - xx - yy);

    m[0][3] = t.x;
    m[1][3] = t.y;
    m[2][3] = t.z;
}

void Matrix34f::makeQ(const Quatf &q) {
    f32 yy = 2.0f * q.v.y * q.v.y;
    f32 zz = 2.0f * q.v.z * q.v.z;
    f32 xx = 2.0f * q.v.x * q.v.x;
    f32 xy = 2.0f * q.v.x * q.v.y;
    f32 xz = 2.0f * q.v.x * q.v.z;
    f32 yz = 2.0f * q.v.y * q.v.z;
    f32 wz = 2.0f * q.w * q.v.z;
    f32 wx = 2.0f * q.w * q.v.x;
    f32 wy = 2.0f * q.w * q.v.y;

    m[0][0] = 1.0f - yy - zz;
    m[0][1] = xy - wz;
    m[0][2] = xz + wy;

    m[1][0] = xy + wz;
    m[1][1] = 1.0f - xx - zz;
    m[1][2] = yz - wx;

    m[2][0] = xz - wy;
    m[2][1] = yz + wx;
    m[2][2] = 1 - xx - yy;

    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}

void Matrix34f::makeS(const Vector3f &s) {
    m[0][0] = s.x;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = s.y;
    m[1][2] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = s.z;
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
}

void Matrix34f::makeT(const Vector3f &t) {
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
    m[0][3] = t.x;
    m[1][3] = t.y;
    m[2][3] = t.z;
}

void Matrix34f::setAxisRotation(const Vector3f &axis, f32 rot) {
    Quatf q;
    q.setAxisRotation(axis, rot);
    makeQ(q);
}

Vector3f Matrix34f::multVector(const Vector3f &vec) const {
    Vector3f ret;
    multVectorTo(vec, ret);
    return ret;
}

void Matrix34f::multiplyTo(const Matrix34f &m2, Matrix34f &to) const {
    PSMTXConcat(m, m2.m, to.m);
}

void Matrix34f::loadPosMtx(u32 posMtxId) {
    GXLoadPosMtxImm(m, posMtxId);
}

void Matrix34f::dump() {}

const Matrix34f Matrix34f::ident(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f);

} // namespace EGG
