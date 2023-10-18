#pragma once

class Point2D {
public:
    double x = 0.0;
    double y = 0.0;
    int order = 0;
    Point2D() = default; // Constructor predeterminado
    Point2D(double x, double y, int order);
    int distanceTo(const Point2D& other) const;
};
