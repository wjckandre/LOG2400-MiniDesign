#include "Nuage.h"
#include <algorithm>

Nuage::Nuage() {

}

Nuage::Nuage(std::string texture, std::vector<Point> points) : texture(texture) {
    for (const auto& p : points) {
        // Create a copy of the point to store in the composite
        children.push_back(std::make_shared<Point>(p));
    }
}

Nuage::~Nuage() {

}

void Nuage::add(std::shared_ptr<PointComponent> c) {
    children.push_back(c);
}

void Nuage::remove(std::shared_ptr<PointComponent> c) {
    auto it = std::remove(children.begin(), children.end(), c);
    if (it != children.end()) {
        children.erase(it, children.end());
    }
}

std::vector<std::shared_ptr<PointComponent>> Nuage::getChildren() {
    return children;
}

Nuage* Nuage::getNuage() {
    return this;
}

void Nuage::getPoints(std::vector<Point>& points) {
    for (const auto& child : children) {
        // Check if child is a Point
        auto p = std::dynamic_pointer_cast<Point>(child);
        if (p) {
            points.push_back(*p);
        }
        // Check if child is a Nuage (recursive)
        auto n = std::dynamic_pointer_cast<Nuage>(child);
        if (n) {
            n->getPoints(points);
        }
    }
}
