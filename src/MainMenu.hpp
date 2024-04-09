#pragma once
#include "Entity.hpp"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void draw(uint8_t ActualMap[]);

private:
    Texture mainMenuMapTexture;
    std::string mainMenuBoard;

    RGB menuBarColor = {255, 255, 255};
};

