#include "Blinky.hpp"

Blinky::Blinky() : Ghosts(Entities::Blinky){
    ghostColor = {255, 0, 0};
}

void Blinky::setTarget(Position destination) {
    this->target.setPosition(destination.getPosition());
}

void Blinky::updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu) {
//    this->setSpeed(currentSpeed++);

//    this->setDirection(right);
    for(uint8_t i = 0; i < this->getSpeed(); i++){
        if (this->isTargetToCalc(mPac)) {
            this->setTarget(mPac);
        }

        if (this->getLiving() && mPac.getPoweredUp()) {
            this->setFacing(4);
        } else {
            this->setFacing(this->getDirection());
        }
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


