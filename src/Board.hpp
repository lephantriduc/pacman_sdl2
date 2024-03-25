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

private:
    Texture mapTexture;
    Texture dotTexture;
    Texture powerupTexture;
    Texture doorTexture;
    Texture swiftTexture;
    std::string charBoard;
    std::string mainMenuBoard;
    uint8_t numericBoard[BOARD_HEIGHT * BOARD_WIDTH];

    RGB boardColor = {0, 255, 247};
};
