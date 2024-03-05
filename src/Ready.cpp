#include "Ready.hpp"

void openSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("I hope you are having a good day. Enjoy the game!", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);

//    TTF_Init();
//    TTF_Font* Font = TTF_OpenFont("fonts/emulogic.ttf", BLOCK_SIZE_24);
//
//    mainMenuText = renderText("Main Menu", Font, textColor, renderer);
//    startText = renderText("Start", Font, textColor, renderer);
//    quitText = renderText("Quit", Font, textColor, renderer);
//
//    mainMenuRect = { SCREEN_WIDTH / 2 - 100, 50, 200, 50 };
//    startButton = { SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, 150, 50 };
//    quitButton = { SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 50, 150, 50 };
//
//    SDL_RenderClear(renderer);
//
//    SDL_RenderCopy(renderer, mainMenuText, nullptr, &mainMenuRect);
//    SDL_RenderCopy(renderer, startText, nullptr, &startButton);
//    SDL_RenderCopy(renderer, quitText, nullptr, &quitButton);
//    SDL_RenderPresent(renderer);

}

// log in acc cua cau vao fork tren may to di to push cho

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}