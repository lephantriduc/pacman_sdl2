#include "Position.hpp"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

int Position::getX() const {
    return this->x;
}

int Position::getY() const {
    return this->y;
}

Position Position::getPosition() const {
    const Position position{this->x, this->y};
    return position;
}

void Position::setX(int newX) {
    this->x = newX;
}

void Position::setY(int newY) {
    this->y = newY;
}

void Position::setPosition(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void Position::setPosition(Position newPos) {
    this->x = newPos.getX();
    this->y = newPos.getY();
}

bool Position::operator==(Position other) const {
    return this->x == other.getX() && this->y == other.getY();
}

