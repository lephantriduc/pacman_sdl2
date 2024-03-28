#pragma once

#include "Pac.hpp"

class Ghosts : public Entity{
public:
    Ghosts(Entity MyIdentity);
    ~Ghosts();

    void calcDirection(uint8_t ActualMap[]);
    void directionsBubbleSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections);

    void draw();
    Position target;
    RGB ghostColor;
private:
    Texture body;
    Texture eyes;
    SDL_Rect ghostSpriteClips[ghostFrames];
    SDL_Rect ghostEyesSpriteClips[ghostEyesFrames];
    uint8_t currentBodyFrame;
};
