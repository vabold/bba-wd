#pragma once

#include <egg/core/eggFader.h>

#include <nw4r/ut/ut_Color.h>

namespace EGG {

class ColorFader : public Fader {
public:
    ColorFader(f32, f32, f32, f32, nw4r::ut::Color, Fader::EStatus);
    virtual ~ColorFader();
    
private:
    u8 _08[0x24 - 0x08];
};

} // namespace EGG
