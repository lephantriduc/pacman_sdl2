#include "Play.hpp"
#include <cmath>

int main() {
    openSDL();

    Play PacMan;
    if (PacMan.RunMainMenu()) PacMan.RunGame();

    closeSDL();
}