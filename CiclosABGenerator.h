#pragma once
#include <vector>
#include "CicloAB.h"
#include "SatelliteList.h"
#include <unordered_set>


class CiclosABGenerator {
public:
    struct SegmentoSelected {
        Segmento segmento;
        bool cerrado=false;
    };

    std::vector<CicloAB> CiclosABGenerator::generarCiclosAB(SatelliteList& padreA, SatelliteList& padreB);
    CiclosABGenerator::SegmentoSelected CiclosABGenerator::select_edge(long nodoAnterior,long nodoActual, SatelliteList& padreA, SatelliteList& padreB, bool segmentoPadreA, std::unordered_set<long> nodosAnalizadosLoopActual);
    //devuelve false si el segmento que ya esten en otro ciclo
    bool CiclosABGenerator::juzgarSegmento(Segmento segmento, std::vector<CicloAB> ciclosAB);
    //devuelve el ciclo cerrado cortando la cola si es necesario
    CicloAB CiclosABGenerator::obtenerCicloSinTail(CicloAB ciclo);
    //devuelve false si el ciclo tiene numero de segmentos impar
    bool CiclosABGenerator::juzgarCiclo(CicloAB ciclo);
    bool getNodoSuperCompartido(long nodoCentral, SatelliteList& padreA, SatelliteList& padreB);
    

private:
    // Aquí puedes agregar métodos privados para ayudar en la generación de ciclos, si es necesario
};

