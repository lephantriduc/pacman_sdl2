
#include "Sound.hpp"


Sound::Sound(){
    Intro = Mix_LoadWAV("sounds/Intro.wav");
    ExtraLife = Mix_LoadWAV("sounds/ExtraLife.wav");
    PacDeath = Mix_LoadWAV("sounds/PacDeath.wav");
    Eating = Mix_LoadWAV("sounds/Eating.wav");
    Music = Mix_LoadWAV("sounds/InGameMusic.wav");
    Mix_Volume(-1, 10);
}

Sound::~Sound(){
    Mix_FreeChunk(Intro);
    Mix_FreeChunk(ExtraLife);
    Mix_FreeChunk(PacDeath);
    Mix_FreeChunk(Eating);
    Mix_FreeChunk(Music);
    Intro = nullptr;
    ExtraLife = nullptr;
    PacDeath = nullptr;
    Eating = nullptr;
    Music = nullptr;
}

bool Sound::IsChannelPlaying(int channel) {
    return Mix_Playing(channel) == 1;
}

void Sound::StopChannel(int channel) {
    Mix_HaltChannel(channel);
}

void Sound::PlayEating() {
    Mix_PlayChannel(6, Eating, -1);
}

void Sound::StopEating() {
    Mix_HaltChannel(6);
}

