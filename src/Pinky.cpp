#include "Pinky.hpp"

Pinky::Pinky() : Ghosts(Entities::Pinky){
    ghostColor = {254,184,255};
}

void Pinky::setTarget(Position destination) {
    this->target.setPosition(destination.getPosition());
}

void Pinky::updatePos(uint8_t actualBoard[], Pac &mPac, bool inMenu) {
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
