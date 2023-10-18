#pragma once
#include <vector>
#include "SatelliteList.h"

class Poblacion {
    

public:
    long cantIndividuos = 20;
    std::vector<SatelliteList> tours;
    std::unordered_set<size_t> hashSet;

    std::pair<SatelliteList, SatelliteList> seleccion();
    bool insertar(SatelliteList tour);
    bool eliminar(SatelliteList tour);
    void Poblacion::eliminarPeores();
    SatelliteList Poblacion::mejorIndividuo();
};