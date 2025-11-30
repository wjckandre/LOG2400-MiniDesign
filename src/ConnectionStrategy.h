#ifndef CONNECTIONSTRATEGY_H
#define CONNECTIONSTRATEGY_H

#include <vector>
#include <memory>

class PointComponent;

class ConnectionStrategy {
public:
    ConnectionStrategy();
    virtual ~ConnectionStrategy();
    virtual std::vector<std::shared_ptr<PointComponent>> orderPoints(std::vector<std::shared_ptr<PointComponent>>& points);
};

#endif
