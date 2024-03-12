#pragma once
#include "RedGhost.hpp"

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
    uint8_t numericBoard[BOARD_HEIGHT * BOARD_WIDTH];

    RGB boardColor = {0, 255, 247};
};
