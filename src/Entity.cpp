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

void Entity::setFacing(uint8_t mFacing) {
        this->facing = mFacing;
}

void Entity::goToOtherSideOfScreen() {
    // Entity goes to the opposite side of screen if going out of bound

    // Entity goes to the sides
    if (this->getX() > SCREEN_WIDTH) {
        this->setX(-BLOCK_SIZE_24);
    }
    if (this->getX() < -BLOCK_SIZE_24) {
        this->setX(SCREEN_WIDTH);
    }

    // Entity goes to top or bottom
    if (this->getY() > SCREEN_HEIGHT) {
        this->setY(-BLOCK_SIZE_24);
    }
    if (this->getY() < -BLOCK_SIZE_24) {
        this->setY(SCREEN_HEIGHT);
    }
}

void Entity::CharBoardPos(unsigned char SideDir, Position &BoardPos, float cell_x, float cell_y){
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

bool Entity::wallCollision(short x, short y, unsigned char ActualMap[]){
    float cell_x = x / static_cast<float>(BLOCK_SIZE_24);
    float cell_y = y / static_cast<float>(BLOCK_SIZE_24);
    Position BoardPos;
    for(unsigned char SideDir = 0; SideDir < 4; SideDir++){
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
