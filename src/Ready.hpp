#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>

constexpr uint8_t BOARD_WIDTH = 28;
constexpr uint8_t BOARD_HEIGHT = 36;
constexpr uint8_t BLOCK_SIZE_32 = 32;
constexpr uint8_t BLOCK_SIZE_24 = 24;
constexpr uint16_t SCREEN_WIDTH = BOARD_WIDTH * BLOCK_SIZE_24;
constexpr uint16_t SCREEN_HEIGHT = BOARD_HEIGHT * BLOCK_SIZE_24;

inline SDL_Window* window = nullptr;
inline SDL_Renderer* renderer = nullptr;
inline SDL_Rect* currentAnimation = nullptr;

inline SDL_Color textColor = {255 , 255 , 255};
inline SDL_Texture* mainMenuText = NULL;
inline SDL_Texture* startText = NULL;
inline SDL_Texture* quitText = NULL;

inline SDL_Rect mainMenuRect , startButton , quitButton;

constexpr uint8_t pacmanFrames = 3;

enum Objects {
    wall,
    door,
    dot,
    powerup,
    space,
};

enum Entities {
    pac,
    redGhost,
    pinkGhost,
    blueGhost,
    orangeGhost,
};

enum Directions {
    up,
    down,
    left,
    right,
};


void openSDL();

inline void InitFrames(const uint8_t TotalFrames, SDL_Rect SpriteClips[], uint8_t CurrentBlockSize){
    unsigned short counter = 0;
    for(unsigned char i = 0; i < TotalFrames; i++){
        SpriteClips[i].x = counter;
        SpriteClips[i].y = 0;
        SpriteClips[i].w = CurrentBlockSize;
        SpriteClips[i].h = CurrentBlockSize;
        counter += CurrentBlockSize;
    }
}

inline SDL_Texture* renderText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
};

inline bool isMouseOver(SDL_Rect button, int mouseX, int mouseY) {
    return mouseX >= button.x && mouseX <= button.x + button.w &&
           mouseY >= button.y && mouseY <= button.y + button.h;
};

void closeSDL();
