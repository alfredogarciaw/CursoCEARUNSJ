#pragma once

#include "Point2D.h"
#include <string>

class Node {
private:
    Point2D point;
public:
    Node(Point2D p);
    Point2D getPoint();
    void setPoint(Point2D p);
    std::string toString();
};
