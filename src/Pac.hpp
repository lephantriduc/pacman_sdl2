#pragma once

#include "Entity.hpp"

class Pac : public Entity{
	public:
		Pac();
		~Pac();
		void updatePosition(std::vector<uint8_t> &mover, uint8_t ActualMap[]);
		void draw();
        void updateFrame();
        void turn(uint8_t mover);

	private:
		TextureManager pacmanTexture;
		SDL_Rect pacmanSpriteAnimation[pacmanFrames];
        uint8_t currentPacmanFrame;
};
