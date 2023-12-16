#pragma once

#include <egg/math/eggVector.h>

namespace EGG {

class BoundBox2f {
public:
    BoundBox2f();

    void resetBound();
    void setDirect(const Vector2f &max, const Vector2f &min);
    void setMin(const Vector2f &min);
    void setMax(const Vector2f &max);
    void setFromCenterAndXY(const Vector2f &center, f32 x, f32 y);
    bool inside(const Vector2f &v) const;

private:
    Vector2f mMax;
    Vector2f mMin;
};

class BoundBox3f {
public:
    BoundBox3f();

    void resetBound();
    void setDirect(const Vector3f &max, const Vector3f &min);
    void setMin(const Vector3f &min);
    void setMax(const Vector3f &max);

private:
    Vector3f mMax;
    Vector3f mMin;
};

} // namespace EGG
