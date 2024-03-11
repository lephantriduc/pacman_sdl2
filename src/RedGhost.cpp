#include "RedGhost.hpp"

RedGhost::RedGhost() : Ghosts(Red, Entities::redGhost){
}

void RedGhost::calcTarget(Position mPac) {
    this->target.setPosition(mPac.getPosition());
}

void RedGhost::updatePos(unsigned char actualBoard[], Pac &mPac) {
    for(uint8_t i = 0; i < this->getSpeed(); i++){
        this->calcTarget(mPac);
        this->calcDirection(actualBoard);
        this->move(this->getDirection());
        this->goToOtherSideOfScreen();

    }
}


