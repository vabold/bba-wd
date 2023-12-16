#include <egg/math/eggBoundBox.h>

#include <egg/math/eggMath.h>

namespace EGG {

BoundBox3f::BoundBox3f() {
    resetBound();
}

void BoundBox3f::resetBound() {
    f32 max = Math<f32>::maxNumber();
    mMin.set(max, max, max);
    mMax.set(-max, -max, -max);
}

void BoundBox3f::setDirect(const Vector3f &min, const Vector3f &max) {
    mMax = max;
    mMin = min;
}

void BoundBox3f::setMin(const Vector3f &min) {
    mMin = min;
}

void BoundBox3f::setMax(const Vector3f &max) {
    mMax = max;
}

BoundBox2f::BoundBox2f() {
    resetBound();
}

void BoundBox2f::resetBound() {
    f32 max = Math<f32>::maxNumber();
    mMin.set(max, max);
    mMax.set(-max, -max);
}

void BoundBox2f::setDirect(const Vector2f &min, const Vector2f &max) {
    mMax = max;
    mMin = min;
}

void BoundBox2f::setMin(const Vector2f &min) {
    mMin = min;
}

void BoundBox2f::setMax(const Vector2f &max) {
    mMax = max;
}

void BoundBox2f::setFromCenterAndXY(const Vector2f &center, f32 x, f32 y) {
    f32 hx = x * 0.5f;
    f32 hy = y * 0.5f;
    mMin.set(center.x - hx, center.y - hy);
    mMax.set(center.x + hx, center.y + hy);
}

bool BoundBox2f::inside(const Vector2f &v) const {
    if (mMin.x <= v.x && v.x <= mMax.x && mMin.y <= v.y && v.y <= mMax.y) {
        return true;
    }

    return false;
}

} // namespace EGG
