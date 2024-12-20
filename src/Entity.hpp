#pragma once

#include "Position.hpp"

class Entity : public Position{
	public:
		Entity(Entities mIdentity);
        uint8_t getIdentity() const;
        uint8_t getSpeed() const;
        uint8_t getFacing() const;
        uint8_t getDirection() const;
        bool getLiving();

        void setSpeed(uint8_t newSpeed);
        void setFacing(uint8_t newFacing);
        void setDirection(uint8_t newDirection);
        void setLiving(bool living);

		void move(uint8_t mover);
        void checkIfGoesOutOfScreen(bool inMenu);
        void CharBoardPos(uint8_t SideDir, Position &BoardPos, float cell_x, float cell_y);
        bool wallCollision(short x, short y, uint8_t ActualMap[], bool canUseDoor = false);
        void getNextPosition(short& x, short& y, uint8_t mover);
        bool isColliding(Position other);

private:
        uint8_t identity;
        uint8_t facing;
        uint8_t speed;
        uint8_t direction;

        bool living;
};
