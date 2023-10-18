#pragma once
#include "SatelliteList.h"


class Opt2 {
public:
    std::pair<SatelliteList, bool>  Opt2::localOpt2(SatelliteList tour, std::vector<std::vector<int>>& nearestNeighbors);
    long getRandonNumber(long cant);
    void Opt2::debug(SatelliteList tour);

};