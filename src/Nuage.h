#ifndef NUAGE_H
#define NUAGE_H

#include "PointComponent.h"
#include "Point.h"
#include <vector>
#include <string>

class Nuage : public PointComponent {
private:
    std::vector<Point> points;
    std::string texture;
    std::shared_ptr<PointComponent> m_PointComponent;
    std::vector<std::shared_ptr<PointComponent>> children;

public:
    Nuage();
    Nuage(std::string texture, std::vector<Point> points);
    virtual ~Nuage();

    void add(std::shared_ptr<PointComponent> c);
    std::vector<std::shared_ptr<PointComponent>> getChildren();
    Nuage* getNuage();
    void getPoints(std::vector<Point>& points); // Output parameter or just setter? Java has `getPoints(List<Point> points)` which usually means populate list.
    void remove();
};

#endif
