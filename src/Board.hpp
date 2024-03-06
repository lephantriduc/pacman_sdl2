#pragma once
#include "Pac.hpp"

class Board {
public:
    Board();
    ~Board();
    void convertSketch();
    void draw(uint8_t ActualMap[]);
    void copyBoard(uint8_t ActualMap[]);
    void putEntities(Entity& mEntity);

private:
    TextureManager mapTexture;
    TextureManager dotTexture;
    TextureManager powerupTexture;
    TextureManager doorTexture;
    std::string charBoard;
    uint8_t NumericBoard[BOARD_HEIGHT * BOARD_WIDTH];

    RGB boardColor = {0x00, 0x00, 0xff}; // Blue
};
