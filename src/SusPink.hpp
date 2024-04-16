#pragma once

#include "Impostor.hpp"

class SusPink : public Impostor {
public:
    SusPink();

    void setTarget(Pac& mPac, Position susRed) override;
};
