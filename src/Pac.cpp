#include "Pac.hpp"

Pac::Pac():Entity(Entities::pac){
	pacmanTexture.load("assets/Pacman.png");

	InitFrames(pacmanFrames,pacmanSpriteAnimation, BLOCK_SIZE_32);
}

Pac::~Pac(){
	pacmanTexture.free();
}

void Pac::updatePosition(std::vector<uint8_t> &mover, uint8_t ActualMap[]){
	for(uint8_t i = 0; i < this->getSpeed(); i++){
            this->updateFrame();
			this->move(mover.at(0));
            this->turn(mover.at(0));

		if(mover.size() != 1 && mover.at(0) != mover.at(1)){
				this->move(mover.at(1));
				mover.erase(mover.begin());
		}
	}
    this->goToOtherSideOfScreen();
}

void Pac::draw(){
	currentAnimation = &pacmanSpriteAnimation[currentPacmanFrame / (pacmanFrames * 4)];
	pacmanTexture.render(this->getX() - 4, this->getY() - 4, this->getFacing(), currentAnimation);
}

void Pac::updateFrame() {
    currentPacmanFrame++;
    if (currentPacmanFrame / (pacmanFrames * 4) >= pacmanFrames) {
        currentPacmanFrame = 0;
    }
}

void Pac::turn(uint8_t mover) {
    switch(mover) {
        case right:
            this->setFacing(0);
            break;
        case down:
            this->setFacing(1);
            break;
        case left:
            this->setFacing(2);
            break;
        case up:
            this->setFacing(3);
            break;
        default:
            break;
    }
}
