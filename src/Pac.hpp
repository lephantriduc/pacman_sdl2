#pragma once

#include "Entity.hpp"

class Pac : public Entity{
public:
    Pac();
    ~Pac();
    void updatePosition(std::vector<uint8_t> &mover, uint8_t ActualMap[]);
    void updatePosition(std::vector<uint8_t> &mover);
    void draw();
    void updateFrame();
    void turn(uint8_t mover);
    uint8_t foodCollision(uint8_t ActualMap[]);

private:
    Texture pacmanTexture;
    SDL_Rect pacmanSpriteClips[pacmanFrames];
    uint8_t currentPacmanFrame;
};
