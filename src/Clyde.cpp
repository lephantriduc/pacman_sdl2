#include "Clyde.hpp"

Clyde::Clyde() : Ghost(Entities::Clyde){
    ghostColor = {255,185,81};
}

void Clyde::setTarget(Pac &mPac, Position mBlinky) {
    // It selects target randomly

    srand(time(nullptr));
    int x = rand() % BOARD_WIDTH * BLOCK_SIZE_24;
    int y = rand() % BOARD_HEIGHT * BLOCK_SIZE_24;

    this->target.setPosition(x, y);
}
