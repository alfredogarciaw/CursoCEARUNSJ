#include "pch.h"
#include <cmath>
#include "Point2D.h"

Point2D::Point2D(double x, double y, int order) : x(x), y(y), order(order) {}
int Point2D::distanceTo(const Point2D& other) const { // Cambiado a int
    double dx = other.x - x;
    double dy = other.y - y;
    return static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy))); // Redondeo y conversión a int
}