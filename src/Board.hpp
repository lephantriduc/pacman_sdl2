#pragma once
#include "Blinky.hpp"

class Board {
public:
    Board();
    ~Board();

    void convertSketch(std::string board);
    void draw(uint8_t ActualMap[]);
    void drawScore();
    void drawHighScore();
    void copyBoard(uint8_t ActualMap[]);
    void resetEntitiesPositions(Entity& entity);
    void resetPosition(Entity& mEntity);

    uint8_t getLives();

    void increaseLives();
    void decreaseLives();
    void increaseScore(int delta);
    void resetScore();
    void resetLives();

private:
    Texture mapTexture;
    Texture dotTexture;
    Texture powerUpTexture;
    Texture doorTexture;
    Texture swiftTexture;
    Texture portal1Texture;
    Texture portal2Texture;
    Texture livesTexture;
    Texture scoreNumberTexture;
    Texture scoreWordTexture;
    Texture highScoreNumberTexture;
    Texture highScoreWordTexture;

    std::string charBoard;
    std::string mainMenuBoard;
    uint8_t numericBoard[BOARD_HEIGHT * BOARD_WIDTH];
    uint8_t Lives = 3;
    unsigned int Score = 0;

    RGB boardColor = {0, 255, 247};
};
