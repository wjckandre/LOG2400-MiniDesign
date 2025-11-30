#ifndef IDDISPLAYSTRATEGY_H
#define IDDISPLAYSTRATEGY_H

#include "DisplayStrategy.h"

class IdDisplayStrategy : public DisplayStrategy {
public:
    IdDisplayStrategy();
    virtual ~IdDisplayStrategy();
    void displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) override;
};

#endif
