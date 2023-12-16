#pragma once

#include <egg/math/eggBoundBox.h>

namespace EGG {

class Sphere3f {
public:
    void calc_boundbox(BoundBox3f &box);

private:
    Vector3f mPos;
    f32 mRadius;
};

} // namespace EGG
