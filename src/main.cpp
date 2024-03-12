#include "Game.hpp"
#include <cmath>

int main() {
    openSDL();

    MainMenu mMenu;
    Game mGame;

    SDL_Event event;
    bool quit = false;

    std::vector<uint8_t> mover;
    mover.push_back(right);

    int quitState = 0;
    int volume = MIX_MAX_VOLUME / 2;
    Mix_Volume(-1 , volume);
    bool isDragging = false;

    Position pacPos = {150, 169};
    mGame.putMenuEntities(pacPos);

    mGame.mSound.PlayIntro();
    while (!quitState) {
        uint8_t hihi[BOARD_HEIGHT * BOARD_WIDTH];
        mMenu.draw(hihi);

        mGame.runMenuEntities(mover);
        if(!mGame.mSound.IsChannelPlaying(0)) mGame.mSound.PlayIntro();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitState = 2;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseY >= SCREEN_HEIGHT / 2 + 70 && mouseY <= SCREEN_HEIGHT / 2 + 110) {
                    isDragging = true;
                    if(mouseX <= SCREEN_WIDTH / 2 - 75) volume = 0;
                    else if(mouseX >= SCREEN_WIDTH / 2 + 75) volume = MIX_MAX_VOLUME;
                    else volume = (mouseX - (SCREEN_WIDTH / 2 - 75)) * MIX_MAX_VOLUME / 150;
                    Mix_Volume(-1, volume);
                }
                if (isMouseOver(startButton, mouseX, mouseY)) {
                    quitState = 1;
                }
                else if (isMouseOver(quitButton, mouseX, mouseY)) {
                    quitState = 2;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                isDragging = false;
            }
            else if (event.type == SDL_MOUSEMOTION && isDragging) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= SCREEN_WIDTH / 2 - 75 && mouseX <= SCREEN_WIDTH / 2 + 75) {
                    volume = (mouseX - (SCREEN_WIDTH / 2 - 75)) * MIX_MAX_VOLUME / 150;
                    Mix_Volume(-1, volume);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        mainMenuText = renderText("Main Menu", Font, textColor, renderer);
        startText = renderText("Start", Font, textColor, renderer);
        quitText = renderText("Quit", Font, textColor, renderer);

        mainMenuRect = { SCREEN_WIDTH / 2 - 100, 50, 200, 50 };
        startButton = { SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 150, 150, 50 };
        quitButton = { SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, 150, 50 };

        SDL_RenderCopy(renderer, mainMenuText, nullptr, &mainMenuRect);
        SDL_RenderCopy(renderer, startText, nullptr, &startButton);
        SDL_RenderCopy(renderer, quitText, nullptr, &quitButton);

        SDL_RenderPresent(renderer);
        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
        SDL_RenderClear(renderer);


        // Delete old volume
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect clearRect = { SCREEN_WIDTH / 2 - 75 , SCREEN_HEIGHT / 2 + 50, SCREEN_WIDTH , 30 };
        SDL_RenderFillRect(renderer, &clearRect);
        clearRect = { SCREEN_WIDTH / 2 - 75 , SCREEN_HEIGHT / 2 + 70 + 15, 150, 30 };
        SDL_RenderFillRect(renderer, &clearRect);
        SDL_RenderClear(renderer);


        // Create new volume bar
        SDL_Rect volumeBorder = { SCREEN_WIDTH / 2 - 76, SCREEN_HEIGHT / 2 + 69 + 15, 152, 32 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &volumeBorder);
        SDL_Rect volumeBar = { SCREEN_WIDTH / 2 - 75 , SCREEN_HEIGHT / 2 + 70 + 15, volume * 150 / MIX_MAX_VOLUME, 30 };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &volumeBar);

        // Create new volume
        volumeToText.str("");
        volumeToText << "VOLUME: " << (volume * 100 / MIX_MAX_VOLUME) << "%";
        volumeSurface = TTF_RenderText_Solid(Font, volumeToText.str().c_str(), textColor);
        volumeText = SDL_CreateTextureFromSurface(renderer, volumeSurface);
        SDL_Rect textRect = { SCREEN_WIDTH / 2 - 75 , SCREEN_HEIGHT / 2 + 50 , volumeSurface->w, volumeSurface->h };
        SDL_RenderCopy(renderer, volumeText, NULL, &textRect);

        SDL_FreeSurface(volumeSurface);
    }

    if(quitState == 2)
    {
        closeSDL();
        return 0;
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0, 0, 0, 255);
    SDL_RenderClear(SDL_GetRenderer(window));
    SDL_RenderPresent(SDL_GetRenderer(window));


    mover.clear();
    mover.push_back(right);
    quitState = 2;
    SDL_Delay(250);
    while (!quit && quitState == 2) {
        if(!mGame.mSound.IsChannelPlaying(7)) mGame.mSound.PlayMusic();
        if (mGame.mSound.IsChannelPlaying(0)) mGame.mSound.StopChannel(0);

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

        SDL_RenderClear(renderer);

        if (mGame.process(mover)) {
            mGame.draw();
            SDL_RenderPresent(renderer);
        }
    }

    closeSDL();
}