#ifndef ORTHESE_H
#define ORTHESE_H

#include "Nuage.h"
#include "Point.h"
#include <vector>

class Orthese {
private:
    std::vector<Point> orderedPoints;
    PointComponent* pointComponent;

public:
    Orthese();
    Orthese(Nuage* nuage, std::vector<Point> orderedPoints);
    virtual ~Orthese();
};

#endif
