#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(actualMap);
    isGameOver = false;
}

Game::~Game() {}

void Game::start() {
    mBoard.putEntities(mPac);
    mBoard.putEntities(mBlinky);
}

void Game::draw() {
    mBoard.draw(actualMap);
    mBlinky.draw();
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
    this->food();

    if (mPac.isColliding(mBlinky)) {
        std::cout << "Colliding\n";
        isGameOver = true;
    }

    if (isGameOver) {
        std::cout << "Game Over\n";
    }
}

void Game::updatePositions(std::vector<uint8_t> &mover) {
    mBlinky.updatePos(actualMap, mPac, 0);
    mPac.updatePosition(mover, actualMap);
}

bool Game::process(std::vector<uint8_t> &mover) {
    if (!gameStarted) {
        this->start();
        gameStarted = true;
    } else if (!isGameOver){
        this->update(mover);
    } else {
        return false;
    }

    return true;
}

void Game::food() {
    switch (mPac.foodCollision(actualMap)) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            mPac.setSpeed(4);
            speedUpTime.restart();
            break;
        default:
            break;
    }
    if (speedUpTime.getTicks() > 50000) {
        mPac.setSpeed(2);
        speedUpTime.reset();
    }
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
