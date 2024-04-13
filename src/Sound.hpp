#pragma once

#include <SDL_mixer.h>

class Sound{
public:
    Sound();
    ~Sound();
    void PlayIntro();
    void PlayPacDeath();
    void PlayMusic();
    bool IsChannelPlaying(int channel);
    void StopChannel(int channel);
private:
    Mix_Chunk* Intro;
    Mix_Chunk* ExtraLife;
    Mix_Chunk* PacDeath;
    Mix_Chunk* Eating;
    Mix_Chunk* Music;
};
