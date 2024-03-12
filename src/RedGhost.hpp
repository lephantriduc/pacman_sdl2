#pragma once

#include "Ghosts.hpp"

class RedGhost : public Ghosts{
public:
    RedGhost();

    void calcTarget(Position mPac);
    void updatePos(uint8_t actualBoard[], Pac &mPac);

private:
    uint8_t currentSpeed = this->getSpeed();

};
