#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(actualMap);
    isGameOver = false;
    mPac.setLiving(true);
}

Game::~Game() {}

void Game::start() {
    mBoard.resetEntitiesPositions(mPac);
    mBoard.resetEntitiesPositions(mBlinky);
    mBoard.resetEntitiesPositions(mPinky);
}

void Game::draw() {
    mBoard.drawScore();
    mBoard.drawHighScore();
    mBoard.draw(actualMap);
    mBlinky.draw(mPac);
    mPinky.draw(mPac);
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
    this->food();

    if (mPac.isColliding(mBlinky) || mPac.isColliding(mPinky)) {
        if (!mPac.getPoweredUp()) { // Pac in normal state
            mPac.setFrame(32);
            mPac.setLiving(false);
            mBoard.decreaseScore(100);
        } else { // Pac is powered up
            if (mPac.isColliding(mBlinky)) {
                mBlinky.setLiving(false);
                if (!flag_0) mBoard.increaseScore(500);
                flag_0 = true;
            }
            if (mPac.isColliding(mPinky)) {
                mPinky.setLiving(false);
                if (!flag_1) mBoard.increaseScore(500);
                flag_1 = true;
            }
        }
    }

    // Flags to avoid counting eating ghosts score too much
    if (mBlinky.isHome()) flag_0 = false;
    if (mPinky.isHome()) flag_1 = false;

}

void Game::updatePositions(std::vector<uint8_t> &mover) {
    mBlinky.updatePos(actualMap, mPac, false);
    mPinky.updatePos(actualMap, mPac, false);
    mPac.updatePosition(mover, actualMap);
}

bool Game::process(std::vector<uint8_t> &mover, Timer gameTimer, unsigned short &startTicks) {
    if (!gameStarted) {
        this->start();
        gameStarted = true;
    }
    if (mPac.getLiving()) {
        this->update(mover);
    } else { // If Pac is ded
        if (mBoard.getLives() > 1) { // If Pac is ded but still have lives
            if (mPac.getPacDoneDying()) { // Wait for death animation to finish before resetting
                mPac.setPacDoneDying(false);
                mBoard.decreaseLives();
                mPac.setLiving(true);
                gameStarted = false;
                this->resetMover(mover); // Make Pac facing right every reset
                return false;
            }
        } else { // If Pac is ded but no lives remaining
            if (mPac.getPacDoneDying()) {
                mPac.setPacDoneDying(false);
                mBoard.decreaseLives();
                isGameOver = true;
            }
        }
    }

    return true;
}

void Game::food() {
    switch (mPac.foodCollision(actualMap)) {
        case 1: // Dot
            mBoard.increaseScore(10);
            break;
        case 2: // PowerUp
            mPac.setPoweredUp(true);
            mBoard.increaseScore(100);
            powerUpTime.restart();
            break;
        case 3: // Speed perk
            mBoard.increaseScore(20);
            mPac.setSpeed(3);
            speedUpTime.restart();
            break;
        case 4: // Teleport perk
            mPac.setX(BLOCK_SIZE_24 * 27 - mPac.getX());
            mPac.setY(BLOCK_SIZE_24 * 36 - mPac.getY());
            break;
        case 5: // Healing perk
            mBoard.increaseLives();
            mBoard.increaseScore(200);
            break;
        default:
            break;
    }
    if (speedUpTime.getTicks() > 5000) {
        mPac.setSpeed(2);
        speedUpTime.reset();
    }

    if (powerUpTime.getTicks() > 5000) {
        mPac.setPoweredUp(false);
        powerUpTime.reset();
    }
}

bool Game::isGameWon(){
	for(unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++){
		if(actualMap[i] == Objects::dot)
			return false;
		if(actualMap[i] == Objects::powerUp)
			return false;
	}
	return true;
}

void Game::resetGame() {
    mBoard.copyBoard(actualMap);
    isGameOver = false;
    mPac.setLiving(true);
    mPac.setFacing(right);
    mBlinky.setFacing(right);
    mPinky.setFacing(right);

    mBoard.resetPosition(mPac);
    mBoard.resetPosition(mBlinky);
    mBoard.resetPosition(mPinky);

    mBoard.resetScore();
    mBoard.resetLives();

    SDL_RenderClear(renderer);
}

void Game::runMenuEntities(std::vector<uint8_t> mover) {
    if (mover.size()) mover.clear();
    mover.push_back(right);
    mover.push_back(right);
    mPac.draw();
    mPac.updateFrame();
    mPac.updatePosition(mover);
    mPac.setFacing(right);

    mBlinky.draw(mPac);
    mBlinky.updatePos(actualMap, mPac, true);
    mBlinky.setFacing(right);
    mBlinky.setDirection(right);

    mPinky.draw(mPac);
    mPinky.updatePos(actualMap, mPac, true);
    mPinky.setFacing(right);
    mPinky.setDirection(right);
}

void Game::putMenuEntities(Position pos) {
    mPac.setPosition(pos);
    mBlinky.setDirection(right);
    mBlinky.setPosition({pos.getX() - 100, pos.getY()});
    mPinky.setPosition(pos.getX() - 150, pos.getY());
}

void Game::resetMover(std::vector<uint8_t> &mover) {
    mover.clear();
    mover.push_back(right);
}
