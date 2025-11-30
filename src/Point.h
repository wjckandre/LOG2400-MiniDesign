#ifndef POINT_H
#define POINT_H

#include "PointComponent.h"
#include <string>

class Point : public PointComponent {
private:
    int id;
    int x;
    int y;
    std::string texture;

public:
    Point();
    Point(int id, int x, int y);
    virtual ~Point();

    std::string getPosition();
    void move(int newX, int newY);
    int getId() const;
    int getX() const;
    int getY() const;
    void setTexture(const std::string& t);
    std::string getTexture() const;
};

#endif
