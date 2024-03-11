#pragma once

#include "Ghosts.hpp"

class RedGhost : public Ghosts{
public:
    RedGhost();

    void calcTarget(Position mPac);
    void updatePos(unsigned char actualBoard[], Pac &mPac);
};
