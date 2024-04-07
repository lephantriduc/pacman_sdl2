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
    uint8_t actualMap[BOARD_HEIGHT * BOARD_WIDTH];
    Timer speedUpTime;
    Timer powerUpTime;
    Timer mapAnimationTimer;
    int ghostsEaten;

    bool flag_0 = false;
    bool flag_1 = false;
};
