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

}

void Game::draw() {
    mBoard.drawScore();
    mBoard.drawHighScore();
    mBoard.draw(actualMap);
    mBlinky.draw();
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
    this->food();

    if (mPac.isColliding(mBlinky)) {
        mPac.setFrame(32);
        mPac.setLiving(false);
    }
}

void Game::updatePositions(std::vector<uint8_t> &mover) {
    mBlinky.updatePos(actualMap, mPac, 0);
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
        if (mBoard.getLives()) { // If Pac is ded but still have lives
            if (mPac.getPacDoneDying()) { // Wait for death animation to finish before resetting
                mPac.setPacDoneDying(false);
                mBoard.decreaseLives();
                mPac.setLiving(true);
                gameStarted = false;
                this->resetMover(mover); // Make Pac facing right every reset
                return false;
            }
        } else { // If Pac is ded but no lives remaining
            isGameOver = true;
        }
    }

    return true;
}

void Game::food() {
    switch (mPac.foodCollision(actualMap)) {
        case 1:
            mBoard.increaseScore(10);
            break;
        case 2:
            mBoard.increaseScore(100);
            break;
        case 3: // Speed perk
            mBoard.increaseScore(20);
            mPac.setSpeed(3);
            speedUpTime.restart();
            break;
        case 4: // Teleport perk
            mPac.setX(BLOCK_SIZE_24 * 27 - mPac.getX());
            mPac.setY(BLOCK_SIZE_24 * 36 - mPac.getY());
        case 5: // Healing perk
            mBoard.increaseLives();
            break;
        default:
            break;
    }
    if (speedUpTime.getTicks() > 5000) {
        mPac.setSpeed(2);
        speedUpTime.reset();
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

    mBoard.resetPosition(mPac);
    mBoard.resetPosition(mBlinky);

    mBoard.resetScore();
    mBoard.resetLives();

    SDL_RenderClear(renderer);
}

void Game::runMenuEntities(std::vector<uint8_t> mover) {
    mover.push_back(right);
    mPac.draw();
    mPac.updateFrame();
    mPac.updatePosition(mover);

    mBlinky.draw();
    mBlinky.updatePos(actualMap, mPac, 1);
}

void Game::putMenuEntities(Position pos) {
    mPac.setPosition(pos);
    mBlinky.setDirection(right);
    mBlinky.setPosition({pos.getX() - 100, pos.getY()});
}

void Game::resetMover(std::vector<uint8_t> &mover) {
    mover.clear();
    mover.push_back(right);
}
