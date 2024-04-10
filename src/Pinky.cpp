#include "Pinky.hpp"

Pinky::Pinky() : Ghost(Entities::Pinky){
    ghostColor = {254,184,255};
}

void Pinky::setTarget(Pac& mPac, Position mBlinky) {
    // Pinky's target tile is determined by looking at Pac-Man's current position and orientation
    // and selecting the location four tiles straight ahead of Pac-Man.
    int x = mPac.getX();
    int y = mPac.getY();

    switch(mPac.getDirection()) {
        case right:
            x += 4;
            break;
        case left:
            x -= 4;
            break;
        case up:
            y -= 4;
            break;
        case down:
            y += 4;
            break;
        default:
            break;
    }

    this->target.setPosition(x, y);
}

