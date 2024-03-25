#pragma once

#include "Ghosts.hpp"

class Blinky : public Ghosts{
public:
    Blinky();

    void calcTarget(Position mPac);
    void updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu);

private:
    uint8_t currentSpeed = this->getSpeed();
};
