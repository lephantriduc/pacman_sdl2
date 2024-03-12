#pragma once

#include "Texture.hpp"

class Position {
public:
    Position(int x = 0, int y = 0);
    int getX() const;
    int getY() const;
    Position getPosition() const;
    void setX(int newX);
    void setY(int newY);
    void setPosition(int newX, int newY);
    void setPosition(Position newPos);

    bool operator ==(Position other) const;

private:
    int x;
    int y;
};
