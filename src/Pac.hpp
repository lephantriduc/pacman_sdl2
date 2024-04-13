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
    void setFrame(uint8_t newFrame);
    void turn(uint8_t mover);
    bool getPacDoneDying();
    void setPacDoneDying(bool answer);
    bool getPoweredUp();
    void setPoweredUp(bool YesOrNo);
    uint8_t foodCollision(uint8_t ActualMap[]);

private:
    Texture pacmanTexture;
    Texture deathTexture;

    SDL_Rect pacmanSpriteClips[pacmanFrames];
    SDL_Rect deathSpriteClips[deathFrames];

    uint8_t currentPacmanFrame;
    short currentDeathFrame;

    bool isPacDoneDying;
    bool isPoweredUp;

    int prev_x, prev_y, cur_x, cur_y;
};
