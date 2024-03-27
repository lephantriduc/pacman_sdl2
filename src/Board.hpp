#pragma once
#include "Blinky.hpp"

class Board {
public:
    Board();
    ~Board();

    void convertSketch(std::string board);
    void draw(uint8_t ActualMap[]);
    void copyBoard(uint8_t ActualMap[]);
    void putEntities(Entity& mEntity);
    void resetPosition(Entity& mEntity);

    void increaseLives();
    void resetScore();
    void resetLives();

private:
    Texture mapTexture;
    Texture dotTexture;
    Texture powerupTexture;
    Texture doorTexture;
    Texture swiftTexture;
    Texture portal1Texture;
    Texture portal2Texture;
    std::string charBoard;
    std::string mainMenuBoard;
    uint8_t numericBoard[BOARD_HEIGHT * BOARD_WIDTH];
    uint8_t Lives = 3;
    short Score = 0;

    RGB boardColor = {0, 255, 247};
};
