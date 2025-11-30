#ifndef DISPLAYSTRATEGY_H
#define DISPLAYSTRATEGY_H

#include <vector>
#include <memory>

class PointComponent;

class DisplayStrategy {
public:
    DisplayStrategy();
    virtual ~DisplayStrategy();
    virtual void displayGrid(std::vector<std::shared_ptr<PointComponent>>& components);
};

#endif
