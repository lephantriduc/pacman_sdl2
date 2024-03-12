#pragma once
#include "Entity.hpp"

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    void convertSketch(std::string board);
    void draw(uint8_t ActualMap[]);

private:
    Texture mainMenuMapTexture;
    std::string mainMenuBoard;

    RGB boardColor = {255, 255, 255};
};

