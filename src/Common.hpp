#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <utility>
#include <algorithm>
#include <random>

constexpr uint8_t BOARD_WIDTH = 28;
constexpr uint8_t BOARD_HEIGHT = 36;
constexpr uint8_t BLOCK_SIZE_32 = 32;
constexpr uint8_t BLOCK_SIZE_24 = 24;
constexpr uint16_t SCREEN_WIDTH = BOARD_WIDTH * BLOCK_SIZE_24;
constexpr uint16_t SCREEN_HEIGHT = BOARD_HEIGHT * BLOCK_SIZE_24;

inline SDL_Window *window = nullptr;
inline SDL_Renderer *renderer = nullptr;
inline SDL_Rect *currentClip = nullptr;

inline SDL_Color textColor = {255, 255, 255};
inline SDL_Texture *mainMenuText = nullptr;
inline SDL_Texture *playText = nullptr;
inline SDL_Texture *quitText = nullptr;
inline SDL_Texture *gameStatementText = nullptr;
inline SDL_Texture *playAgainText = nullptr;
inline SDL_Texture *quitGameText = nullptr;
inline SDL_Texture *mapText = nullptr;
inline SDL_Texture *volumeText = nullptr;
inline SDL_Texture *OkText = nullptr;
inline SDL_Texture *NextTexture = nullptr;
inline SDL_Texture *PrevTexture = nullptr;
inline SDL_Texture *GamePausedText = nullptr;
inline SDL_Texture *QuitToMenuText = nullptr;
inline SDL_Texture *ContinueText = nullptr;
inline SDL_Texture *RUScaredText = nullptr;
inline SDL_Texture *RUScaredText1 = nullptr;
inline SDL_Texture *NoteText = nullptr;
inline SDL_Texture *NoteText1 = nullptr;
inline SDL_Texture *AuthorText = nullptr;
inline SDL_Texture *AuthorText1 = nullptr;

inline SDL_Rect dstRect;
inline SDL_Rect NextRect;
inline SDL_Rect PrevRect;

inline SDL_Surface *Surface[4];
inline SDL_Surface *Map[4];


inline SDL_Surface *volumeSurface = nullptr;
inline std::stringstream volumeToText;
inline TTF_Font *Font = TTF_OpenFont("fonts/emulogic.ttf", BLOCK_SIZE_24);

inline SDL_Rect mainMenuRect, playButton, quitButton, playAgainButton, quitGameButton, mapButton, OkButton,
        gameStatementRect, PauseRect, PauseBorder, GamePausedRect, ContinueButton, QuitToMenuButton,
        RUScaredRect, RUScaredRect1, NoteRect, NoteRect1, AuthorRect, AuthorRect1;

static bool gameStarted = false;
static unsigned short startTicks = 3000;

constexpr uint8_t pacmanFrames = 3;
constexpr uint8_t deathFrames = 10;
constexpr uint8_t impostorFrames = 4;

inline std::string map_num;
inline int mapClickCount = 0;

inline std::vector<int> g[BOARD_WIDTH * BOARD_HEIGHT];

inline int volume = 50;

enum Objects {
    wall,
    door,
    dot,
    powerUp,
    swift,
    space,
    portal1,
    portal2,
    heal,
};

enum Entities {
    pac,
    SusRed,
    SusPink,
    SusGreen,
    SusBrown,
};

enum Directions {
    right,
    up,
    left,
    down,
};

const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Red = {255, 0, 0};


void openSDL();

inline void InitFrames(const uint8_t TotalFrames, SDL_Rect SpriteClips[], uint8_t CurrentBlockSize = BLOCK_SIZE_32) {
    unsigned short counter = 0;
    for (uint8_t i = 0; i < TotalFrames; i++) {
        SpriteClips[i].x = counter;
        SpriteClips[i].y = 0;
        SpriteClips[i].w = CurrentBlockSize;
        SpriteClips[i].h = CurrentBlockSize;
        counter += CurrentBlockSize;
    }
}

inline SDL_Texture *renderText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Renderer *renderer) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}


inline bool isMouseOver(SDL_Rect button, int mouseX, int mouseY) {
    return mouseX >= button.x && mouseX <= button.x + button.w &&
           mouseY >= button.y && mouseY <= button.y + button.h;
}

void closeSDL();