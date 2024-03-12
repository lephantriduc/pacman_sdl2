#pragma once

#include "Board.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"

class Game {
public:
    Game();
    ~Game();

    void start();
    void draw();
    void update(std::vector<uint8_t> &mover);
    void updatePositions(std::vector <uint8_t> &mover);
    bool process(std::vector<uint8_t> &mover);

    void putMenuEntities(Position pos);
    void runMenuEntities(std::vector<uint8_t> mover);
    Sound mSound;

private:
    Pac mPac;
    Board mBoard;
    Blinky mBlinky;
    uint8_t actualMap[BOARD_HEIGHT * BOARD_WIDTH];

};
