#include "Ghosts.hpp"

Ghosts::Ghosts(Entity mIdentity) : Entity(mIdentity) {
    body.load("assets/Ghost.png");
    eyes.load("assets/GhostEyes.png");
    InitFrames(ghostFrames, ghostSpriteClips);
    InitFrames(ghostEyesFrames, ghostEyesSpriteClips);
    currentBodyFrame = 0;
    canUseDoor = false;
    doorTarget.setPosition(13 * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2, 15 * BLOCK_SIZE_24);
    home.setPosition(13 * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2, 17 * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
}

Ghosts::~Ghosts() {
    body.free();
}

void Ghosts::calcDirection(uint8_t ActualMap[]) {
    std::vector<int> distances;
    std::vector<uint8_t> possibleDirections;

    // Checking for each of the 4 directions
    for (uint8_t i = 0; i < 4; i++) {
        short x = this->getX();
        short y = this->getY();
        // Get the next possible block (there are 4 of them)
        this->getNextPosition(x, y, i);
        if (!this->wallCollision(x, y, ActualMap, canUseDoor)) { // Process the direction if it isn't a wall
            // Calculating distance from each potential block to Pac
            auto distX = abs(x - this->target.getX());
            if (distX > SCREEN_WIDTH / 2)
                distX = SCREEN_WIDTH - distX;
            auto distY = abs(y - target.getY());
            auto dist = (distX * distX + distY * distY);

            distances.push_back(dist);
            possibleDirections.push_back(i);
        }
    }

    // Sort the possible directions
    this->directionsBubbleSort(distances, possibleDirections);

    // To make sure that ghosts won't reverse direction abruptly
    for (uint8_t i = 0; i < possibleDirections.size(); i++) {
        if (possibleDirections.at(i) != (this->getDirection() + 2) % 4) {
            this->setDirection(possibleDirections.at(i));
            return;
        }
    }
}

void Ghosts::draw(Pac &pac) {
    RGB white{0xff, 0xff, 0xff};

    if (this->getLiving()) {
        if (!pac.getPoweredUp()) {
            body.paint(ghostColor);
            this->setSpeed(2);
        } else {
            body.paint({0,0,255});
            this->setSpeed(1);
        }
    } else {
        body.paint({0,0,0});
        this->setSpeed(5);
    }

    if (this->isHome()) {
        this->setLiving(true);
    }

    eyes.paint(white);

    currentClip = &ghostSpriteClips[currentBodyFrame / ghostFrames];
    body.render(this->getX() - 4, this->getY() - 4, 0, currentClip);

    currentClip = &ghostEyesSpriteClips[this->getFacing()];
    eyes.render(this->getX() - 4, this->getY() - 4, 0, currentClip);

    currentBodyFrame++;
    if (currentBodyFrame / ghostFrames >= ghostFrames) {
        currentBodyFrame = 0;
    }
}

void Ghosts::directionsBubbleSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections) {
    for (uint8_t i = 0; i < distances.size(); i++) {
        for (uint8_t j = 0; j < distances.size(); j++) {
            if (distances.at(i) < distances.at(j)) {
                auto temp1 = distances.at(i);
                distances.at(i) = distances.at(j);
                distances.at(j) = temp1;
                uint8_t temp2 = possibleDirections.at(i);
                possibleDirections.at(i) = possibleDirections.at(j);
                possibleDirections.at(j) = temp2;
            }
        }
    }
}

bool Ghosts::isHome() {
    if(this->getX() > 11 * BLOCK_SIZE_24 && this->getX() < 17 * BLOCK_SIZE_24){
        if(this->getY() > 15 * BLOCK_SIZE_24 && this->getY() < 18 * BLOCK_SIZE_24)
            return true;
    }
    return false;
}

bool Ghosts::isTargetToCalc(Pac &mPac){

    if(!this->getLiving()){
        canUseDoor = true;
        target.setPosition(home);
        if(this->getPosition() == home.getPosition())
            this->setLiving(true);
        return false;
    }

    if(this->isHome() && mPac.getPoweredUp()){
        if(this->getPosition() == home.getPosition())
            target.setY(this->home.getY() - BLOCK_SIZE_24);
        else if(this->getX() == home.getX() && this->getY() == home.getY() - BLOCK_SIZE_24)
            target.setY(this->home.getY());
        return false;
    }

    if(this->isHome() && this->getLiving()){
        canUseDoor = true;
        target.setPosition(this->doorTarget);
        return false;
    }

    canUseDoor = false;
    return true;
}

