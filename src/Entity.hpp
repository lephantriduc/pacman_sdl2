#pragma once

#include "Position.hpp"

class Entity : public Position{
	public:
		Entity(Entities mIdentity);
		[[nodiscard]] uint8_t getIdentity() const;
        [[nodiscard]] uint8_t getSpeed() const;

		void move(uint8_t mover);
        [[nodiscard]] uint8_t getFacing() const;
        void setFacing(uint8_t mFacing);
        void goToOtherSideOfScreen();
        void CharBoardPos(unsigned char SideDir, Position &BoardPos, float cell_x, float cell_y);
        bool wallCollision(short x, short y, unsigned char ActualMap[]);
        void getNextPosition(short& x, short& y, uint8_t mover);
        uint8_t getDirection();
        void setDirection(uint8_t newDirection);

private:
        uint8_t identity;
        uint8_t speed;
        uint8_t facing;
        uint8_t direction;
};
