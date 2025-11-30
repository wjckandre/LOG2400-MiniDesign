#ifndef POINT_H
#define POINT_H

#include "PointComponent.h"
#include <string>

class Point : public PointComponent {
private:
    int id;
    int x;
    int y;

public:
    Point();
    Point(int id, int x, int y);
    virtual ~Point();

    std::string getPosition();
    void move(int newX, int newY);
};

#endif
