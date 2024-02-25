#pragma once
#include "TextureManager.hpp"

class Board {
public:
    Board();
    ~Board();
    void convertSketch();
    void draw(unsigned char ActualMap[]);
    void copyBoard(unsigned char ActualMap[]);

private:
    TextureManager mapTexture;
    TextureManager dotTexture;
    TextureManager powerupTexture;
    TextureManager doorTexture;
    unsigned char NumericBoard[BOARD_HEIGHT * BOARD_WIDTH];

    RGB boardColor = {0x00, 0x00, 0xff}; // Blue
};
