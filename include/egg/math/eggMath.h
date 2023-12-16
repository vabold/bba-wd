#pragma once

#include <Common.h>

namespace EGG {

template <typename T>
struct Math {
    static T maxNumber() {
        // TODO: Generalize to other classes
        // This is low priority since it will always be a float
        return FLT_MAX;
    }
};

} // namespace EGG
