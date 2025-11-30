#include "Point.h"

Point::Point() : id(0), x(0), y(0) {

}

Point::Point(int id, int x, int y) : id(id), x(x), y(y) {

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
