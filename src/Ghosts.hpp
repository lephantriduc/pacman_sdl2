#pragma once

#include "Pac.hpp"

class Ghosts : public Entity{
public:
    Ghosts(SDL_Color MyColor, Entity MyIdentity);
    ~Ghosts();

    void calcDirection(uint8_t ActualMap[]);
    void directionsBubbleSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections);

    void draw();
    Position target;
private:
    TextureManager body;
    SDL_Rect ghostSpriteAnimation[ghostFrames];
    SDL_Color Color;
    uint8_t currentGhostFrame;
};
