#pragma once

#include <memory>
#include <vector>
#include "TspFile.h"
#include "InitialPath.h"
#include <vcclr.h> // Para gcroot




class Manejador {
public:
    Manejador(TspFile& tspFile);
    bool createInitialPath();
    bool createInitialPath2Ptos();
    SatelliteList Manejador::createGreedyPath();
    SatelliteList Manejador::createGreedy2ptosPath();
    void updateDistanceMatrix();
    void sortPointsByDistanceFrom(int index);
    SatelliteList initialPath;
    std::vector<std::vector<int>> distanceMatrix;
    const std::vector<int>* Manejador::getNearestOrdersByOrder(int targetOrder) const;
    std::vector<std::vector<int>> nearestNeighbors;
    TspFile& tspFile_;
    
};
