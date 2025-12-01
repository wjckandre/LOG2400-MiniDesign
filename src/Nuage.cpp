#include "Nuage.h"
#include <algorithm>

Nuage::Nuage() {

}

Nuage::Nuage(std::string texture, std::vector<Point> points) : texture(texture) {
    for (const auto& p : points) {
        auto ptr = std::make_shared<Point>(p);
        ptr->setTexture(texture);
        children.push_back(ptr);
    }
}

Nuage::~Nuage() {

}

void Nuage::add(std::shared_ptr<PointComponent> c) {
    children.push_back(c);
    
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
        auto p = std::dynamic_pointer_cast<Point>(child);
        if (p) {
            points.push_back(*p);
        }
        
        auto n = std::dynamic_pointer_cast<Nuage>(child);
        if (n) {
            n->getPoints(points);
        }
    }
}

std::string Nuage::getTexture() const {
    return texture;
}
