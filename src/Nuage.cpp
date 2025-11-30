#include "Nuage.h"
#include <algorithm>

Nuage::Nuage() {

}

Nuage::Nuage(std::string texture, std::vector<Point> points) : texture(texture) {
    for (const auto& p : points) {
        // Create a copy of the point to store in the composite
        // NOTE: In this context, we usually want to move the EXISTING points into the cloud,
        // but `f` command logic will handle the move.
        // This constructor might be used if we create a cloud from scratch copies.
        auto ptr = std::make_shared<Point>(p);
        ptr->setTexture(texture); // Propagate texture
        children.push_back(ptr);
    }
}

Nuage::~Nuage() {

}

void Nuage::add(std::shared_ptr<PointComponent> c) {
    children.push_back(c);
    // Propagate texture if it's a Point
    if (auto p = std::dynamic_pointer_cast<Point>(c)) {
        p->setTexture(this->texture);
    }
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

std::string Nuage::getTexture() const {
    return texture;
}
