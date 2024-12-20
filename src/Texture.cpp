#include "Texture.hpp"

Texture::Texture() {
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::load(std::string path) {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    //Return success
    mTexture = newTexture;
    return mTexture != nullptr;
}

void Texture::paint(RGB color) {
    SDL_SetTextureColorMod(mTexture, color.r, color.g, color.b);
}

void Texture::render(short x, short y, uint8_t facing, SDL_Rect *clip, int flip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // Render to screen
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, facing * 90.0f, nullptr, (flip == right) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}


void Texture::free() {
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface *textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return mTexture != NULL;
}