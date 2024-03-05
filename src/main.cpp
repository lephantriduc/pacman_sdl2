#include "Game.hpp"

int main(int argc, const char* argv[]) {
    openSDL();

    // gameLoop;
    Game mGame;

    SDL_Event event;
    bool quit = false;

    std::vector<unsigned char> mover;
    mover.push_back(right);

    int quitState = 0;
//    while (!quitState && !quit) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
//                int mouseX, mouseY;
//                SDL_GetMouseState(&mouseX, &mouseY);
//                if (isMouseOver(startButton, mouseX, mouseY)) {
//                    SDL_DestroyTexture(mainMenuText);
//                    SDL_DestroyTexture(startText);
//                    SDL_DestroyTexture(quitText);
//                    quitState = 2;
//                }
//                else if (isMouseOver(quitButton, mouseX, mouseY)) {
//                    quitState = 1;
//                }
//            }
//        }
//    }

    quitState = 2;
    while (!quit && quitState == 2) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                quit = true;

            if(event.key.state == SDL_PRESSED){
                if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)  mover.push_back(right);
                else if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w) mover.push_back(up);
                else if(event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)  mover.push_back(left);
                else if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)	mover.push_back(down);
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