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

    this->target.setPosition(30, 30);
}
