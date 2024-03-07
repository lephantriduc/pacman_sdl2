#pragma once

#include "Position.hpp"

class Entity : public Position{
	public:
		Entity(Entities mIdentity);
		uint8_t getIdentity();
        uint8_t getSpeed();

		void move(uint8_t mover);
        uint8_t getFacing();
        void setFacing(uint8_t mFacing);
        void goToOtherSideOfScreen();

	private:
        uint8_t identity;
        uint8_t speed;
        uint8_t facing;
};
