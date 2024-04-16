#pragma once

#include "SusRed.hpp"

class SusGreen : public Impostor {
public:
    SusGreen();

    void setTarget(Pac& mPac, Position susRed) override;
};

