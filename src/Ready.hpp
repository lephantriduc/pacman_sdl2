#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>

const unsigned int BoardWidth = 28;
const unsigned int BoardHeight = 36;
const unsigned int BlockSize32 = 32;
const unsigned char BlockSize24 = 24;
constexpr int SCREEN_WIDTH = BoardWidth * BlockSize24;
constexpr int SCREEN_HEIGHT = BoardHeight * BlockSize24;

inline SDL_Window* window = NULL;
inline SDL_Renderer* renderer = NULL;

const std::string CharBoard =
    "                            "
    "                            "
    "                            "
    "############################"
    "#............##............#"
    "#.####.#####.##.#####.####.#"
    "#o####.#####.##.#####.####o#"
    "#.####.#####.##.#####.####.#"
    "#..........................#"
    "#.####.##.########.##.####.#"
    "#.####.##.########.##.####.#"
    "#......##....##....##......#"
    "######.##### ## #####.######"
    "     #.##### ## #####.#     "
    "     #.##    1     ##.#     "
    "     #.## ###==### ##.#     "
    "######.## #      # ##.######"
    "      .   #2 3 4 #   .      "
    "######.## #      # ##.######"
    "     #.## ######## ##.#     "
    "     #.##          ##.#     "
    "     #.## ######## ##.#     "
    "######.## ######## ##.######"
    "#............##............#"
    "#.####.#####.##.#####.####.#"
    "#.####.#####.##.#####.####.#"
    "#o..##.......0 .......##..o#"
    "###.##.##.########.##.##.###"
    "###.##.##.########.##.##.###"
    "#......##....##....##......#"
    "#.##########.##.##########.#"
    "#.##########.##.##########.#"
    "#..........................#"
    "############################"
    "                            "
    "                            ";

void openSDL();

void gameLoop();

void closeSDL();