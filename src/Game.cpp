#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(ActualMap);
}

Game::~Game() {}

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
    this->update(mover);

    return true;
}
