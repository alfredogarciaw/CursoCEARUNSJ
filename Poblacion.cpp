#include "pch.h"
#include "Poblacion.h"
#include <iostream>
#include <vector>
#include <random>
#include <utility>

std::pair<SatelliteList, SatelliteList> Poblacion::seleccion() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tours.size() - 1);

    int index1 = dis(gen);
    int index2 = dis(gen);

    // Asegurarse de que los índices sean distintos
    while (index1 == index2) {
        index2 = dis(gen);
    }

    return std::make_pair(tours[index1], tours[index2]);
}




bool Poblacion::insertar(SatelliteList tour) {
    size_t hash = tour.getHash();
    if (hashSet.find(hash) == hashSet.end()) { // Se asegura que no se repita
        hashSet.insert(hash);

        // Encuentra la posición donde se debe insertar el tour de forma ordenada según getFitness
        size_t pos;
        for (pos = 0; pos < tours.size(); ++pos) {
            if (tour.getFitness() < tours[pos].getFitness()) {
                break;
            }
        }

        // Inserta el tour en la posición encontrada
        tours.insert(tours.begin() + pos, tour);

        return true;
    }
    return false;
}

bool Poblacion::eliminar(SatelliteList tour) {
    size_t hash = tour.getHash();
    if (hashSet.find(hash) == hashSet.end()) {
        return false;
    }

    hashSet.erase(hash);

    for (size_t i = 0; i < tours.size(); ) {
        if (tours[i].getHash() == hash) {
            tours.erase(tours.begin() + i);  // Elimina el elemento actual
        }
        else {
            ++i;  // Avanza al siguiente elemento
        }
    }

    return true;
}


void Poblacion::eliminarPeores() {
    if (tours.size() <= cantIndividuos) {
        return;
    }

    for (size_t i = tours.size() - 1; i >= cantIndividuos; --i) {
        eliminar(tours[i]);
    }
}


SatelliteList Poblacion::mejorIndividuo()  {
    if (tours.empty()) {
        throw std::runtime_error("No hay individuos en la población");
    }
    return tours.front();  // El primer elemento tiene el mejor fitness, dado que está ordenado
}