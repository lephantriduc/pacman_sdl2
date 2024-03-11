#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Common.hpp"
#include "Structs.hpp"

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    bool load(std::string path);
    void paint(RGB color);
    void render(short x = 0, short y = 0, uint8_t facing = 0, SDL_Rect* clip = NULL);
    void free();

private:
    SDL_Texture* mTexture;
    unsigned short mWidth;
    unsigned short mHeight;
};
