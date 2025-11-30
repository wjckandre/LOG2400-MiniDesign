#include "ListDisplayStrategy.h"
#include "PointComponent.h"
#include "Point.h"
#include "Nuage.h"
#include <iostream>

ListDisplayStrategy::ListDisplayStrategy() {

}

ListDisplayStrategy::~ListDisplayStrategy() {

}

void ListDisplayStrategy::displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) {
    for (const auto& c : components) {
        if (auto p = std::dynamic_pointer_cast<Point>(c)) {
            std::cout << "Point: ID=" << p->getId()
                      << " " << p->getPosition()
                      << " Texture=" << p->getTexture() << std::endl;
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
            std::cout << "Nuage: Texture=" << n->getTexture() << std::endl;
            auto children = n->getChildren();
            for (const auto& child : children) {
                if (auto cp = std::dynamic_pointer_cast<Point>(child)) {
                    std::cout << "\tPoint: ID=" << cp->getId()
                              << " " << cp->getPosition()
                              << " Texture=" << cp->getTexture() << std::endl;
                }
            }
        }
    }
}
