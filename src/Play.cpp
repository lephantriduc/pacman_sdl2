#include "Play.hpp"

bool Play::RunMainMenu() {
    mover.push_back(right);

    int volume = MIX_MAX_VOLUME / 2;
    Mix_Volume(-1, volume);
    bool isDragging = false;

    Position pacPos = {150, 169};
    mGame.putMenuEntities(pacPos);

    mGame.mSound.PlayIntro();
    while (1) {
        uint8_t hihi[BOARD_HEIGHT * BOARD_WIDTH];
        mMenu.draw(hihi);

        mGame.runMenuEntities(mover);
        if (!mGame.mSound.IsChannelPlaying(0)) mGame.mSound.PlayIntro();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                       event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseY >= SCREEN_HEIGHT / 2 + 70 &&
                    mouseY <= SCREEN_HEIGHT / 2 + 110) {
                    isDragging = true;
                    if (mouseX <= SCREEN_WIDTH / 2 - 75)
                        volume = 0;
                    else if (mouseX >= SCREEN_WIDTH / 2 + 75)
                        volume = MIX_MAX_VOLUME;
                    else
                        volume = (mouseX - (SCREEN_WIDTH / 2 - 75)) *
                                 MIX_MAX_VOLUME / 150;
                    Mix_Volume(-1, volume);
                }
                if (isMouseOver(startButton, mouseX, mouseY)) {
                    return true;
                } else if (isMouseOver(quitButton, mouseX, mouseY)) {
                    return false;
                }
            } else if (event.type == SDL_MOUSEBUTTONUP &&
                       event.button.button == SDL_BUTTON_LEFT) {
                isDragging = false;
            } else if (event.type == SDL_MOUSEMOTION && isDragging) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= SCREEN_WIDTH / 2 - 75 &&
                    mouseX <= SCREEN_WIDTH / 2 + 75) {
                    volume = (mouseX - (SCREEN_WIDTH / 2 - 75)) *
                             MIX_MAX_VOLUME / 150;
                    Mix_Volume(-1, volume);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        mainMenuText = renderText("PacMan", Font, textColor, renderer);
        startText = renderText("Start", Font, textColor, renderer);
        quitText = renderText("Quit", Font, textColor, renderer);

        mainMenuRect = {SCREEN_WIDTH / 2 - 100, 50, 200, 50};
        startButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 150, 150, 50};
        quitButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, 150, 50};

        SDL_RenderCopy(renderer, mainMenuText, nullptr, &mainMenuRect);
        SDL_RenderCopy(renderer, startText, nullptr, &startButton);
        SDL_RenderCopy(renderer, quitText, nullptr, &quitButton);

        SDL_RenderPresent(renderer);
        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
        SDL_RenderClear(renderer);

        // Delete old volume
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        clearRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 50,
                              SCREEN_WIDTH, 30};
        SDL_RenderFillRect(renderer, &clearRect);
        clearRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 70 + 15, 150,
                     30};
        SDL_RenderFillRect(renderer, &clearRect);
        SDL_RenderClear(renderer);

        // Create new volume bar
        volumeBorder = {SCREEN_WIDTH / 2 - 76,
                                 SCREEN_HEIGHT / 2 + 69 + 15, 152, 32};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &volumeBorder);
        volumeBar = {SCREEN_WIDTH / 2 - 75,
                              SCREEN_HEIGHT / 2 + 70 + 15,
                              volume * 150 / MIX_MAX_VOLUME, 30};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &volumeBar);

        // Create new volume
        volumeToText.str("");
        volumeToText << "VOLUME: " << (volume * 100 / MIX_MAX_VOLUME) << "%";
        volumeSurface =
            TTF_RenderText_Solid(Font, volumeToText.str().c_str(), textColor);
        volumeText = SDL_CreateTextureFromSurface(renderer, volumeSurface);
        textRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 50,
                             volumeSurface->w, volumeSurface->h};
        SDL_RenderCopy(renderer, volumeText, NULL, &textRect);

        SDL_FreeSurface(volumeSurface);
    }
}

void Play::RunGame() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0, 0, 0, 255);
    SDL_RenderClear(SDL_GetRenderer(window));
    SDL_RenderPresent(SDL_GetRenderer(window));

    mover.clear();
    mover.push_back(right);
    // GameTimer.Start()

    Playing();
}

void Play::DisplayChoices(bool WinOrLose) {
    SDL_RenderClear(renderer);
    std::string name = WinOrLose ? "Play" : "Try";
    playAgainText = renderText(name + " Again", Font, Yellow, renderer);
    quitGameText = renderText("Quit", Font, Yellow, renderer);

    playAgainButton = {10 * BLOCK_SIZE_24 + (WinOrLose ? -5 : 5), 20 * BLOCK_SIZE_24, 20 * (WinOrLose ? 10 : 9),
                       BLOCK_SIZE_24};
    quitGameButton = {12 * BLOCK_SIZE_24 + 9, 26 * BLOCK_SIZE_24, 20 * 4, BLOCK_SIZE_24};

    SDL_RenderCopy(renderer, playAgainText, nullptr, &playAgainButton);
    SDL_RenderCopy(renderer, quitGameText, nullptr, &quitGameButton);

    mGame.draw();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Play::Playing() {
    Timer GameTimer;
    static unsigned short startTicks = 4500;

    if(mGame.isGameOver || mGame.isGameWon()){
        SDL_Delay(250);
        DisplayChoices(mGame.isGameWon());
        if(PlayAgain()) mGame.resetGame() , RunGame();
        return;
    }

    if (!mGame.mSound.IsChannelPlaying(7)) mGame.mSound.PlayMusic();
    if (mGame.mSound.IsChannelPlaying(0)) mGame.mSound.StopChannel(0);

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) return;

        if (event.key.state == SDL_PRESSED) {
            if (event.key.keysym.sym == SDLK_RIGHT ||
                event.key.keysym.sym == SDLK_d)
                mover.push_back(right);
            else if (event.key.keysym.sym == SDLK_UP ||
                     event.key.keysym.sym == SDLK_w)
                mover.push_back(up);
            else if (event.key.keysym.sym == SDLK_LEFT ||
                     event.key.keysym.sym == SDLK_a)
                mover.push_back(left);
            else if (event.key.keysym.sym == SDLK_DOWN ||
                     event.key.keysym.sym == SDLK_s)
                mover.push_back(down);
            if (mover.size() > 2) mover.erase(mover.begin() + 1);
        }
    }

    SDL_RenderClear(renderer);

    if (mGame.process(mover, GameTimer, startTicks)) {
        mGame.draw();
        SDL_RenderPresent(renderer);
    }

    Playing();
}

bool Play::PlayAgain() {
    bool isPlayAgain = false;
    bool isQuitGame = false;

    while (!isPlayAgain && !isQuitGame) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuitGame = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (isMouseOver(playAgainButton, mouseX, mouseY)) {
                    isPlayAgain = true;
                } else if (isMouseOver(quitGameButton, mouseX, mouseY)) {
                    isQuitGame = true;
                }
            }
        }
    }

    SDL_RenderClear(renderer);

    return isPlayAgain;
}

