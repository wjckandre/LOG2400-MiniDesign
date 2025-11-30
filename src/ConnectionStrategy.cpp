#include "ConnectionStrategy.h"
#include "PointComponent.h"

ConnectionStrategy::ConnectionStrategy() {

}

ConnectionStrategy::~ConnectionStrategy() {

}

std::vector<std::shared_ptr<PointComponent>> ConnectionStrategy::orderPoints(std::vector<std::shared_ptr<PointComponent>>& points) {
    (void)points;
    return std::vector<std::shared_ptr<PointComponent>>();
}
