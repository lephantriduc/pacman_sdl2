#pragma once

#include "Board.hpp"

class Game {
public:
    Game();
    ~Game();

    void draw();
    void update(std::vector<unsigned char> &mover);
    void updatePositions(std::vector <unsigned char> &mover);
    bool process(std::vector<unsigned char> &mover);

private:
    Board mBoard;
    Pac mPac;
    unsigned char ActualMap[BOARD_HEIGHT * BOARD_WIDTH];

};
