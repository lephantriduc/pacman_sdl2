#pragma once

#include "Ghost.hpp"

class Clyde : public Ghost{
public:
    Clyde();

    void setTarget(Pac& mPac, Position mBlinky) override;
};