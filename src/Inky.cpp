#include "Inky.hpp"

Inky::Inky() : Ghost(Entities::Inky) {
    ghostColor = {1, 255, 255};
}

void Inky::setTarget(Pac &mPac, Position mBlinky) {
    // Inky actually uses both Pac-Man's position/facing and Blinky's (the red ghost's) position in his calculation.
    // To locate Inky's target, we first start by selecting the position
    // two tiles in front of Pac-Man in his current direction of travel, similar to Pinky's targeting method.
    // From there, imagine drawing a vector from Blinky's position to this tile,
    // and then doubling the length of the vector.
    // The tile that this new, extended vector ends on will be Inky's actual target.

    int x_pac = mPac.getX();
    int y_pac = mPac.getY();

    int x_b = mBlinky.getX();
    int y_b = mBlinky.getY();

    switch(mPac.getDirection()) {
        case right:
            x_pac += 2;
            break;
        case left:
            x_pac -= 2;
            break;
        case up:
            y_pac -= 2;
            break;
        case down:
            y_pac += 2;
            break;
        default:
            break;
    }

    int x = 2 * x_pac - x_b;
    int y = 2 * y_pac - y_b;

    this->target.setPosition(x, y);
}
