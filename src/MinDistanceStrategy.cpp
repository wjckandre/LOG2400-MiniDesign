#include "MinDistanceStrategy.h"
#include "Point.h"
#include <cmath>
#include <algorithm>
#include <limits>

MinDistanceStrategy::MinDistanceStrategy() {

}

MinDistanceStrategy::~MinDistanceStrategy() {

}

std::vector<std::shared_ptr<PointComponent>> MinDistanceStrategy::orderPoints(std::vector<std::shared_ptr<PointComponent>>& points) {
    if (points.empty()) return {};

    std::vector<std::shared_ptr<PointComponent>> ordered;
    std::vector<std::shared_ptr<PointComponent>> remaining = points;

    
    auto it = std::min_element(remaining.begin(), remaining.end(), [](const std::shared_ptr<PointComponent>& a, const std::shared_ptr<PointComponent>& b){
         auto pA = std::dynamic_pointer_cast<Point>(a);
         auto pB = std::dynamic_pointer_cast<Point>(b);
         if (pA && pB) return pA->getId() < pB->getId();
         return false;
    });

    std::shared_ptr<PointComponent> current = *it;
    ordered.push_back(current);
    remaining.erase(it);

    while (!remaining.empty()) {
        auto pCurrent = std::dynamic_pointer_cast<Point>(current);
        if (!pCurrent) break;

        auto nearestIt = remaining.end();
        double minDist = std::numeric_limits<double>::max();

        for (auto it2 = remaining.begin(); it2 != remaining.end(); ++it2) {
            auto pCandidate = std::dynamic_pointer_cast<Point>(*it2);
            if (pCandidate) {
                double dist = std::sqrt(std::pow(pCurrent->getX() - pCandidate->getX(), 2) +
                                        std::pow(pCurrent->getY() - pCandidate->getY(), 2));
                if (dist < minDist) {
                    minDist = dist;
                    nearestIt = it2;
                } else if (dist == minDist) {
                     if (pCandidate->getId() < std::dynamic_pointer_cast<Point>(*nearestIt)->getId()) {
                         nearestIt = it2;
                     }
                }
            }
        }

        if (nearestIt != remaining.end()) {
            current = *nearestIt;
            ordered.push_back(current);
            remaining.erase(nearestIt);
        } else {
            break;
        }
    }

    return ordered;
}
