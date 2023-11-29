#pragma once

#include <sdk/GXTypes.h>

namespace nw4r {
namespace ut {

struct Color : public _GXColor {
public:
    Color(u32 val) {
        *this = val;
    }

    Color &operator=(u32 val) {
        ToU32ref() = val;
    }

    u32 &ToU32ref() {
        return *reinterpret_cast<u32 *>(this);
    }
};

} // namespace ut
} // namespace nw4r
