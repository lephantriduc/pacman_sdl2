#include "Ghosts.hpp"

Ghosts::Ghosts(SDL_Color MyColor, Entity mIdentity) : Entity(mIdentity) {
    body.load("assets/ghost_test.png");
    InitFrames(ghostFrames, ghostSpriteAnimation);
    Color = MyColor;
    currentGhostFrame = 0;
}

Ghosts::~Ghosts() {
    body.free();
}

void Ghosts:: calcDirection(unsigned char ActualMap[]) {
    std::vector<float> distances;
    std::vector<uint8_t> possibleDirections;
    for(uint8_t i = 0; i < 4; i++){
        short x = this->getX();
        short y = this->getY();
        this->getNextPosition(x, y, i);
        if(!this->wallCollision(x, y, ActualMap)){
            float distX = abs(x - this->target.getX());
            if(distX > SCREEN_WIDTH / 2)
                distX = SCREEN_WIDTH - distX;
            auto dist = static_cast<float>(distX * distX + (y - target.getY()) * (y - target.getY()));
            distances.push_back(dist);
            possibleDirections.push_back(i);
        }
    }

    if (distances.size() != 2) std::cout << distances.size() << '\n';
    this->directionsBubbleSort(distances, possibleDirections);

    for(uint8_t i = 0; i < possibleDirections.size(); i++){
        if(possibleDirections.at(i) != (this->getDirection() + 2) % 4){
            this->setDirection(possibleDirections.at(i));
            return;
        }
    }
}

void Ghosts::draw() {
    RGB red {0xff, 0x00, 0x00};
    body.paint(red);
    body.render(this->getX() - 4, this->getY() - 4, 0, NULL);

}

void Ghosts::directionsBubbleSort(std::vector<float> &distances, std::vector<unsigned char> &possibleDirections) {
    for(unsigned char i = 0; i < distances.size(); i++){
        for(unsigned char j = 0; j < distances.size(); j++){
            if(distances.at(i) < distances.at(j)){
                float temp1 = distances.at(i);
                distances.at(i) = distances.at(j);
                distances.at(j) = temp1;
                unsigned char temp2 = possibleDirections.at(i);
                possibleDirections.at(i) = possibleDirections.at(j);
                possibleDirections.at(j) = temp2;
            }
        }
    }
}

