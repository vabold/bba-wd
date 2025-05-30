#include <egg/core/eggLongStopWatch.h>

namespace EGG {

void LongStopWatch::start() {
    // Unknown
    u32 arr[] = {0, 0};

    if (!isRunning()) {
        // If we were paused, we need to not count the time
        mBaseTime += OSGetTime() - mStopTime;
        mStopTime = 0;
    }
}

void LongStopWatch::reset() {
    // This behavior is undesirable because it could lead to a wrong base time if paused
    // This should be one OSGetTime call put into a local var so paused timers start at 0
    mBaseTime = OSGetTime();
    if (!isRunning()) {
        mStopTime = OSGetTime();
    }
}

LongStopWatch::LongStopWatch() {
    stop();
    reset();
}

} // namespace EGG
