#ifndef IDORDERSTRATEGY_H
#define IDORDERSTRATEGY_H

#include "ConnectionStrategy.h"

class IdOrderStrategy : public ConnectionStrategy {
public:
    IdOrderStrategy();
    virtual ~IdOrderStrategy();
    std::vector<std::shared_ptr<PointComponent>> orderPoints(std::vector<std::shared_ptr<PointComponent>>& points) override;
};

#endif
