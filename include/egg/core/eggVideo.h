#pragma once

#include <Common.h>

namespace EGG {

class Video {
public:
    bool isBlack() {
        return !(mFlag & 1);
    }

private:
    u8 _00[0x04 - 0x00];
    u8 mFlag;
};

} // namespace EGG
