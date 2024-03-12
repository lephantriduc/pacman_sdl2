#include "Entity.hpp"


Entity::Entity(Entities mIdentity){
	identity = mIdentity;
	speed = 2;
    facing = 0;
}

uint8_t Entity::getIdentity() const{
	return identity;
}

uint8_t Entity::getSpeed() const{
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

uint8_t Entity::getFacing() const {
    return facing;
}

void Entity::setFacing(uint8_t newFacing) {
        this->facing = newFacing;
}

void Entity::checkIfGoesOutOfScreen(bool inMenu) {
    if (this->getX() > SCREEN_WIDTH) {
        if (!inMenu)this->setX(-BLOCK_SIZE_24);
        else {
            this->setY(669);
            this->setDirection((this->getDirection() + 2) % 4);
        }
    }
    if (this->getX() < -BLOCK_SIZE_24) {
        if (!inMenu)this->setX(SCREEN_WIDTH);
        else {
            this->setY(169);
            this->setDirection((this->getDirection() + 2) % 4);
        }
    }
}

void Entity::CharBoardPos(uint8_t SideDir, Position &BoardPos, float cell_x, float cell_y){
    switch(SideDir){
        case 0:
            BoardPos.setX(static_cast<short>(floor(cell_x)));
            BoardPos.setY(static_cast<short>(floor(cell_y)));
            break;
        case 1:
            BoardPos.setX(static_cast<short>(ceil(cell_x)));
            BoardPos.setY(static_cast<short>(floor(cell_y)));
            break;
        case 2:
            BoardPos.setX(static_cast<short>(floor(cell_x)));
            BoardPos.setY(static_cast<short>(ceil(cell_y)));
            break;
        case 3:
            BoardPos.setX(static_cast<short>(ceil(cell_x)));
            BoardPos.setY(static_cast<short>(ceil(cell_y)));
            break;
        default:
            break;
    }
}

bool Entity::wallCollision(short x, short y, uint8_t ActualMap[]){
    float cell_x = x / static_cast<float>(BLOCK_SIZE_24);
    float cell_y = y / static_cast<float>(BLOCK_SIZE_24);
    Position BoardPos;
    for(uint8_t SideDir = 0; SideDir < 4; SideDir++){
        this->CharBoardPos(SideDir, BoardPos, cell_x, cell_y);
        if(Objects::wall == ActualMap[BOARD_WIDTH * BoardPos.getY() + abs(BoardPos.getX() % BOARD_WIDTH)]){
            return true;
        }
    }
    return false;
}

void Entity::getNextPosition(short &x, short &y, uint8_t mover) {
    switch(mover){
        case right:
            x++;
            break;
        case left:
            x--;
            break;
        case down:
            y++;
            break;
        case up:
            y--;
            break;
        default:
            break;
    }
}

uint8_t Entity::getDirection() const {
    return direction;
}

void Entity::setDirection(uint8_t newDirection) {
    direction = newDirection;
}

void Entity::setSpeed(uint8_t newSpeed) {
    speed = newSpeed;
}

