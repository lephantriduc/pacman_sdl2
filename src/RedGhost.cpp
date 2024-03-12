#include "RedGhost.hpp"

RedGhost::RedGhost() : Ghosts(Red, Entities::redGhost){

}

void RedGhost::calcTarget(Position mPac) {
    this->target.setPosition(mPac.getPosition());
}

void RedGhost::updatePos(uint8_t actualBoard[], Pac &mPac) {
//    this->setSpeed(currentSpeed++);

    for(uint8_t i = 0; i < this->getSpeed(); i++){
        this->calcTarget(mPac);
        this->calcDirection(actualBoard);
        this->move(this->getDirection());
        this->goToOtherSideOfScreen();

    }
}


