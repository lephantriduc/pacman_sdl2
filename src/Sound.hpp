#pragma once

#include <SDL_mixer.h>

class Sound{
public:
    Sound();
    ~Sound();
    void PlayIntro(){Mix_PlayChannel(0, Intro, 0);}
    void PlayPacDeath(){Mix_PlayChannel(3, PacDeath, 0);}
    void PlayEating();
    void StopEating();
    void PlayMusic(){Mix_PlayChannel(7 , Music, -1);}
    bool IsChannelPlaying(int channel);
    void StopChannel(int channel);
private:
    Mix_Chunk* Intro;
    Mix_Chunk* ExtraLife;
    Mix_Chunk* PacDeath;
    Mix_Chunk* Eating;
    Mix_Chunk* Music;
};
