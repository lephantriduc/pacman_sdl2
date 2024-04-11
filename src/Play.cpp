#include "Play.hpp"

bool Play::RunMainMenu() {
    mover.push_back(right);

//    int volume = MIX_MAX_VOLUME / 10 + 1;
    int volume = 0;
    Mix_Volume(-1, volume);
    bool isDragging = false;

    Position pacPos = {250, 169};
    mGame.putMenuEntities(pacPos);

    mGame.mSound.PlayIntro();
    while (1) {
        uint8_t menuBar[BOARD_HEIGHT * BOARD_WIDTH];
        mMenu.draw(menuBar);

        mGame.runMenuEntities(mover);
        if (!mGame.mSound.IsChannelPlaying(0)) mGame.mSound.PlayIntro();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                       event.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseY >= SCREEN_HEIGHT / 2 + 205 &&
                    mouseY <= SCREEN_HEIGHT / 2 + 235) {
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
                } else if (isMouseOver(mapButton, mouseX, mouseY)) {
                    int Quit = 0;
                    while (!Quit) {
                        if (!mGame.mSound.IsChannelPlaying(0)) mGame.mSound.PlayIntro();
                        while (SDL_PollEvent(&event) != 0) {
                            if (event.type == SDL_QUIT) {
                                Quit = 1;
                            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                                SDL_GetMouseState(&mouseX, &mouseY);
                                if (isMouseOver(OkButton, mouseX, mouseY)) {
                                    Quit = 1;
                                } else if (isMouseOver(PrevRect, mouseX, mouseY)) {
                                    for (int i = 2; i >= 0; i--) std::swap(Surface[i], Surface[i + 1]);
                                    mapClickCount += 3;
                                } else if (isMouseOver(NextRect, mouseX, mouseY)) {
                                    for (int i = 0; i < 3; i++) std::swap(Surface[i], Surface[i + 1]);
                                    mapClickCount++;
                                }
                            }
                        }
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        SDL_RenderClear(renderer);
                        SDL_Texture *MapTexture = SDL_CreateTextureFromSurface(renderer, Surface[0]);

                        SDL_RenderCopy(renderer, mainMenuText, nullptr, &mainMenuRect);
                        SDL_RenderCopy(renderer, MapTexture, nullptr, &dstRect);
                        SDL_RenderCopy(renderer, OkText, nullptr, &OkButton);
                        SDL_RenderCopy(renderer, NextTexture, nullptr, &NextRect);
                        SDL_RenderCopy(renderer, PrevTexture, nullptr, &PrevRect);
                        SDL_RenderPresent(renderer);
                    }
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

        SDL_RenderCopy(renderer, mainMenuText, nullptr, &mainMenuRect);
        SDL_RenderCopy(renderer, startText, nullptr, &startButton);
        SDL_RenderCopy(renderer, quitText, nullptr, &quitButton);
        SDL_RenderCopy(renderer, mapText, nullptr, &mapButton);

        SDL_RenderPresent(renderer);
        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
        SDL_RenderClear(renderer);

        // Delete old volume
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        clearRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 160,
                     SCREEN_WIDTH, 30};
        SDL_RenderFillRect(renderer, &clearRect);
        clearRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 190, 150,
                     30};
        SDL_RenderFillRect(renderer, &clearRect);
        SDL_RenderClear(renderer);

        // Create new volume bar
        volumeBorder = {SCREEN_WIDTH / 2 - 76,
                        SCREEN_HEIGHT / 2 + 189 + 15, 152, 32};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &volumeBorder);
        volumeBar = {SCREEN_WIDTH / 2 - 75,
                     SCREEN_HEIGHT / 2 + 190 + 15,
                     volume * 150 / MIX_MAX_VOLUME, 30};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &volumeBar);

        // Create new volume
        volumeToText.str("");
        volumeToText << "VOLUME: " << (volume * 100 / MIX_MAX_VOLUME) << "%";
        volumeSurface =
                TTF_RenderText_Solid(Font, volumeToText.str().c_str(), textColor);
        volumeText = SDL_CreateTextureFromSurface(renderer, volumeSurface);
        textRect = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 160,
                    volumeSurface->w, volumeSurface->h};
        SDL_RenderCopy(renderer, volumeText, nullptr, &textRect);

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
    mGame.start();
    // GameTimer.Start()
    mGame.setMap(mapClickCount);

    Playing();
}

void Play::DisplayChoices(bool hasWon) {
    SDL_RenderClear(renderer);
    std::string name = hasWon ? "Victory <3" : "Defeat :(";
    gameStatementText = renderText(name, Font, hasWon ? Yellow : Red, renderer);
    playAgainText = renderText("Play Again", Font, Yellow, renderer);
    quitGameText = renderText("Back To Menu", Font, Yellow, renderer);

    gameStatementRect = { 11 * BLOCK_SIZE_24 - 31, 14 * BLOCK_SIZE_24, 200, BLOCK_SIZE_24};
    playAgainButton = {10 * BLOCK_SIZE_24 + (hasWon ? -5 : 5), 20 * BLOCK_SIZE_24, 20 * (hasWon ? 10 : 9),
                       BLOCK_SIZE_24};
    quitGameButton = {9 * BLOCK_SIZE_24, 26 * BLOCK_SIZE_24, 20 * 12, BLOCK_SIZE_24};

    SDL_RenderCopy(renderer, playAgainText, nullptr, &playAgainButton);
    SDL_RenderCopy(renderer, quitGameText, nullptr, &quitGameButton);
    SDL_RenderCopy(renderer, gameStatementText, nullptr, &gameStatementRect );

    mGame.draw();
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void Play::Playing() {
    Timer GameTimer;
    static unsigned short startTicks = 4500;

    if (mGame.isGameOver || mGame.isGameWon()) {
        DisplayChoices(mGame.isGameWon());
        mGame.resetGame();
        if (PlayAgain()) RunGame();
        else if (RunMainMenu()) RunGame();
        return;
    }

    if (!mGame.mSound.IsChannelPlaying(7)) mGame.mSound.PlayMusic();
    if (mGame.mSound.IsChannelPlaying(0)) mGame.mSound.StopChannel(0);

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) return;

        if (event.key.state == SDL_PRESSED) {
            if(event.key.keysym.sym == SDLK_SPACE)
                if(!PauseGame()) {
                    mGame.resetGame();
                    if(RunMainMenu()) RunGame();
                    return;
                }
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

void Play::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto &fw: fireworks) {
        SDL_SetRenderDrawColor(renderer, fw.r, fw.g, fw.b, fw.a);
        SDL_RenderDrawPoint(renderer, fw.x, fw.y);
    }

    for (const auto &p: particles) {
        SDL_SetRenderDrawColor(renderer, p.r, p.g, p.b, p.a);
        SDL_Rect rect = {(int) p.x, (int) p.y, p.size, p.size};
        SDL_RenderFillRect(renderer, &rect);
    }

    mGame.draw();
    DisplayChoices(mGame.isGameWon());
    SDL_RenderPresent(renderer);
}

void Play::shootFireworks() {
    for (int j = 0; j < 8; ++j) {
        createFirework(SCREEN_WIDTH / 2 + (rand() % 201 - 100), SCREEN_HEIGHT / 2 + (rand() % 401 - 300));
        int delay = 0;
        while (delay++ <= 30) {
            update();
            render();
            SDL_Delay(10);
        }
    }
    while (!particles.empty()) {
        update();
        render();
        SDL_Delay(10);
    }
}
