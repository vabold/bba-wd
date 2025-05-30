#pragma once

#include <Common.h>

namespace nw4r {
namespace ut {

struct Rect {
    Rect(f32 l, f32 t, f32 r, f32 b) : left(l), top(t), right(r), bottom(b) {}

    f32 GetWidth() const {
        return right - left;
    }

    f32 GetHeight() const {
        return bottom - top;
    }

    f32 left, top, right, bottom;
};

} // namespace ut
} // namespace nw4r
