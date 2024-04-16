#include "SusGreen.hpp"

SusGreen::SusGreen() : Impostor(Entities::SusGreen) {
    restPos = {-999,9999};
    SusColor = "Green";
}

void SusGreen::setTarget(Pac &mPac, Position susRed) {
    // SusGreen actually uses both Pac-Man's position/facing and SusRed's position in his calculation.
    // To locate SusGreen's target, we first start by selecting the position
    // two tiles in front of Pac-Man in his current direction of travel, similar to SusPink's targeting method.
    // From there, imagine drawing a vector from SusRed's position to this tile,
    // and then doubling the length of the vector.
    // The tile that this new, extended vector ends on will be SusGreen's actual target.

    int x_pac = mPac.getX();
    int y_pac = mPac.getY();

    int x_b = susRed.getX();
    int y_b = susRed.getY();

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
