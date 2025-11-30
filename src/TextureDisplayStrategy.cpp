#include "TextureDisplayStrategy.h"
#include "PointComponent.h"
#include "Point.h"
#include "Nuage.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

TextureDisplayStrategy::TextureDisplayStrategy() {

}

TextureDisplayStrategy::~TextureDisplayStrategy() {

}

void TextureDisplayStrategy::displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) {
    // Collect all points
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
        std::string t = p->getTexture();
        char c = t.empty() ? '.' : t[0];
        grid[p->getY()][p->getX()] = c;
    }

    // Print upside down or normal?
    // Coordinates usually: (0,0) at bottom-left or top-left?
    // Standard console is top-left (0,0).
    // But math graphs are bottom-left.
    // Given the input (5,0), (14,16)... let's assume standard math coordinates
    // where Y increases upwards. So we print from maxY down to 0.

    for (int y = maxY; y >= 0; --y) {
        std::cout << grid[y] << std::endl;
    }
}
