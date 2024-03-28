
#include "Sound.hpp"


Sound::Sound(){
    Intro = Mix_LoadWAV("sounds/Intro.wav");
    EatFruit = Mix_LoadWAV("sounds/EatFruit.wav");
    ExtraLife = Mix_LoadWAV("sounds/ExtraLife.wav");
    PacDeath = Mix_LoadWAV("sounds/PacDeath.wav");
    GhostDeath = Mix_LoadWAV("sounds/GhostDeath.wav");
    ScatterGhost = Mix_LoadWAV("sounds/ScatterGhost.wav");
    Waka = Mix_LoadWAV("sounds/Waka.wav");
    Music = Mix_LoadWAV("sounds/InGameMusic.wav");
    Mix_Volume(-1, 10);
}

Sound::~Sound(){
    Mix_FreeChunk(Intro);
    Mix_FreeChunk(EatFruit);
    Mix_FreeChunk(ExtraLife);
    Mix_FreeChunk(PacDeath);
    Mix_FreeChunk(GhostDeath);
    Mix_FreeChunk(ScatterGhost);
    Mix_FreeChunk(Waka);
    Mix_FreeChunk(Music);
    Intro = nullptr;
    EatFruit = nullptr;
    ExtraLife = nullptr;
    PacDeath = nullptr;
    GhostDeath = nullptr;
    ScatterGhost = nullptr;
    Waka = nullptr;
    Music = nullptr;
}

bool Sound::IsChannelPlaying(int channel) {
    return Mix_Playing(channel) == 1;
}

void Sound::StopChannel(int channel) {
    Mix_HaltChannel(channel);
}

