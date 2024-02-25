#include "Board.hpp"

Board::Board() {
    mapTexture.load("assets/Map.png");
    dotTexture.load("assets/Dot.png");
    powerupTexture.load("assets/Powerup.png");
    doorTexture.load("assets/Door.png");

    mapTexture.paint(boardColor);
    this->convertSketch(); // Without converting, dots and powerups aren't properly placed on board
}

Board::~Board() {
    mapTexture.free();
    dotTexture.free();
    powerupTexture.free();
    doorTexture.free();
}

void Board::convertSketch() {
    for(unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++){
        switch(CharBoard[i]){
            case '#':
                NumericBoard[i] = Objects::wall;
            break;
            case '=':
                NumericBoard[i] = Objects::door;
            break;
            case '.':
                NumericBoard[i] = Objects::dot;
            break;
            case 'o':
                NumericBoard[i] = Objects::powerup;
            break;
            default:
                NumericBoard[i] = Objects::space;
            break;
        }
    }
}

void Board::draw(unsigned char ActualMap[]) {
    mapTexture.render();

    doorTexture.render(SCREEN_WIDTH/2 - 23, SCREEN_HEIGHT/2 - 57);
    char y = -1;
    for(unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        unsigned char x = i % BOARD_WIDTH;
        if(x == 0) {
            y++;
        }
        if(ActualMap[i] == Objects::dot) {
            dotTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
        if(ActualMap[i] == Objects::powerup) {
            powerupTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
    }
    // constexpr RGB mapColor = {0, 0, 255};
    // mapTexture.paint(mapColor);
}


void Board::copyBoard(unsigned char ActualMap[]) {
    memcpy(ActualMap, NumericBoard, BOARD_HEIGHT * BOARD_WIDTH);
}
