#pragma once

#include "Entity.hpp"

class Pac : public Entity{
	public:
		Pac();
		~Pac();
		void updatePosition(std::vector<unsigned char> &mover, unsigned char ActualMap[]);
		void draw();
	private:
		TextureManager pacmanTexture;

};
