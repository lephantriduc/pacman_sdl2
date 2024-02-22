#include "Game.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

Game::Game() {
    isRunning = false;
    window = nullptr;
    renderer = nullptr;
}

Game::~Game() {
}

void Game::init(const char* title, const int xPos, const int yPos, const int width, const int height,
                const bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized!\n";

        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if (window) {
            std::cout << "Window created!\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!\n";
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

}

void Game::handleEvent() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
        break;
        default:
            break;
    }
}

void Game::render() const {
    SDL_RenderClear(renderer);

    // update renderer
    SDL_RenderPresent(renderer);
}

void Game::update() {
}

void Game::clean() const {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game Cleaned!\n";
}
