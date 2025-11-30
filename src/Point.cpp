#include "Point.h"

Point::Point() : id(0), x(0), y(0) {

}

Point::Point(int id, int x, int y) : id(id), x(x), y(y), texture(".") {

}

Point::~Point() {

}

std::string Point::getPosition() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

void Point::move(int newX, int newY) {
    x = newX;
    y = newY;
}

int Point::getId() const { return id; }
int Point::getX() const { return x; }
int Point::getY() const { return y; }
void Point::setTexture(const std::string& t) { texture = t; }
std::string Point::getTexture() const { return texture; }
