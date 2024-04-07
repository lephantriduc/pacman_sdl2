#pragma once

#include "Ghosts.hpp"

class Blinky : public Ghosts{
public:
    Blinky();

    void setTarget(Position destination);
    void updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu);
private:

};
