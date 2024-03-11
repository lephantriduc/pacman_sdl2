#pragma once

#include "Pac.hpp"

class Ghosts : public Entity{
public:
    Ghosts(SDL_Color MyColor, Entity MyIdentity);
    ~Ghosts();
    void calcDirection(unsigned char ActualMap[]);
    void directionsBubbleSort(std::vector<float> &distances, std::vector<unsigned char> &possibleDirections);

    void draw();
    Position target;
private:
    TextureManager body;
    SDL_Rect ghostSpriteAnimation[ghostFrames];
    SDL_Color Color;
    unsigned char currentGhostFrame;
};
