#pragma once

#include "Board.hpp"

class Game {
public:
    Game();
    ~Game();

    void start();
    void update();
    void draw();

private:
    Board mBoard;
    unsigned char ActualMap[BOARD_HEIGHT * BOARD_WIDTH];

    bool isStarted;
};
