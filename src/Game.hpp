#pragma once

#include "Board.hpp"

class Game {
public:
    Game();
    ~Game();

    void start();
    void draw();
    void update(std::vector<uint8_t> &mover);
    void updatePositions(std::vector <uint8_t> &mover);
    bool process(std::vector<uint8_t> &mover);


private:
    Board mBoard;
    Pac mPac;
    uint8_t ActualMap[BOARD_HEIGHT * BOARD_WIDTH];

};
