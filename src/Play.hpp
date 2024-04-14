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
    void renderFireworks();
    bool PauseGame();
    void shootFireworks();

private:
    SDL_Event event;
    Game mGame;
    MainMenu mMenu;
    Timer GameTimer;
    std::vector<unsigned char> mover;
    SDL_Rect volumeBar;
    SDL_Rect textRect;
    SDL_Rect volumeBorder;
    SDL_Rect clearRect;
    Texture AreYouScaredGhost;
    Texture Note;
    Texture Authors;
};