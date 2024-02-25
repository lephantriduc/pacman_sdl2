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

enum Objects {
    wall,
    door,
    dot,
    powerup,
    space,
};

void openSDL();

void closeSDL();
