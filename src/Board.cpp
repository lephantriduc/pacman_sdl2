#include "Board.hpp"

Board::Board() {
    mapTexture.load("assets/Map.png");
    dotTexture.load("assets/Dot.png");
    powerupTexture.load("assets/Powerup.png");
    doorTexture.load("assets/Door.png");

    charBoard =
        "                            "
        "                            "
        "                            "
        "############################"
        "#............##............#"
        "#.####.#####.##.#####.####.#"
        "#o####.#####.##.#####.####o#"
        "#.####.#####.##.#####.####.#"
        "#..........................#"
        "#.####.##.########.##.####.#"
        "#.####.##.########.##.####.#"
        "#......##....##....##......#"
        "######.##### ## #####.######"
        "     #.##### ## #####.#     "
        "     #.##    1     ##.#     "
        "     #.## ###==### ##.#     "
        "######.## #      # ##.######"
        "......o   #2 3 4 #   o......"
        "######.## #      # ##.######"
        "     #.## ######## ##.#     "
        "     #.##          ##.#     "
        "     #.## ######## ##.#     "
        "######.## ######## ##.######"
        "#............##............#"
        "#.####.#####.##.#####.####.#"
        "#.####.#####.##.#####.####.#"
        "#o..##.......0 .......##..o#"
        "###.##.##.########.##.##.###"
        "###.##.##.########.##.##.###"
        "#......##....##....##......#"
        "#.##########.##.##########.#"
        "#.##########.##.##########.#"
        "#..........................#"
        "############################"
        "                            "
        "                            ";

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
        switch(charBoard[i]){
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
}


void Board::copyBoard(unsigned char ActualMap[]) {
    memcpy(ActualMap, NumericBoard, BOARD_HEIGHT * BOARD_WIDTH);
}

void Board::putEntities(Entity& entity) {
    int8_t y = -1;

    for (short i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
        uint8_t x = i % BOARD_WIDTH;

        if (x == 0) {
            y++;
        }
        if (charBoard[i] == '0' && entity.getIdentity() == Entities::pac) {
            entity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            entity.setY(y * BLOCK_SIZE_24);
            return;
        }
    }
}
