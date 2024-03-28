#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

constexpr uint8_t BOARD_WIDTH = 28;
constexpr uint8_t BOARD_HEIGHT = 36;
constexpr uint8_t BLOCK_SIZE_32 = 32;
constexpr uint8_t BLOCK_SIZE_24 = 24;
constexpr uint16_t SCREEN_WIDTH = BOARD_WIDTH * BLOCK_SIZE_24;
constexpr uint16_t SCREEN_HEIGHT = BOARD_HEIGHT * BLOCK_SIZE_24;

inline SDL_Window* window = nullptr;
inline SDL_Renderer* renderer = nullptr;
inline SDL_Rect* currentClip = nullptr;

inline SDL_Color textColor = {255 , 255 , 255};
inline SDL_Texture* mainMenuText = nullptr;
inline SDL_Texture* startText = nullptr;
inline SDL_Texture* quitText = nullptr;
inline SDL_Texture* playAgainText = nullptr;
inline SDL_Texture* quitGameText = nullptr;

inline SDL_Surface* volumeSurface = nullptr;
inline SDL_Texture* volumeText = nullptr;
inline std::stringstream volumeToText;
inline TTF_Font* Font = TTF_OpenFont("fonts/emulogic.ttf", BLOCK_SIZE_24);

inline SDL_Rect mainMenuRect , startButton , quitButton, playAgainButton, quitGameButton;

static bool gameStarted = false;

constexpr uint8_t pacmanFrames = 3;
constexpr uint8_t deathFrames = 10;
constexpr uint8_t ghostFrames = 6;
constexpr uint8_t ghostEyesFrames = 5;

enum Objects {
    wall,
    door,
    dot,
    powerUp,
    swift,
    space,
    portal1,
    portal2,
};

enum Entities {
    pac,
    redGhost,
    pinkGhost,
    blueGhost,
    orangeGhost,
};

enum Directions {
    right,
    up,
    left,
    down,
};

const SDL_Color Red = {0xff, 0x00, 0x00};
const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};


void openSDL();

inline void InitFrames(const uint8_t TotalFrames, SDL_Rect SpriteClips[], uint8_t CurrentBlockSize = BLOCK_SIZE_32){
    unsigned short counter = 0;
    for(uint8_t i = 0; i < TotalFrames; i++){
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
}

inline bool isMouseOver(SDL_Rect button, int mouseX, int mouseY) {
    return mouseX >= button.x && mouseX <= button.x + button.w &&
           mouseY >= button.y && mouseY <= button.y + button.h;
} 

void closeSDL();

void DisPlayChoices(bool WinOrLose);