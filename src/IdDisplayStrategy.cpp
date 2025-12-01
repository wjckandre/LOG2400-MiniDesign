#include "IdDisplayStrategy.h"
#include "PointComponent.h"
#include "Point.h"
#include "Nuage.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

IdDisplayStrategy::IdDisplayStrategy() {

}

IdDisplayStrategy::~IdDisplayStrategy() {

}

void IdDisplayStrategy::displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) {
    std::vector<std::shared_ptr<Point>> allPoints;

    std::function<void(std::shared_ptr<PointComponent>)> collect;
    collect = [&](std::shared_ptr<PointComponent> c) -> void {
        if (auto p = std::dynamic_pointer_cast<Point>(c)) {
            allPoints.push_back(p);
        } else if (auto n = std::dynamic_pointer_cast<Nuage>(c)) {
            for (auto child : n->getChildren()) {
                collect(child);
            }
        }
    };

    for (auto c : components) collect(c);

    if (allPoints.empty()) return;

    int maxX = 0;
    int maxY = 0;
    for (auto p : allPoints) {
        maxX = std::max(maxX, p->getX());
        maxY = std::max(maxY, p->getY());
    }

    std::vector<std::string> grid(maxY + 1, std::string(maxX + 1, ' '));

    for (auto p : allPoints) {
        int id = p->getId();
        char c = '0' + (id % 10);
        grid[p->getY()][p->getX()] = c;
    }

    for (int y = maxY; y >= 0; --y) {
        std::cout << grid[y] << std::endl;
    }
}
