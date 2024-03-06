#include "Entity.hpp"


Entity::Entity(Entities mIdentity){
	identity = mIdentity;
	speed = 2;
}

uint8_t Entity::getIdentity(){
	return identity;
}

uint8_t Entity::getSpeed(){
	return speed;
}

void Entity::move(uint8_t mover){
	switch(mover){
		case right:
            this->setX(this->getX() + 1);
			break;
		case up:
            this->setY(this->getY() - 1);
			break;
		case left:
            this->setX(this->getX() - 1);
			break;
		case down:
            this->setY(this->getY() + 1);
			break;
		default:
			break;
	}
}

uint8_t Entity::getFacing() {
    return facing;
}

void Entity::setFacing(uint8_t mFacing) {
        this->facing = mFacing;
}

