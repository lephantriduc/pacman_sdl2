#include "Ready.hpp"

void openSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("I hope you are having a good day. Enjoy the game!", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
}
