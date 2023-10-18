#pragma once
#include "Point2D.h"
#include "SatelliteList.h"
#include <vector>

class InitialPath {
public:
    static SatelliteList tspGreedy( std::vector<Point2D>& points);
    static SatelliteList tspGreedy2Ptos( std::vector<Point2D>& points);
    

};
