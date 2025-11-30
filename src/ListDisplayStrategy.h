#ifndef LISTDISPLAYSTRATEGY_H
#define LISTDISPLAYSTRATEGY_H

#include "DisplayStrategy.h"

class ListDisplayStrategy : public DisplayStrategy {
public:
    ListDisplayStrategy();
    virtual ~ListDisplayStrategy();
    void displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) override;
};

#endif
