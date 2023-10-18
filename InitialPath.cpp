#include "pch.h"
#include "InitialPath.h"
#include <cmath>
#include <limits>
#include <random> // Necesario para la generación de números aleatorios
#include <chrono>




SatelliteList InitialPath::tspGreedy(std::vector<Point2D>& points) {

    std::vector<bool> visited(points.size(), false);
    std::vector<Point2D> pointsGreedy;
    // Generar un índice aleatorio para el punto de partida
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count() +
        (std::mt19937::result_type)
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()
            ).count());

    std::mt19937 gen(seed);

    std::uniform_int_distribution<> distrib(0, points.size() - 1);
    int current = distrib(gen); // Comenzamos en un punto aleatorio

    pointsGreedy.push_back(points.at(current)); // Agrega el punto inicial a pointsGreedy

    for (int i = 0; i < points.size(); ++i) {
        visited[current] = true;

        int minDist = std::numeric_limits<int>::max();
        int closest = -1;

        for (int j = 0; j < points.size(); ++j) {
            if (visited[j]) continue;

            int dist = points[current].distanceTo(points[j]);
            if (dist < minDist) {
                minDist = dist;
                closest = j;
            }
        }

        if (closest != -1) { // Asegúrate de que no haya un valor inválido
            pointsGreedy.push_back(points.at(closest));
            current = closest;
        }
    }

    // Agrega cualquier punto restante no visitado si es necesario
    for (int i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            pointsGreedy.push_back(points.at(i));
        }
    }

    SatelliteList tour;
    tour.addPoints(pointsGreedy);

    return tour;
}





SatelliteList InitialPath::tspGreedy2Ptos(std::vector<Point2D>& points) {
    std::vector<Point2D> pointsGreedy;
    std::vector<bool> visited(points.size(), false);

    // Generar un índice aleatorio para el punto de partida
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, points.size() - 1);
    int current = distrib(gen); // Comenzamos en un punto aleatorio

    pointsGreedy.push_back(points.at(current)); // Agrega el punto inicial a pointsGreedy

    for (int i = 0; i < points.size() - 1; ++i) {
        visited[current] = true;

        double minDist = std::numeric_limits<double>::max();
        double secondMinDist = std::numeric_limits<double>::max();
        int closest = -1;
        int secondClosest = -1;

        for (int j = 0; j < points.size(); ++j) {
            if (visited[j]) continue;

            double dist = points[current].distanceTo(points[j]);
            if (dist < minDist) {
                secondMinDist = minDist;
                secondClosest = closest;
                minDist = dist;
                closest = j;
            }
            else if (dist < secondMinDist) {
                secondMinDist = dist;
                secondClosest = j;
            }
        }

        // Probabilidad del 80% para el más cercano, 20% para el segundo más cercano
        std::uniform_real_distribution<> prob(0, 1);
        if (prob(gen) < 0.8 || secondClosest == -1) {
            current = closest;
        }
        else {
            current = secondClosest;
        }

        if (current != -1) { // Asegúrate de que no haya un valor inválido
            pointsGreedy.push_back(points.at(current));
        }
    }

    SatelliteList tour;
    tour.addPoints(pointsGreedy);
    return tour;
}


