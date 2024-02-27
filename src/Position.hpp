#pragma once

#include "TextureManager.hpp"

class Position {
public:
    Position(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    Position getPos() const;
    void changeX(int newX);
    void changeY(int newY);
    void changeCoordinates(int newX, int newY);

    bool operator ==(Position other) const;

private:
    int x;
    int y;
};
