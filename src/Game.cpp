#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(ActualMap);
}

Game::~Game() {}

void Game::start() {
    mBoard.putEntities(mPac);
}

void Game::draw() {
    mBoard.draw(ActualMap);
    mPac.draw();
}

void Game::update(std::vector<uint8_t> &mover) {
    this->updatePositions(mover);
}

void Game::updatePositions(std::vector <uint8_t> &mover){
    mPac.updatePosition(mover, ActualMap);
}

bool Game::process(std::vector<uint8_t> &mover){
    if (!gameStarted) {
        this->start();
        gameStarted = true;
    }
    this->update(mover);

    return true;
}

