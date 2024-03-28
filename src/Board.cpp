#include "Board.hpp"

Board::Board() {
    mapTexture.load("assets/Map24.png");
    dotTexture.load("assets/Dot.png");
    powerUpTexture.load("assets/powerUp.png");
    doorTexture.load("assets/Door.png");
    swiftTexture.load("assets/Lightning.png");
    portal1Texture.load("assets/Portal1.png");
    portal2Texture.load("assets/Portal2.png");
    livesTexture.load("assets/PacLives.png");

    scoreWordTexture.loadFromRenderedText("Score", White);
    highScoreWordTexture.loadFromRenderedText("High Score", White);

    charBoard =
            "                            "
            "                            "
            "                            "
            "############################"
            "#[...........##...........]#"
            "#.####.#####.##.#####.####.#"
            "#o####.#####.##.#####.####o#"
            "#.####.#####.##.#####.####.#"
            "#............!.............#"
            "#.####.##.########.##.####.#"
            "#.####.##.########.##.####.#"
            "#......##....##....##......#"
            "######.##### ## #####.######"
            "     #.##### ## #####.#     "
            "     #.##    1     ##.#     "
            "     #.## ######## ##.#     "
            "######.## #      # ##.######"
            "......o   #2 3 4 #   o......"
            "######.## #      # ##.######"
            "     #.## ######## ##.#     "
            "     #.##    0     ##.#     "
            "     #.## ######## ##.#     "
            "######.## ######## ##.######"
            "#............##............#"
            "#.####.#####.##.#####.####.#"
            "#.####.#####.##.#####.####.#"
            "#o..##................##..o#"
            "###.##.##.########.##.##.###"
            "###.##.##.########.##.##.###"
            "#......##....##....##......#"
            "#.##########.##.##########.#"
            "#.##########.##.##########.#"
            "#]........................[#"
            "############################"
            "                            "
            "                            ";

//    charBoard = // For testing game over (winning)
//            "                            "
//            "                            "
//            "                            "
//            "############################"
//            "#[           ##           ]#"
//            "# #### ##### ## ##### #### #"
//            "# #### ##### ## ##### #### #"
//            "# #### ##### ## ##### #### #"
//            "#            !             #"
//            "# #### ## ######## ## #### #"
//            "# #### ## ######## ## #### #"
//            "#      ##    ##    ##      #"
//            "###### ##### ## ##### ######"
//            "     # ##### ## ##### #     "
//            "     # ##    1     ## #     "
//            "     # ## ######## ## #     "
//            "###### ## #      # ## ######"
//            "          #2 3 4 #          "
//            "###### ## #      # ## ######"
//            "     # ## ######## ## #     "
//            "     # ##.   0     ## #     "
//            "     # ## ######## ## #     "
//            "###### ## ######## ## ######"
//            "#            ##            #"
//            "# #### ##### ## ##### #### #"
//            "# #### ##### ## ##### #### #"
//            "#   ##                ##   #"
//            "### ## ## ######## ## ## ###"
//            "### ## ## ######## ## ## ###"
//            "#      ##    ##    ##      #"
//            "# ########## ## ########## #"
//            "# ########## ## ########## #"
//            "#]                        [#"
//            "############################"
//            "                            "
//            "                            ";


    mapTexture.paint(boardColor);
    this->convertSketch(charBoard);
}

Board::~Board() {
    mapTexture.free();
    dotTexture.free();
    powerUpTexture.free();
    doorTexture.free();
    swiftTexture.free();
    portal1Texture.free();
    portal2Texture.free();
    livesTexture.free();
    scoreWordTexture.free();
    highScoreWordTexture.free();
    scoreNumberTexture.free();
}

void Board::convertSketch(std::string board) {
    for (unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        switch (board[i]) {
            case '#':
                numericBoard[i] = Objects::wall;
                break;
            case '=':
                numericBoard[i] = Objects::door;
                break;
            case '.':
                numericBoard[i] = Objects::dot;
                break;
            case 'o':
                numericBoard[i] = Objects::powerUp;
                break;
            case '!':
                numericBoard[i] = Objects::swift;
                break;
            case '[':
                numericBoard[i] = Objects::portal1;
                break;
            case ']':
                numericBoard[i] = Objects::portal2;
                break;
            default:
                numericBoard[i] = Objects::space;
                break;
        }
    }
}

void Board::drawScore() {
    std::stringstream ss;
    ss << Score;
    scoreNumberTexture.loadFromRenderedText(ss.str(), White);
}

void Board::draw(uint8_t ActualMap[]) {
    mapTexture.render();

    scoreWordTexture.render();
    highScoreWordTexture.render(300);
    scoreNumberTexture.render(0, 32);
    std::cout << Score << "\n";

    doorTexture.render(SCREEN_WIDTH / 2 - 23, SCREEN_HEIGHT / 2 - 57);
    char y = -1;

    for (unsigned short i = 1; i <= Lives; i++) {
        livesTexture.render(i * BLOCK_SIZE_32, 825);
    }

    for (unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        uint8_t x = i % BOARD_WIDTH;
        if (x == 0) {
            y++;
        }
        if (ActualMap[i] == Objects::dot) {
            dotTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
        if (ActualMap[i] == Objects::powerUp) {
            powerUpTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
        if (ActualMap[i] == Objects::swift) {
            swiftTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
        if (ActualMap[i] == Objects::portal1) {
            portal1Texture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
        if (ActualMap[i] == Objects::portal2) {
            portal2Texture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
    }
}

void Board::copyBoard(uint8_t ActualMap[]) {
    memcpy(ActualMap, numericBoard, BOARD_HEIGHT * BOARD_WIDTH);
}

void Board::resetEntitiesPositions(Entity &entity) {
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
        } else if (charBoard[i] == '1' &&
                   entity.getIdentity() == Entities::redGhost) {
            entity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            entity.setY(y * BLOCK_SIZE_24);
            return;
        }
    }
}

void Board::increaseLives() {
    Lives++;
}

void Board::decreaseLives() {
    Lives--;
}

void Board::resetScore() {
    Score = 0;
}

void Board::resetLives() {
    Lives = 3;
}

void Board::resetPosition(Entity &mEntity) {
    uint8_t y = -1;
    for (unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        uint8_t x = i % BOARD_WIDTH;
        if (x == 0) {
            y++;
        }
        if (charBoard[i] == '0' && mEntity.getIdentity() == Entities::pac) {
            mEntity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            mEntity.setY(y * BLOCK_SIZE_24);
            return;
        }
        if (charBoard[i] == '1' && mEntity.getIdentity() == Entities::redGhost) {
            mEntity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            mEntity.setY(y * BLOCK_SIZE_24);
            return;
        }
    }
}

uint8_t Board::getLives() {
    return Lives;
}

void Board::increaseScore(int delta) {
    Score += delta;
}

