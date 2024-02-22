#include "Game.hpp"

Game* game = nullptr;


int main(int argc, const char* argv[]) {
    constexpr int FPS = 60;
    constexpr int frameDelay = 1000 / FPS;


    game = new Game();

    game->init("wee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (game->running()) {
        const Uint32 frameStart = SDL_GetTicks();

        game->handleEvent(); // handle any user input
        game->update(); // update all objects (e.g. positions, etc.)
        game->render(); // render changes to display

        const Uint32 frameTime = SDL_GetTicks() - frameStart;

        // if (frameDelay > frameTime) {
        //     SDL_Delay(frameDelay - frameTime);
        // }
    }

    game->clean();
}
