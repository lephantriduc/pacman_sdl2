#include "Board.hpp"

Board::Board() {
    map_num = "0";
    std::string assets_path_name = "assets/Map" + map_num + ".png";
    std::string data_path_name = "../data/Map" + map_num + ".txt";
    mapTexture.load(assets_path_name);
    std::ifstream in_file(data_path_name);

    // Read the whole file
    std::stringstream buffer;
    buffer << in_file.rdbuf();
    charBoard = buffer.str();

    // Erase \n characters
    charBoard.erase(std::remove(charBoard.begin(), charBoard.end(), '\n'), charBoard.end());

    dotTexture.load("assets/Dot.png");
    powerUpTexture.load("assets/powerUp.png");
    doorTexture.load("assets/Door.png");
    swiftTexture.load("assets/Lightning.png");
    portal1Texture.load("assets/Portal1.png");
    portal2Texture.load("assets/Portal2.png");
    healTexture.load("assets/Heart.png");
    livesTexture.load("assets/PacLives.png");

    scoreWordTexture.loadFromRenderedText("Score", White);
    highScoreWordTexture.loadFromRenderedText("High Score", White);


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
    healTexture.free();
    scoreWordTexture.free();
    highScoreWordTexture.free();
    scoreNumberTexture.free();
    highScoreNumberTexture.free();
}

void Board::setMap(int clicks) {
    int r = clicks % 4;
    map_num = std::to_string(r);

    std::string assets_path_name = "assets/Map" + map_num + ".png";
    std::string data_path_name = "../data/Map" + map_num + ".txt";
    mapTexture.load(assets_path_name);
    std::ifstream in_file(data_path_name);

    // Read the whole file
    std::stringstream buffer;
    buffer << in_file.rdbuf();
    charBoard = buffer.str();

    // Erase \n characters
    charBoard.erase(std::remove(charBoard.begin(), charBoard.end(), '\n'), charBoard.end());

    mapTexture.paint(boardColor);
    this->convertSketch(charBoard);

    this->makeGraph(charBoard);
}

void Board::convertSketch(std::string board) {
    if (map_num != "3") {
        std::vector<int> pos;
        for (unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
            if (board[i] == '.') pos.push_back(i);
        }

        std::shuffle(pos.begin(), pos.end(), std::mt19937(std::random_device()()));
        for (int i = 0; i < 4; i++) board[pos[i]] = 'o';
        for (int i = 4; i < 6; i++) board[pos[i]] = '!';
        for (int i = 6; i < 7; i++) board[pos[i]] = 'h';
        pos.clear();
    }

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
            case 'h':
                numericBoard[i] = Objects::heal;
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

void Board::drawHighScore() {
    unsigned int highscore;
    std::stringstream ss;
    std::ifstream in_file("../data/Highscore.txt");
    in_file >> highscore;
    if (!in_file.is_open()) {
        std::cout << "Could not open input file!!!\n";
    }
    if (Score > highscore) {
        highscore = Score;
        std::ofstream out_file("../data/Highscore.txt");
        if (!out_file.is_open()) {
            std::cout << "Could not open output file!!!\n";
        }
        out_file << std::to_string(highscore);
    }
    in_file.close();
    ss << highscore;
    highScoreNumberTexture.loadFromRenderedText(ss.str(), White);
}


void Board::draw(uint8_t ActualMap[]) {
    mapTexture.render();

    scoreWordTexture.render();
    highScoreWordTexture.render(400);
    scoreNumberTexture.render(0, 32);
    highScoreNumberTexture.render(400, 32);

    doorTexture.render(SCREEN_WIDTH / 2 - 23, SCREEN_HEIGHT / 2 - 57);
    char y = -1;

    for (unsigned short i = 0; i < Lives; i++) {
        livesTexture.render(i * (BLOCK_SIZE_32 + 10) + 10, 825);
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
        if (ActualMap[i] == Objects::heal) {
            healTexture.render(x * BLOCK_SIZE_24, y * BLOCK_SIZE_24);
        }
    }
}

void Board::copyBoard(uint8_t ActualMap[]) {
    memcpy(ActualMap, numericBoard, BOARD_HEIGHT * BOARD_WIDTH);
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
        if (charBoard[i] == '1' && mEntity.getIdentity() == Entities::SusRed) {
            mEntity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            mEntity.setY(y * BLOCK_SIZE_24);
            return;
        }
        if (charBoard[i] == '2' && mEntity.getIdentity() == Entities::SusPink) {
            mEntity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            mEntity.setY(y * BLOCK_SIZE_24);
            return;
        }
        if (charBoard[i] == '3' && mEntity.getIdentity() == Entities::SusGreen) {
            mEntity.setX(x * BLOCK_SIZE_24 + BLOCK_SIZE_24 / 2);
            mEntity.setY(y * BLOCK_SIZE_24);
            return;
        }
        if (charBoard[i] == '4' && mEntity.getIdentity() == Entities::SusBrown) {
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

void Board::decreaseScore(int delta) {
    if (Score < delta) {
        Score = 0;
    } else {
        Score -= delta;
    }
}


void Board::makeGraph(std::string CharBoard) {
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++) {
        if (CharBoard[i] != '#') {
                if (i % BOARD_WIDTH != BOARD_WIDTH - 1 && CharBoard[i + 1] != '#') g[i].push_back(i + 1);
                if (i % BOARD_WIDTH != 0 && CharBoard[i - 1] != '#') g[i].push_back(i - 1);
                if (i / BOARD_WIDTH != BOARD_HEIGHT - 1 && CharBoard[i + BOARD_WIDTH] != '#') g[i].push_back(i + BOARD_WIDTH);
                if (i > 23 && CharBoard[i - BOARD_WIDTH] != '#') g[i].push_back(i - BOARD_WIDTH);
            }
    }
}