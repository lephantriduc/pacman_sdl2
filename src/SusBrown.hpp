#pragma once

#include "Impostor.hpp"

class SusBrown : public Impostor{
public:
    SusBrown();

    void setTarget(Pac& mPac, Position susRed) override;
};