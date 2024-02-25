#include "Game.hpp"

int main(int argc, const char* argv[]) {
    openSDL();


    // gameLoop;
    Game mGame;

    SDL_Event event;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;
        }

        // Don't forget to clear the renderer
        SDL_RenderClear(renderer);

        mGame.draw();
        SDL_RenderPresent(renderer);
    }

    closeSDL();
}
