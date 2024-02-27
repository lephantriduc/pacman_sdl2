#pragma once

#include "Position.hpp"

class Entity : public Position{
	public:
		Entity(Entities mIdentity);
		unsigned char getIdentity();
		unsigned char getSpeed();

		void move(unsigned char mover);
	private:
		unsigned char identity;
		unsigned char speed;
};
