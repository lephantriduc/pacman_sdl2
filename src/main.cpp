#include "Game.hpp"

int main(int argc, const char* argv[]) {
    openSDL();

    // gameLoop;
    Game mGame;

    SDL_Event event;
    bool quit = false;

    std::vector<unsigned char> mover;
    mover.push_back(right);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;

            if(event.key.state == SDL_PRESSED){
                if(event.key.keysym.sym == SDLK_RIGHT)  mover.push_back(right);
                else if(event.key.keysym.sym == SDLK_UP) mover.push_back(up);
                else if(event.key.keysym.sym == SDLK_LEFT)  mover.push_back(left);
                else if(event.key.keysym.sym == SDLK_DOWN)	mover.push_back(down);
                if(mover.size() > 2)
                    mover.erase(mover.begin() + 1);
            }
        }

        // Don't forget to clear the renderer
        SDL_RenderClear(renderer);

        if (mGame.process(mover)) {
            mGame.draw();
            SDL_RenderPresent(renderer);
        }
    }

    closeSDL();
}
