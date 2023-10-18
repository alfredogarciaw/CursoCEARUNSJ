#pragma once
#include "SatelliteList.h"
#include "CicloAB.h"
#include "CiclosABGenerator.h"
#include "SatelliteList.h"
#include "TspFile.h"
#include <vector>

class Crossover {
public:
    SatelliteList cruzar( SatelliteList& padre1,  SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors, TspFile tspFile);
    SatelliteList unionDeSegmentos(std::vector<Segmento>& miniToursPadre1, std::vector<std::vector<int>>& nearestNeighbors,TspFile tspFile);
    std::vector<Segmento> getMiniToursPadre1(SatelliteList& padre1, SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors);
    std::vector<Segmento> Crossover::getCiclosAB(SatelliteList& padre1, SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors);



    std::unordered_map<long, long> asociarNodosConCiclos();
    std::unordered_map<long, std::unordered_set<long>> identificarNodosExtremos();
    void asignarIdsACiclos();
    std::vector<CicloAB> identificarCiclos(std::vector<Segmento>& miniToursPadre1);
    void Crossover::conectarCiclosAbiertos( std::vector<std::vector<int>>& nearestNeighbors);
    void Crossover::conectarCiclosCerrados( std::vector<std::vector<int>>& nearestNeighbors);
};
