#pragma once

#include "Ghosts.hpp"

class Pinky : public Ghosts {
public:
    Pinky();

    void calcTarget(Position mPac);
    void updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu);
};
