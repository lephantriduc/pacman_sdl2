#pragma once

#include "Game.hpp"

class Play {
   private:
    SDL_Event event;
    Game mGame;
    MainMenu mMenu;
    // Timer GameTimer;
    std::vector<unsigned char> mover;
    // unsigned short StartTicks = 4500;
   public:
    bool RunMainMenu();
//    bool PlayAgain();
    void RunGame();
    void Playing();
};