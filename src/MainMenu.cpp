#include "MainMenu.hpp"

MainMenu::MainMenu() {
    mainMenuMapTexture.load("assets/MenuMap.png");

    mainMenuMapTexture.paint(boardColor);
}

MainMenu::~MainMenu() {
    mainMenuMapTexture.free();
}

void MainMenu::draw(uint8_t ActualMap[]) {
    mainMenuMapTexture.render();
}
