#pragma once

#include <egg/math/eggMath.h>
#include <egg/math/eggQuat.h>
#include <egg/math/eggVector.h>

#include <nw4r/math/types.h>

namespace EGG {

struct Matrix34f {
    Matrix34f() {}
    Matrix34f(f32 xx, f32 xy, f32 xz, f32 xw, f32 yx, f32 yy, f32 yz, f32 yw, f32 zx, f32 zy,
            f32 zz, f32 zw);

    f32 operator()(int i, int j) const {
        return m[i][j];
    }
    f32 &operator()(int i, int j) {
        return m[i][j];
    }
    f32 operator()(int i) const {
        return arr[i];
    }
    f32 &operator()(int i) {
        return arr[i];
    }

    void inverseTo(Matrix34f &) const;
    void inverseTransposeTo(Matrix34f &) const;
    void makeIdentity();
    void makeSRT(const Vector3f &s, const Vector3f &r, const Vector3f &t);
    void makeRT(const Vector3f &r, const Vector3f &t);
    void makeR(const Vector3f &r);
    void makeST(const Vector3f &s, const Vector3f &t);
    void makeSQT(const Vector3f &s, const Quatf &q, const Vector3f &t);
    void makeQ(const Quatf &q);
    void makeS(const Vector3f &s);
    void makeT(const Vector3f &t);
    void setAxisRotation(const Vector3f &axis, f32 rot);
    Vector3f multVector(const Vector3f &vec) const;
    void multiplyTo(const Matrix34f &m2, Matrix34f &to) const;
    void loadPosMtx(u32 posMtxId);
    void dump();

    // NYI
    void rotateBaseX(Vector3f &, Matrix34f &);
    void rotateVectorChange(Vector3f &, Vector3f &, Matrix34f &);
    void inverseTo33(Matrix34f &) const;
    void calcRPY() const;
    void makeSQ(const Vector3f &s, const Quatf &q);
    void makeQT(const Quatf &q, const Vector3f &t);
    void fromQuat(const Quatf &q);
    void toQuat(Quatf &q) const;
    void slerpTo(const Matrix34f &from, Matrix34f &to, f32 t);
    void copyTo16(f32 *pf) const;
    void loadNrmMtx(u32 nrmMtxId);

    // Inlines
    void concat(const Matrix34f &, Matrix34f &) const;
    void copyFrom(const Matrix34f &other);
    void rotate(const Vector3f &rpy) const;
    void multVectorTo(const Vector3f &from, Vector3f &to) const;
    void transposeTo(Matrix34f &to) const;
    void setBase(int idx, const Vector3f &b) {
        m[0][idx] = b.x;
        m[1][idx] = b.y;
        m[2][idx] = b.z;
    }
    void getBase(int idx, Vector3f &b) const {
        b.x = m[0][idx];
        b.y = m[1][idx];
        b.z = m[2][idx];
    }
    void setTranslation(const Vector3f &t) {
        setBase(3, t);
    }
    void getTranslation(Vector3f &t) const {
        getBase(3, t);
    }
    void makeZero() {
        m[0][3] = m[0][2] = m[0][1] = m[0][0] = 0.0f;
        m[1][3] = m[1][2] = m[1][1] = m[1][0] = 0.0f;
        m[2][3] = m[2][2] = m[2][1] = m[2][0] = 0.0f;
    }

    union {
        f32 m[3][4];
        f32 arr[12];
    };

    static const Matrix34f ident;
};

} // namespace EGG
