#pragma once

#include <sdk/OSTime.h>

namespace EGG {

class LongStopWatch {
public:
    LongStopWatch();

    void start();
    void reset();

    void stop() {
        if (isRunning()) {
            mStopTime = OSGetTime();
        }
    }

    bool isRunning() {
        return mStopTime == 0;
    }

    u64 getTime() {
        u64 time = isRunning() ? OSGetTime() : mStopTime;
        return time - mBaseTime;
    }

private:
    u64 mStopTime;
    u64 mBaseTime;
};

} // namespace EGG
