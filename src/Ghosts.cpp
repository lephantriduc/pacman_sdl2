#include "Ghosts.hpp"

Ghosts::Ghosts(Entity mIdentity) : Entity(mIdentity) {
    body.load("assets/Ghost.png");
    eyes.load("assets/GhostEyes.png");
    InitFrames(ghostFrames, ghostSpriteClips);
    InitFrames(ghostEyesFrames, ghostEyesSpriteClips);
    currentBodyFrame = 0;
}

Ghosts::~Ghosts() {
    body.free();
}

void Ghosts::calcDirection(uint8_t ActualMap[]) {
    std::vector<int> distances;
    std::vector<uint8_t> possibleDirections;

    // Checking for each of the 4 directions
    for(uint8_t i = 0; i < 4; i++){
        short x = this->getX();
        short y = this->getY();
        // Get the next possible block (there are 4 of them)
        this->getNextPosition(x, y, i);
        if(!this->wallCollision(x, y, ActualMap)){ // Process the direction if it isn't a wall
            // Calculating distance from each potential block to Pac
            auto distX = abs(x - this->target.getX());
            if(distX > SCREEN_WIDTH / 2)
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
    for(uint8_t i = 0; i < possibleDirections.size(); i++){
        if(possibleDirections.at(i) != (this->getDirection() + 2) % 4){
            this->setDirection(possibleDirections.at(i));
            return;
        }
    }
}

void Ghosts::draw() {
    RGB red {0xff, 0x00, 0x00};
    RGB white {0xff, 0xff, 0xff};

    body.paint(ghostColor);
    eyes.paint(white);

    currentClip = &ghostSpriteClips[currentBodyFrame / ghostFrames];
    body.render(this->getX() - 4, this->getY() - 4, 0, currentClip);

    currentClip = &ghostEyesSpriteClips[this->getFacing()];
    eyes.render(this->getX() - 4, this->getY() - 4, 0, currentClip);

    currentBodyFrame++;
    if(currentBodyFrame / ghostFrames >= ghostFrames){
        currentBodyFrame = 0;
    }
}

void Ghosts::directionsBubbleSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections) {
    for(uint8_t i = 0; i < distances.size(); i++){
        for(uint8_t j = 0; j < distances.size(); j++){
            if(distances.at(i) < distances.at(j)){
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

