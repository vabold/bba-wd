#pragma once

#include <egg/math/eggVector.h>

namespace EGG {

struct BoundBox2f {
    BoundBox2f();
    ~BoundBox2f() {}

    void resetBound();
    void setDirect(const Vector2f &max, const Vector2f &min);
    void setMin(const Vector2f &min);
    void setMax(const Vector2f &max);
    void setFromCenterAndXY(const Vector2f &center, f32 x, f32 y);
    bool inside(const Vector2f &v) const;

    f32 getSizeX() const {
        return mMax.x - mMin.x;
    }

    f32 getSizeY() const {
        return mMax.y - mMin.y;
    }

    Vector2f mMin;
    Vector2f mMax;
};

struct BoundBox3f {
    BoundBox3f();

    void resetBound();
    void setDirect(const Vector3f &max, const Vector3f &min);
    void setMin(const Vector3f &min);
    void setMax(const Vector3f &max);

    Vector3f mMin;
    Vector3f mMax;
};

} // namespace EGG
