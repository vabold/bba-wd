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

    static T pi() {
        return 3.14159265f;
    }

    static T pi_half() {
        return pi()/2.0f;
    }

    static T epsilon() {
        return 1.192092896e-07f;
    }

    static T inv(T t) {
        return 1 / t;
    }

    static T abs(T t) { 
        return t > 0 ? t : -t;
    }

    static T sqrt(T); 
    static T sin(T);
    static T cos(T);
    static T tan(T);
    static T asin(T);
    static T acos(T);
    static T atan2(T, T);
    static T log10(T);
};

} // namespace EGG
