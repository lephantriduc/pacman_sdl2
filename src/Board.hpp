#pragma once
#include "Pac.hpp"

class Board {
public:
    Board();
    ~Board();
    void convertSketch();
    void draw(unsigned char ActualMap[]);
    void copyBoard(unsigned char ActualMap[]);
    void putEntities(Entity& mEntity);

private:
    TextureManager mapTexture;
    TextureManager dotTexture;
    TextureManager powerupTexture;
    TextureManager doorTexture;
    std::string charBoard;
    unsigned char NumericBoard[BOARD_HEIGHT * BOARD_WIDTH];

    RGB boardColor = {0x00, 0x00, 0xff}; // Blue
};
