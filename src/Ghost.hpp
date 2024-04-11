#pragma once

#include "Pac.hpp"

class Ghost : public Entity{
public:
    Ghost(Entity MyIdentity);
    ~Ghost();

    bool isHome();
    void calcDirection(uint8_t ActualMap[]);
    void directionsBubbleSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections);
    bool isTargetToCalc(Pac& mPac);
    void setChasingOrNot(bool TimedStatus, Pac& mPac);
    virtual void setTarget(Pac& mPac, Position mBlinky = {0, 0});
    virtual void updatePos(uint8_t actualBoard[], Pac &mPac, Position mBlinky, bool inMenu, bool TimedStatus);

    void draw(Pac& pac);
    Position target;
    Position home;
    Position doorTarget;
    Position restPos;
    RGB ghostColor;
private:
    Texture body;
    Texture eyes;
    SDL_Rect ghostSpriteClips[ghostFrames];
    SDL_Rect ghostEyesSpriteClips[ghostEyesFrames];
    uint8_t currentBodyFrame;

    bool canUseDoor;
    bool isChasing;
};
