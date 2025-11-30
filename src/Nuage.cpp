#include "Nuage.h"

Nuage::Nuage() {

}

Nuage::Nuage(std::string texture, std::vector<Point> points) : points(points), texture(texture) {

}

Nuage::~Nuage() {

}

void Nuage::add(std::shared_ptr<PointComponent> c) {
    children.push_back(c);
}

std::vector<std::shared_ptr<PointComponent>> Nuage::getChildren() {
    return children;
}

Nuage* Nuage::getNuage() {
    return nullptr;
}

void Nuage::getPoints(std::vector<Point>& points) {
    points = this->points;
}

void Nuage::remove() {

}
