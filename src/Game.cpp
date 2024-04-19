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
    mBoard.resetPosition(susRed);
    mBoard.resetPosition(susPink);
    mBoard.resetPosition(susGreen);
    mBoard.resetPosition(susBrown);
    impostorTime.restart();
    impostorTime.start();
    isChasing = true;
    impostorTimeLimit = chaseTime;
    deathMusicYetToPlay = true;
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
    susRed.draw(mPac);
    susPink.draw(mPac);
    susGreen.draw(mPac);
    susBrown.draw(mPac);
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
    this->food();
    this->chaseTimer();

    if (mPac.isColliding(susRed) || mPac.isColliding(susPink) || mPac.isColliding(susGreen) || mPac.isColliding(susBrown)) {
        if (!mPac.getPoweredUp()) { // Pac in normal state
            mPac.setFrame(32);
            mPac.setLiving(false); // Commenting this for immortality
            mBoard.decreaseScore(100);
        } else { // Pac is powered up
            if (mPac.isColliding(susRed)) {
                susRed.setLiving(false);
                if (!flag_0) mBoard.increaseScore(500);
                flag_0 = true;
            }
            if (mPac.isColliding(susPink)) {
                susPink.setLiving(false);
                if (!flag_1) mBoard.increaseScore(500);
                flag_1 = true;
            }
            if (mPac.isColliding(susGreen)) {
                susGreen.setLiving(false);
                if (!flag_2) mBoard.increaseScore(500);
                flag_2 = true;
            }
            if (mPac.isColliding(susBrown)) {
                susBrown.setLiving(false);
                if (!flag_3) mBoard.increaseScore(500);
                flag_3 = true;
            }
        }
    }

    // Flags to avoid counting score for eating impostors too many times
    if (susRed.isHome()) flag_0 = false;
    if (susPink.isHome()) flag_1 = false;
    if (susGreen.isHome()) flag_2 = false;
    if (susBrown.isHome()) flag_3 = false;
}

void Game::updatePositions(std::vector<uint8_t> &mover) {
    susRed.updatePos(actualMap, mPac, {0, 0}, false, isChasing);
    susPink.updatePos(actualMap, mPac, {0, 0}, false, isChasing);
    susGreen.updatePos(actualMap, mPac, susRed, false, isChasing);
    susBrown.updatePos(actualMap, mPac, {0, 0}, false, isChasing);
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
            if (mSound.IsChannelPlaying(7)) mSound.StopChannel(7);
            if (deathMusicYetToPlay) {
                mSound.PlayPacDeath();
                deathMusicYetToPlay = false;
            }

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
    int newX, newY;
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
            newX = BLOCK_SIZE_24 * 27 - mPac.getX();
            newY = BLOCK_SIZE_24 * 36 - mPac.getY();

            if (mPac.getFacing() == up || mPac.getFacing() == down) {
                if (abs(newX - 24) < abs(newX - 624)) {
                    newX = 24;
                    if (mPac.getFacing() == up) {
                        newY = 118;
                    }
                } else {
                    newX = 624;
                }
            }
            if (mPac.getFacing() == right || mPac.getFacing() == left) {
                if (abs(newY - 96) < abs(newY - 768)) {
                    newY = 96;
                } else {
                    newY = 768;
                }
            }
            mPac.setPosition(newX, newY);
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

    if (powerUpTime.getTicks() > 7000) {
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
    deathMusicYetToPlay = true;
    mPac.setLiving(true);
    mPac.setFacing(right);
    mPac.setPoweredUp(false);

    mBoard.resetPosition(mPac);
    mBoard.resetPosition(susRed);
    mBoard.resetPosition(susPink);
    mBoard.resetPosition(susGreen);

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

    susRed.draw(mPac);
    susRed.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    susRed.setFacing(right);
    susRed.setDirection(right);

    susPink.draw(mPac);
    susPink.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    susPink.setFacing(right);
    susPink.setDirection(right);

    susGreen.draw(mPac);
    susGreen.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    susGreen.setFacing(right);
    susGreen.setDirection(right);

    susBrown.draw(mPac);
    susBrown.updatePos(actualMap, mPac, {0, 0}, true, isChasing);
    susBrown.setFacing(right);
    susBrown.setDirection(right);
}

void Game::putMenuEntities(Position pos) {
    mPac.setPosition(pos);
    susRed.setPosition({pos.getX() - 100, pos.getY()});
    susPink.setPosition(pos.getX() - 150, pos.getY());
    susGreen.setPosition(pos.getX() - 200, pos.getY());
    susGreen.setPosition(pos.getX() - 200, pos.getY());
    susBrown.setPosition(pos.getX() - 250, pos.getY());
}

void Game::resetMover(std::vector<uint8_t> &mover) {
    mover.clear();
    mover.push_back(right);
}


void Game::chaseTimer() {
    if (impostorTime.getTicks() > impostorTimeLimit) {
        if (impostorTimeLimit == restTime) { // If it is resting
            isChasing = true;
            impostorTimeLimit = chaseTime;
            impostorTime.restart();
        } else if (impostorTimeLimit == chaseTime) { // If it is chasing
            isChasing = false;
            impostorTimeLimit = restTime;
            impostorTime.restart();
        }
    }
}