#include "Common.hpp"

void openSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Let's goooooooo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Init();
    Font = TTF_OpenFont("fonts/emulogic.ttf", BLOCK_SIZE_24);
//    LittleFont = TTF_OpenFont("Fonts/VpPixel.ttf", 20);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

    mainMenuText = renderText("pacman", Font, textColor, renderer);
    startText = renderText("Play", Font, textColor, renderer);
    quitText = renderText("Quit", Font, textColor, renderer);
    mapText = renderText("Maps", Font, textColor, renderer);

    mainMenuRect = {SCREEN_WIDTH / 2 - 100, 50, 200, 50};
    startButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 150, 150, 50};
    quitButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, 150, 50};
    mapButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 50, 150, 50};
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}



