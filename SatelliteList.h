#pragma once
#include <vector>
#include "Point2D.h"
#include "CicloAB.h"
#include "TspFile.h"
#include <unordered_map>
#include <unordered_set>
#include <functional> // para std::hash

class SatelliteList {
public:
    long cacheFitness = -1;
    Point2D SatelliteList::nextNodo(long nodo);//este es para el numero de nodo cargado en tspfile
    Point2D SatelliteList::previousNodo(long nodo);
   
    
    size_t getHash()  {
        size_t hash_value_forward = 0;
        size_t hash_value_backward = 0;
        std::hash<int> int_hasher;

        long currentIndex = next(mapaNodo_city[0]);
        long initial_Index = currentIndex;  

        do {
            int order_next = mapaCity_nodo[next(currentIndex)];
            hash_value_forward ^= int_hasher(order_next) + 0x9e3779b9 + (hash_value_forward << 6) + (hash_value_forward >> 2);

            int order_prev = mapaCity_nodo[previous(currentIndex)];
            hash_value_backward ^= int_hasher(order_prev) + 0x9e3779b9 + (hash_value_backward << 6) + (hash_value_backward >> 2);

            // Asumo que hay alguna forma de obtener el ID del nodo siguiente
            currentIndex = next(currentIndex);
        } while (currentIndex != initial_Index);

        return hash_value_forward ^ (hash_value_backward << 1);
    }








    std::vector<long> satellites;

    std::unordered_map<long, long> mapaNodo_city;
    std::unordered_map<long, long> mapaCity_nodo;
    std::unordered_map<long, Point2D> mapaNodo_point;
    long next(long city_index);
    long previous(long city_index);
    long city(long satellite_index);
    long complement(long satellite_index);
    void Reverse_Subpath(long city_index_a, long city_index_b, long city_index_c, long city_index_d);
    void addPoints( std::vector<Point2D> points);
    void SatelliteList::addPoints(const CicloAB& ciclo, TspFile tspFile);
    std::vector<Segmento> SatelliteList::divideTourConCiclosAB(const std::vector<CicloAB>& ciclosAB);

    Point2D SatelliteList::getSatelliteNode(long nodo);
    long getFitness();
    SatelliteList SatelliteList::clone();
    void SatelliteList::Reverse_SubpathNodos(long nodoA, long nodoB, long nodoC, long nodoD);
    bool SatelliteList::hayGananciaReverse_SubpathNodos(long a, long b, long c, long d);


  
};


