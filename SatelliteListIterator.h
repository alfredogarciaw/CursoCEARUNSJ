#ifndef SATELLITELISTITERATOR_H
#define SATELLITELISTITERATOR_H

#include "Point2D.h"
#include "SatelliteList.h"

class SatelliteListIterator {
private:
    SatelliteList* satelliteList;
    long currentIndex;
    bool isStart;
    long cantIteraciones = 0;

public:
    // Constructor
    SatelliteListIterator(SatelliteList* list);

    // Verificar si hay un siguiente elemento en la lista
    bool hasNext();

    // Obtener el siguiente elemento de la lista
    Point2D next();
};

#endif // SATELLITELISTITERATOR_H

