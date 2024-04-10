#pragma once

#include "Board.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"
#include "Timer.hpp"

class Game {
public:
    Game();
    ~Game();

    void start();
    void draw();
    void setMap(int clicks);
    void update(std::vector<uint8_t> &mover);
    void updatePositions(std::vector <uint8_t> &mover);
    bool process(std::vector<uint8_t> &mover, Timer gameTimer, unsigned short &startTicks);

    void food();

    void putMenuEntities(Position pos);
    void runMenuEntities(std::vector<uint8_t> mover);
    bool isGameWon();
    void resetGame();
    void resetMover(std::vector<uint8_t> &mover);
    
    bool isGameOver;
    Sound mSound;

private:
    Pac mPac;
    Board mBoard;
    class Blinky mBlinky;
    class Pinky mPinky;
    class Inky mInky;
    uint8_t actualMap[BOARD_HEIGHT * BOARD_WIDTH];
    Timer speedUpTime;
    Timer powerUpTime;
    Timer mapAnimationTimer;

    bool flag_0 = false;
    bool flag_1 = false;
    bool flag_2 = false;
    bool flag_3 = false;
};
