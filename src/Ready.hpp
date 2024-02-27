#pragma once

#include <SDL.h>
#include <SDL_image.h>

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
inline SDL_Rect* CurrentClip = nullptr;

const unsigned char LivingPacFrames = 3;


// const std::string CharBoard =

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

void closeSDL();
