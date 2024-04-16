#include "SusBrown.hpp"

SusBrown::SusBrown() : Impostor(Entities::SusBrown){
    restPos = {9999, 9999};
    SusColor = "Brown";
}

void SusBrown::setTarget(Pac &mPac, Position susRed) {
    // It selects target randomly

    srand(time(nullptr));
    int x = rand() % BOARD_WIDTH * BLOCK_SIZE_24;
    int y = rand() % BOARD_HEIGHT * BLOCK_SIZE_24;

    this->target.setPosition(x, y);
}
