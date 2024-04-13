#pragma once

#include "Game.hpp"
#include "Fireworks.hpp"

class Play {
public:
    Play();
    ~Play();
    bool RunMainMenu();
    void RunGame();
    void DisplayChoices(bool hasWon);
    void Playing();
    bool PlayAgain();
    void render();
    bool PauseGame();
    void shootFireworks();

private:
    SDL_Event event;
    Game mGame;
    MainMenu mMenu;
     Timer GameTimer;
    std::vector<unsigned char> mover;
    // unsigned short StartTicks = 4500;
    SDL_Rect volumeBar;
    SDL_Rect textRect;
    SDL_Rect volumeBorder;
    SDL_Rect clearRect;

    Texture ghosty;
    Texture Note;
    Texture Authors;
};