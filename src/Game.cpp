#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(actualMap);
    isGameOver = false;
    mPac.setLiving(true);
    Ready.loadFromRenderedText("Ready?", Yellow);
}

Game::~Game() {
    Ready.free();
}

void Game::start() {
    mBoard.resetPosition(mPac);
    mBoard.resetPosition(mBlinky);
    mBoard.resetPosition(mPinky);
    mBoard.resetPosition(mInky);
    mBoard.resetPosition(mClyde);
    ghostTime.restart();
    ghostTime.start();
    isChasing = true;
    ghostTimeLimit = chaseTime;
    Ready.render(11 * 24, 20 * 24 - 5);
}

void Game::setMap(int clicks) {
    mBoard.setMap(clicks);
    mBoard.copyBoard(actualMap);
}

void Game::draw() {
    mBoard.drawScore();
    mBoard.drawHighScore();
    mBoard.draw(actualMap);
    mBlinky.draw(mPac);
    mPinky.draw(mPac);
    mInky.draw(mPac);
    mClyde.draw(mPac);
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
    this->food();
    this->chaseTimer();

    if (mPac.isColliding(mBlinky) || mPac.isColliding(mPinky) || mPac.isColliding(mInky) || mPac.isColliding(mClyde)) {
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
            if (mPac.isColliding(mInky)) {
                mInky.setLiving(false);
                if (!flag_2) mBoard.increaseScore(500);
                flag_2 = true;
            }
            if (mPac.isColliding(mClyde)) {
                mClyde.setLiving(false);
                if (!flag_3) mBoard.increaseScore(500);
                flag_3 = true;
            }
        }
    }

    // Flags to avoid counting eating ghosts score too much
    if (mBlinky.isHome()) flag_0 = false;
    if (mPinky.isHome()) flag_1 = false;
    if (mInky.isHome()) flag_2 = false;
    if (mClyde.isHome()) flag_3 = false;
}

void Game::updatePositions(std::vector<uint8_t> &mover) {
    mBlinky.updatePos(actualMap, mPac, {0, 0}, false, isChasing);
    mPinky.updatePos(actualMap, mPac, {0, 0}, false,isChasing);
    mInky.updatePos(actualMap, mPac, mBlinky, false,isChasing);
    mClyde.updatePos(actualMap, mPac, {0, 0}, false,isChasing);
    mPac.updatePosition(mover, actualMap);
}

bool Game::process(std::vector<uint8_t> &mover, Timer& gameTimer, unsigned short &startTicks) {
    if (gameTimer.getTicks() < startTicks || !gameStarted) {
        if (!gameStarted) gameTimer.restart();
        gameStarted = true;
        this->start();
    } else {
        if (mPac.getLiving()) {
            this->update(mover);
        } else { // If Pac is ded
            if (mBoard.getLives() > 1) { // If Pac is ded but still have lives
                if (mPac.getPacDoneDying()) { // Wait for death animation to finish before resetting
                    this->resetMover(mover); // Make Pac facing right every reset
                    startTicks = 2000;
                    mPac.setPacDoneDying(false);
                    mPac.setLiving(true);
                    mBoard.decreaseLives();
                    mPac.setFacing(right);
                    gameStarted = false;
                    gameTimer.reset();
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
            mPac.setPosition(BLOCK_SIZE_24 * 27 - mPac.getX(),BLOCK_SIZE_24 * 36 - mPac.getY());
            break;
        case 5: // Healing perk
            if (mBoard.getLives() < 3) mBoard.increaseLives(), mBoard.increaseScore(200);;
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

bool Game::isGameWon() {
    for (unsigned short i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i++) {
        if (actualMap[i] == Objects::dot)
            return false;
        if (actualMap[i] == Objects::powerUp)
            return false;
    }
    return true;
}

void Game::resetGame() {
    mBoard.copyBoard(actualMap);
    isGameOver = false;
    mPac.setLiving(true);
    mPac.setFacing(right);
    mPac.setPoweredUp(false);

    mBoard.resetPosition(mPac);
    mBoard.resetPosition(mBlinky);
    mBoard.resetPosition(mPinky);
    mBoard.resetPosition(mInky);

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
    mBlinky.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    mBlinky.setFacing(right);
    mBlinky.setDirection(right);

    mPinky.draw(mPac);
    mPinky.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    mPinky.setFacing(right);
    mPinky.setDirection(right);

    mInky.draw(mPac);
    mInky.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    mInky.setFacing(right);
    mInky.setDirection(right);

    mClyde.draw(mPac);
    mClyde.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    mClyde.setFacing(right);
    mClyde.setDirection(right);
}

void Game::putMenuEntities(Position pos) {
    mPac.setPosition(pos);
    mBlinky.setPosition({pos.getX() - 100, pos.getY()});
    mPinky.setPosition(pos.getX() - 150, pos.getY());
    mInky.setPosition(pos.getX() - 200, pos.getY());
    mInky.setPosition(pos.getX() - 200, pos.getY());
    mClyde.setPosition(pos.getX() - 250, pos.getY());
}

void Game::resetMover(std::vector<uint8_t> &mover) {
    mover.clear();
    mover.push_back(right);
}


void Game::chaseTimer() {
    if (ghostTime.getTicks() > ghostTimeLimit) {
        if (ghostTimeLimit == restTime) { // If it is resting
            isChasing = true;
            ghostTimeLimit = chaseTime;
            ghostTime.restart();
        } else if (ghostTimeLimit == chaseTime) { // If it is chasing
            isChasing = false;
            ghostTimeLimit = restTime;
            ghostTime.restart();
        }
    }
}