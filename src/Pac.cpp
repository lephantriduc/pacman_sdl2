#include "Pac.hpp"

Pac::Pac():Entity(Entities::pac){
	pacmanTexture.load("assets/Pacman.png");

	InitFrames(pacmanFrames,pacmanSpriteAnimation, BLOCK_SIZE_32);
}

Pac::~Pac(){
	pacmanTexture.free();
}

void Pac::updatePosition(std::vector<unsigned char> &mover, unsigned char ActualMap[]){
	for(unsigned char i = 0; i < this->getSpeed(); i++){
            this->updateFrame();
			this->move(mover.at(0));

		if(mover.size() != 1 && mover.at(0) != mover.at(1)){
				this->move(mover.at(1));
				mover.erase(mover.begin());
		}
	}
}

void Pac::draw(){
	currentAnimation = &pacmanSpriteAnimation[currentPacmanFrame / (pacmanFrames * 4)];
	pacmanTexture.render(this->getX() - 4, this->getY() - 4, 0, currentAnimation);
}

void Pac::updateFrame() {
    currentPacmanFrame++;
    if (currentPacmanFrame / (pacmanFrames * 4) >= pacmanFrames) {
        currentPacmanFrame = 0;
    }
}
