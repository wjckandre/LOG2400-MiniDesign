#include "IdOrderStrategy.h"
#include "Point.h"
#include <algorithm>

IdOrderStrategy::IdOrderStrategy() {

}

IdOrderStrategy::~IdOrderStrategy() {

}

std::vector<std::shared_ptr<PointComponent>> IdOrderStrategy::orderPoints(std::vector<std::shared_ptr<PointComponent>>& points) {
    std::vector<std::shared_ptr<PointComponent>> result = points;
    std::sort(result.begin(), result.end(), [](const std::shared_ptr<PointComponent>& a, const std::shared_ptr<PointComponent>& b) {
        auto pA = std::dynamic_pointer_cast<Point>(a);
        auto pB = std::dynamic_pointer_cast<Point>(b);
        if (pA && pB) {
            return pA->getId() < pB->getId();
        }
        return false;
    });
    return result;
}
