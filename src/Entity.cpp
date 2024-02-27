#include "Entity.hpp"


Entity::Entity(Entities mIdentity){
	identity = mIdentity;
	speed = 2;
}

unsigned char Entity::getIdentity(){
	return identity;
}

unsigned char Entity::getSpeed(){
	return speed;
}

void Entity::move(unsigned char mover){
	switch(mover){
		case right:
			this->changeX(this->getX() + 1);
			break;
		case up:
			this->changeY(this->getY() - 1);
			break;
		case left:
			this->changeX(this->getX() - 1);
			break;
		case down:
			this->changeY(this->getY() + 1);
			break;
		default:
			break;
	}
}
