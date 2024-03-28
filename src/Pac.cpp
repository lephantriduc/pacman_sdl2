#include "Pac.hpp"

Pac::Pac():Entity(Entities::pac){
	pacmanTexture.load("assets/Pacman.png");
    deathTexture.load("assets/DeathPac.png");

	InitFrames(pacmanFrames, pacmanSpriteClips, BLOCK_SIZE_32);
    InitFrames(deathFrames, deathSpriteClips, BLOCK_SIZE_32);

    currentPacmanFrame = 0;
    currentDeathFrame = 0;
}

Pac::~Pac(){
	pacmanTexture.free();
    deathTexture.free();
}

void Pac::updatePosition(std::vector<uint8_t> &mover, uint8_t ActualMap[]){
	for(uint8_t i = 0; i < this->getSpeed(); i++){
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
            this->setFrame(32);
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
    this->checkIfGoesOutOfScreen(false);
}

void Pac::draw(){
    if (this->getLiving()) {
        currentClip = &pacmanSpriteClips[currentPacmanFrame / (pacmanFrames * 4)];
        pacmanTexture.render(this->getX() - 4, this->getY() - 4, this->getFacing(), currentClip);
    } else {
        currentClip = &deathSpriteClips[currentDeathFrame / deathFrames];
        deathTexture.render(this->getX() - 4, this->getY() - 4, this->getFacing(), currentClip);
        currentDeathFrame++;
        if (currentDeathFrame / deathFrames >= deathFrames){
            currentDeathFrame = 0;
            setPacDoneDying(true);
        }
        std::cout << currentDeathFrame << '\n';
    }
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

void Pac::updatePosition(std::vector<uint8_t> &mover) {
    for(uint8_t i = 0; i < this->getSpeed(); i++){
        this->updateFrame();
        this->move(mover.at(0));
        this->turn(mover.at(0));

        mover.erase(mover.begin());
    }
    this->checkIfGoesOutOfScreen(false);
}

uint8_t Pac::foodCollision(uint8_t ActualMap[]) {
    float cell_x = this->getX() / static_cast<float>(BLOCK_SIZE_24);
    float cell_y = this->getY() / static_cast<float>(BLOCK_SIZE_24);
    Position BoardPos;
    for (uint8_t sideDir = 0; sideDir < 4; sideDir++) {
        this->CharBoardPos(sideDir, BoardPos, cell_x, cell_y);
        if (ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] == Objects::dot) {
            ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] = Objects::space;
            return 1;
        }
        if (ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] == Objects::powerup) {
            ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] = Objects::space;
            return 2;
        }
        if (ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] == Objects::swift) {
            ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] = Objects::space;
            return 3;
        }
        if (ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] == Objects::portal1) {
            return 4;
        }
        if (ActualMap[BOARD_WIDTH * BoardPos.getY() + BoardPos.getX()] == Objects::portal2) {
            return 4;
        }
    }

    return 0;
}

void Pac::setFrame(uint8_t newFrame) {
    currentPacmanFrame = newFrame;
}

bool Pac::getPacDoneDying() {
    return isPacDoneDying;
}

void Pac::setPacDoneDying(bool answer) {
    isPacDoneDying = answer;
}
