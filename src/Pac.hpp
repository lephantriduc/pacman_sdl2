#pragma once

#include "Entity.hpp"

class Pac : public Entity{
	public:
		Pac();
		~Pac();
		void updatePosition(std::vector<unsigned char> &mover, unsigned char ActualMap[]);
		void draw();
        void updateFrame();
	private:
		TextureManager pacmanTexture;
		SDL_Rect pacmanSpriteAnimation[pacmanFrames];
        uint8_t currentPacmanFrame;
};
