#include "Game.hpp"

Game::Game() {
    mBoard.copyBoard(ActualMap);
    isStarted = false;
}

Game::~Game() {

}

void Game::start() {

}

void Game::update() {

}

void Game::draw() {
    mBoard.draw(ActualMap);
}
