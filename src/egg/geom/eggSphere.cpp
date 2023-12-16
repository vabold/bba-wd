#include <egg/geom/eggSphere.h>

namespace EGG {

void Sphere3f::calc_boundbox(BoundBox3f &box) {
    const Vector3f min = Vector3f(mPos.x - mRadius, mPos.y - mRadius, mPos.z - mRadius);
    const Vector3f max = Vector3f(mPos.x + mRadius, mPos.y + mRadius, mPos.z + mRadius);

    box.setDirect(min, max);
}

} // namespace EGG
