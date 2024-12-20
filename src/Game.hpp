#pragma once

#include "Board.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"
#include "Timer.hpp"

class Game {
public:
    Game();
    ~Game();

    void start();
    void draw();
    void setMap(int clicks);
    void update(std::vector<uint8_t> &mover);
    void updatePositions(std::vector <uint8_t> &mover);
    bool process(std::vector<uint8_t> &mover, Timer& gameTimer, unsigned short &startTicks);

    void food();

    void putMenuEntities(Position pos);
    void runMenuEntities(std::vector<uint8_t> mover);
    bool isGameWon();
    void resetGame();
    void resetMover(std::vector<uint8_t> &mover);
    void chaseTimer();

    bool isGameOver;
    bool deathMusicYetToPlay;
    Sound mSound;

private:
    Pac mPac;
    Board mBoard;
    class SusRed susRed;
    class SusPink susPink;
    class SusGreen susGreen;
    class SusBrown susBrown;
    uint8_t actualMap[BOARD_HEIGHT * BOARD_WIDTH];
    Timer speedUpTime;
    Timer powerUpTime;
    Timer impostorTime;
    int impostorTimeLimit;
    int chaseTime = 16000;
    int restTime = 4000;
    bool isChasing;
    Texture Ready;

    bool flag_0 = false;
    bool flag_1 = false;
    bool flag_2 = false;
    bool flag_3 = false;
};
