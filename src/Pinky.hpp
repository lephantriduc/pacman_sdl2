#pragma once

#include "Ghosts.hpp"

class Pinky : public Ghosts {
public:
    Pinky();

    void setTarget(Position destination);
    void updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu);
};
