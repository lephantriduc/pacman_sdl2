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

void Game::update(std::vector<unsigned char> &mover) {
    this->updatePositions(mover);
}

void Game::updatePositions(std::vector <unsigned char> &mover){
    mPac.updatePosition(mover, ActualMap);
}

bool Game::process(std::vector<unsigned char> &mover){
    if (!gameStarted) {
        this->start();
        gameStarted = true;
    }
    this->update(mover);

    return true;
}

