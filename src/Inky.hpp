#pragma once

#include "Blinky.hpp"

class Inky : public Ghost {
public:
    Inky();

    void setTarget(Pac& mPac, Position mBlinky) override;
};

