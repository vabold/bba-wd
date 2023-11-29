#pragma once

#include <Common.h>

namespace EGG {

class Fader {
public:
    enum EStatus {
        FADER_STATUS_OPAQUE,
        FADER_STATUS_HIDDEN,
        FADER_STATUS_FADE_IN,
        FADER_STATUS_FADE_OUT
    };

    virtual void setStatus(EStatus status);
    virtual EStatus getStatus() const;
    virtual bool fadeIn();
    virtual bool fadeOut();
    virtual BOOL calc();
    virtual void draw();

private:
    EStatus mStatus;
};

} // namespace EGG
