#include "Timer.hpp"

Timer::Timer() {
    startTicks = 0;
    pauseTicks = 0;
    paused = started = false;
}

void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pauseTicks = 0;
}

void Timer::reset() {
    startTicks = 0;
    pauseTicks = 0;
    paused = started = false;
}

void Timer::restart() {
    this->reset();
    this->start();
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;
    }
}

int Timer::getTicks() {
    int time = 0;
    if (started) {
        if (paused) {
            time = pauseTicks;
        } else {
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool Timer::isStarted() {
    return started;
}

bool Timer::isPaused() {
    return paused;
}





