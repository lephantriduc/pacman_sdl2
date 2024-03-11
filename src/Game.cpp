#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(actualMap);
}

Game::~Game() {}

void Game::start() {
    mBoard.putEntities(mPac);
    mBoard.putEntities(mRedGhost);
}

void Game::draw() {
    mBoard.draw(actualMap);
    mRedGhost.draw();
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
}

void Game::updatePositions(std::vector <uint8_t> &mover){
    mRedGhost.updatePos(actualMap, mPac);
    mPac.updatePosition(mover, actualMap);
}

bool Game::process(std::vector<uint8_t> &mover){
    if (!gameStarted) {
        this->start();
        gameStarted = true;
    }
    this->update(mover);

    return true;
}

