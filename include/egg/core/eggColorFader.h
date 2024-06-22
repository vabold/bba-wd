#pragma once

#include <egg/core/eggFader.h>

#include <nw4r/ut/Color.h>
#include <nw4r/ut/Rect.h>

namespace EGG {

class ColorFader : public Fader {
public:
    ColorFader(f32, f32, f32, f32, nw4r::ut::Color, Fader::EStatus);
    virtual ~ColorFader() {}
    virtual void setStatus(EStatus status);
    virtual EStatus getStatus() const {
        return mStatus;
    }
    virtual bool fadeIn();
    virtual bool fadeOut();
    virtual bool calc();
    virtual void draw();

    void setFrame(u16 frame);
    void setColor(nw4r::ut::Color color);

private:
    u8 mFlags;
    u16 mFrame;
    u16 mFrameTimer;
    nw4r::ut::Color mColor;
    nw4r::ut::Rect mRect;
};

} // namespace EGG
