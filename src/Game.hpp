#ifndef GAME_H
#define GAME_H


#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 640;

class Game {
public:
    Game();

    ~Game();

    static bool isRunning;

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

    void handleEvent();
    void update();
    void render() const;
    void clean() const;
    bool running() const {
        return isRunning;
    };

    static SDL_Event event;
    static SDL_Renderer* renderer;


private:
    SDL_Window* window;
};

#endif //GAME_H
