#include "Common.hpp"

void openSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Init();
    Font = TTF_OpenFont("fonts/emulogic.ttf", BLOCK_SIZE_24);
//    LittleFont = TTF_OpenFont("Fonts/VpPixel.ttf", 20);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

    mainMenuText = renderText("pacman", Font, Yellow, renderer);
    playText = renderText("Play", Font, textColor, renderer);
    quitText = renderText("Quit", Font, textColor, renderer);
    mapText = renderText("Maps", Font, textColor, renderer);
    AuthorText = renderText("This is our first", Font, textColor, renderer);
    AuthorText1 = renderText("collaborative game", Font, textColor, renderer);

    mainMenuRect = {SCREEN_WIDTH / 2 - 150, 20, 300, 80};
    playButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 150, 150, 50};
    quitButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 + 50, 150, 50};
    mapButton = {SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, 150, 50};
    AuthorRect = {109, 740, 180, 20};
    AuthorRect1 = {390, 740, 180, 20};

    int scale = 2;

    OkText = renderText("Ok", Font, textColor, renderer);
    OkButton = {SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 2 + 300, 30, 30};

    Map[0] = IMG_Load("assets/Map0.png");
    Map[1] = IMG_Load("assets/Map1.png");
    Map[2] = IMG_Load("assets/Map2.png");
    Map[3] = IMG_Load("assets/Map3.png");
    SDL_Surface *Next = IMG_Load("assets/Next.png");
    SDL_Surface *Prev = IMG_Load("assets/Previous.png");

    for (int i = 0; i < 4; i++) {
        Surface[i] = SDL_CreateRGBSurface(0, Map[i]->w / scale, Map[i]->h / scale, 32, 0, 0, 0, 0);
        SDL_BlitScaled(Map[i], nullptr, Surface[i], nullptr);
    }

    dstRect = {SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4,
               Surface[0]->w, Surface[0]->h};
    NextRect = {SCREEN_WIDTH - 80, SCREEN_HEIGHT / 2 - 14, 40, 28};
    PrevRect = {40, SCREEN_HEIGHT / 2 - 14, 40, 28};


    NextTexture = SDL_CreateTextureFromSurface(renderer, Next);
    PrevTexture = SDL_CreateTextureFromSurface(renderer, Prev);
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}



