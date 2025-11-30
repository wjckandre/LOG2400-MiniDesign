#ifndef NUAGE_H
#define NUAGE_H

#include "PointComponent.h"
#include "Point.h"
#include <vector>
#include <string>

class Nuage : public PointComponent {
private:
    std::string texture;
    std::vector<std::shared_ptr<PointComponent>> children;

public:
    Nuage();
    Nuage(std::string texture, std::vector<Point> points);
    virtual ~Nuage();

    void add(std::shared_ptr<PointComponent> c);
    void remove(std::shared_ptr<PointComponent> c);
    std::vector<std::shared_ptr<PointComponent>> getChildren();
    Nuage* getNuage();
    void getPoints(std::vector<Point>& points);
};

#endif
