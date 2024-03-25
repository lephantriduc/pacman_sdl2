#pragma once

#include "Common.hpp"

class Timer {
public:
    Timer();

    void start();
    void reset();
    void restart();
    void pause();
    void unpause();
    int getTicks();
    bool isStarted();
    bool isPaused();

private:
    int startTicks;
    int pauseTicks;
    bool paused;
    bool started;
};