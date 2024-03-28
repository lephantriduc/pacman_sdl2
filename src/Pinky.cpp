#include "Pinky.hpp"

Pinky::Pinky() : Ghosts(Entities::Pinky){
    ghostColor = {254,184,255};
}

void Pinky::calcTarget(Position mPac) {
    this->target.setPosition(mPac.getPosition());
}

void Pinky::updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu) {
//    this->setSpeed(currentSpeed++);

//    this->setDirection(right);
    for(uint8_t i = 0; i < this->getSpeed(); i++){
        this->calcTarget(mPac);
        this->setFacing(this->getDirection());
        if (!inMenu) {
            this->calcDirection(actualBoard);
            this->move(this->getDirection());
            this->checkIfGoesOutOfScreen(false);
        }
        else {
            this->move(this->getDirection());
            this->checkIfGoesOutOfScreen(false);
        }
    }
}
