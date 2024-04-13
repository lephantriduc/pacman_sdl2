
#include "Sound.hpp"


Sound::Sound(){
    Intro = Mix_LoadWAV("sounds/Intro.wav");
    PacDeath = Mix_LoadWAV("sounds/PacDeath.wav");
    Music = Mix_LoadWAV("sounds/InGameMusic.wav");
    Mix_Volume(-1, 10);
}

Sound::~Sound(){
    Mix_FreeChunk(Intro);
    Mix_FreeChunk(PacDeath);
    Mix_FreeChunk(Music);
    Intro = nullptr;
    PacDeath = nullptr;
    Music = nullptr;
}

bool Sound::IsChannelPlaying(int channel) {
    return Mix_Playing(channel) == 1;
}

void Sound::StopChannel(int channel) {
    Mix_HaltChannel(channel);
}

void Sound::PlayPacDeath() {
    Mix_PlayChannel(3, PacDeath, 0);
}

void Sound::PlayMusic() {
    Mix_PlayChannel(7 , Music, -1);
}

void Sound::PlayIntro() {
    Mix_PlayChannel(0, Intro, 0);
}


