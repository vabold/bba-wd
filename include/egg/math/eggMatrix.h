#pragma once

#include <egg/math/eggQuat.h>

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

    void rotateBaseX(Vector3f &, Matrix34f &);
    void rotateVectorChange(Vector3f &, Vector3f &, Matrix34f &);
    void inverseTo33(Matrix34f &) const;
    void inverseTo(Matrix34f &to) const;
    void inverseTransposeTo(Matrix34f &to) const;
    void makeIdentity();
    void calcRPY() const;
    void makeSRT(const Vector3f &s, const Vector3f &r, const Vector3f &t);
    void makeRT(const Vector3f &r, const Vector3f &t);
    void makeR(const Vector3f &r);
    void makeST(const Vector3f &s, const Vector3f &t);
    void makeSQT(const Vector3f &s, const Quatf &q, const Vector3f &t);
    void makeSQ(const Vector3f &s, const Quatf &q);
    void makeQT(const Quatf &q, const Vector3f &t);
    void makeQ(const Quatf &q);
    void makeS(const Vector3f &s);
    void makeT(const Vector3f &t);
    void fromQuat(const Quatf &q);
    void toQuat(Quatf &q) const;
    void setAxisRotation(const Vector3f &axis, f32 rot);
    Vector3f multVector(const Vector3f &vec) const;
    void multiplyTo(const Matrix34f &m2, Matrix34f &to) const;
    void slerpTo(const Matrix34f &from, Matrix34f &to, f32 t);
    void copyTo16(f32 *pf) const;
    void loadPosMtx(u32 posMtxId);
    void loadNrmMtx(u32 nrmMtxId);
    void dump();

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
        for (int i = 0; i < 12; i++) {
            arr[i] = 0.0f;
        }
    }

    union {
        f32 m[3][4];
        f32 arr[12];
    };

    static const Matrix34f ident;
};

} // namespace EGG
