#ifndef TEXTUREDISPLAYSTRATEGY_H
#define TEXTUREDISPLAYSTRATEGY_H

#include "DisplayStrategy.h"

class TextureDisplayStrategy : public DisplayStrategy {
public:
    TextureDisplayStrategy();
    virtual ~TextureDisplayStrategy();
    void displayGrid(std::vector<std::shared_ptr<PointComponent>>& components) override;
};

#endif
