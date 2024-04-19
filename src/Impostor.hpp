#pragma once

#include "Pac.hpp"

class Impostor : public Entity{
public:
    Impostor(Entity MyIdentity);
    ~Impostor();

    bool isHome();
    void calcDirection(uint8_t ActualMap[]);
    bool isTargetToCalc(Pac& mPac);
    void setChasingOrNot(bool TimedStatus, Pac& mPac);
    virtual void setTarget(Pac& mPac, Position susRed = {0, 0});
    virtual void updatePos(uint8_t actualBoard[], Pac &mPac, Position susRed, bool inMenu, bool TimedStatus);

    void merge(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections, std::vector<int> &tempDistances, std::vector<uint8_t> &tempDirections, int left, int mid, int right);
    void mergeSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections, std::vector<int> &tempDistances, std::vector<uint8_t> &tempDirections, int left, int right);
    void directionsMergeSort(std::vector<int> &distances, std::vector<uint8_t> &possibleDirections);

    void draw(Pac& pac);
    Position target;
    Position home;
    Position doorTarget;
    Position restPos;
    std::string SusColor;
private:
    Texture body;
    SDL_Rect impostorSpriteClips[impostorFrames];
    uint8_t currentBodyFrame;

    bool canUseDoor;
    bool isChasing;
};
