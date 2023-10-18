#pragma once

#include "Node.h"
#include <unordered_set>
#include <string>

class TspFile {
private:
    std::vector<Point2D> setCities;
    int maxX;
    int maxY;
    int minX;
    int minY;

public:
    TspFile();
    TspFile(std::string filePath);
    std::vector<Point2D> getSetCities();
    int getMaxX();
    int getMaxY();
    int getMinX();
    int getMinY();
};
