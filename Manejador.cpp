#include "pch.h"
#include "Manejador.h"
#include <algorithm>



Manejador::Manejador(TspFile& tspFile)
  :  tspFile_(tspFile) {
    updateDistanceMatrix();
}

bool Manejador::createInitialPath() {
    // Puede utilizar tspFile_ para obtener los puntos y luego llamar a InitialPath::tspGreedy
    // para calcular el camino inicial.
    std::vector<Point2D> points = tspFile_.getSetCities(); 
    if (points.size() > 2) {
     initialPath = InitialPath::tspGreedy(points);
     return true;
    }


    return false;

}



SatelliteList Manejador::createGreedyPath() {
    // Puede utilizar tspFile_ para obtener los puntos y luego llamar a InitialPath::tspGreedy
    // para calcular el camino inicial.
    std::vector<Point2D> points = tspFile_.getSetCities();
    SatelliteList greedyPath = InitialPath::tspGreedy(points);
    return greedyPath;
}


SatelliteList Manejador::createGreedy2ptosPath() {
    // Puede utilizar tspFile_ para obtener los puntos y luego llamar a InitialPath::tspGreedy
    // para calcular el camino inicial.
    std::vector<Point2D> points = tspFile_.getSetCities();
    SatelliteList greedyPath = InitialPath::tspGreedy2Ptos(points);
    return greedyPath;
}




bool Manejador::createInitialPath2Ptos() {
    // Puede utilizar tspFile_ para obtener los puntos y luego llamar a InitialPath::tspGreedy
    // para calcular el camino inicial.
    std::vector<Point2D> points = tspFile_.getSetCities(); // Asumiendo que hay una función que devuelve un vector de puntos
    if (points.size() > 2) {
        initialPath = InitialPath::tspGreedy2Ptos(points);
        return true;
    }

    return false;
    
}

void Manejador::updateDistanceMatrix() {
    std::vector<Point2D> points = tspFile_.getSetCities(); // Asumiendo que hay una función que devuelve un vector de puntos
    // Matriz para almacenar las distancias
    std::vector<std::vector<int>> distanceMatrix(points.size(), std::vector<int>(points.size()));

    // Llenar la matriz de distancias
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < points.size(); ++j) {
            distanceMatrix[i][j] = points[i].distanceTo(points[j]);
        }
    }

    // Matriz para almacenar los vecinos más cercanos para cada punto
    nearestNeighbors.resize(points.size());

    // Identificar los vecinos más cercanos para cada punto
    for (size_t i = 0; i < points.size(); ++i) {
        std::vector<std::pair<int, size_t>> distances;
        for (size_t j = 0; j < points.size(); ++j) {
            if (i != j) {
                distances.emplace_back(distanceMatrix[i][j], j);
            }
        }
        std::sort(distances.begin(), distances.end());

        for (const auto& pair : distances) {
            int dist = pair.first;
            size_t index = pair.second;
            nearestNeighbors[i].push_back(index);
        }
    }

  


}

  const std::vector<int>* Manejador::getNearestOrdersByOrder(int targetOrder) const {
        if (targetOrder >= 0 && targetOrder < nearestNeighbors.size()) {
            return &nearestNeighbors[targetOrder];
        }
        return nullptr;
    }


