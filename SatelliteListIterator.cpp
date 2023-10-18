#include "pch.h"
#include "SatelliteListIterator.h"
#include <stdexcept>

// Constructor
SatelliteListIterator::SatelliteListIterator(SatelliteList* list)
     {
    satelliteList = list;
    isStart = true;
    currentIndex = satelliteList->mapaNodo_city[0];
}

// Verificar si hay un siguiente elemento en la lista
bool SatelliteListIterator::hasNext() {
    if(cantIteraciones> satelliteList->mapaNodo_city.size()-1) return false;
    return true;
}

// Obtener el siguiente elemento de la lista
Point2D SatelliteListIterator::next() {
    if (!hasNext()) {
        throw std::out_of_range("No more elements");
    }
    cantIteraciones++;

    isStart = false; // Marcar que el iterador ya ha comenzado a iterar

    // Utilizar el método next de SatelliteList
    Point2D node = satelliteList->mapaNodo_point[satelliteList->mapaCity_nodo[currentIndex]];
    currentIndex = satelliteList->next(currentIndex); 
    return node;
}
