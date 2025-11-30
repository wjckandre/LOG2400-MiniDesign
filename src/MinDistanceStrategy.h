#ifndef MINDISTANCESTRATEGY_H
#define MINDISTANCESTRATEGY_H

#include "ConnectionStrategy.h"

class MinDistanceStrategy : public ConnectionStrategy {
public:
    MinDistanceStrategy();
    virtual ~MinDistanceStrategy();
    std::vector<std::shared_ptr<PointComponent>> orderPoints(std::vector<std::shared_ptr<PointComponent>>& points) override;
};

#endif
