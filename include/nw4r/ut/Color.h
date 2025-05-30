#pragma once

#include <sdk/GXTypes.h>

namespace nw4r {
namespace ut {

struct Color : public _GXColor {
public:
    Color() {
        *this = 0xFFFFFFFF;
    }

    Color(const Color &rhs) {
        r = rhs.r;
        g = rhs.g;
        b = rhs.b;
        a = rhs.a;
    }

    Color(u32 val) {
        *this = val;
    }

    ~Color() {}

    void operator=(u32 val) {
        ToU32ref() = val;
    }

    u32 &ToU32ref() {
        return *reinterpret_cast<u32 *>(this);
    }
} __attribute__ ((aligned(4)));

} // namespace ut
} // namespace nw4r
