#pragma once

#include "Ghost.hpp"

class Pinky : public Ghost {
public:
    Pinky();

    void setTarget(Pac& mPac, Position mBlinky) override;
};
