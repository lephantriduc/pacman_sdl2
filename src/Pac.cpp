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
        // Display items in mover vector to screen
        for (uint8_t i : mover) {
            std::string dir;
            switch (i) {
                case 0:
                    dir = "right";
                    break;
                case 1:
                    dir = "up";
                    break;
                case 2:
                    dir = "left";
                    break;
                case 3:
                    dir = "down";
                    break;
                default:
                    break;
            }
//            std::cout << dir << " ";
        }
//        std::cout << '\n';

        // Calculate the potential next step that Pacman is going to take
        short potentialX = this->getX();
        short potentialY = this->getY();
        this->getNextPosition(potentialX, potentialY, mover.at(0));

        if (!wallCollision(potentialX, potentialY, ActualMap)) {
            // If no wall then update Pacman
            this->updateFrame();
            this->move(mover.at(0));
            this->turn(mover.at(0));
        } else {
            // Pacman will have the same sprite for every time hitting wall
            this->currentPacmanFrame = 32;
        }

        // Check if there's another item in mover vector (2 steps ahead in the future)
		if(mover.size() != 1 && mover.at(0) != mover.at(1)){
            // Calculate that future step
            short potentialX = this->getX();
            short potentialY = this->getY();
            this->getNextPosition(potentialX, potentialY, mover.at(1));

            if (!wallCollision(potentialX, potentialY, ActualMap)) {
                // If no wall then proceed to update
                this->updateFrame();
                this->move(mover.at(1));
                this->turn(mover.at(1));

                // Pacman stop doing the current action and proceed to do the next one
                mover.erase(mover.begin());
            }
		}
	}
    // Pacman seamlessly goes from this side of screen to the opposite one
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
