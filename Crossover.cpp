#include "pch.h"
#include "Crossover.h"
#include <unordered_map>
#include <algorithm> // para std::find_if
#include <iterator>  // para std::back_inserter
#include <iostream>
#include <vector>
#include <unordered_set>
std::unordered_map<long, long> nodoACiclo;
std::unordered_map<long, CicloAB> ciclos;
long idCicloClass = 0;
SatelliteList Crossover::cruzar( SatelliteList& padre1,  SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors, TspFile tspFile) {
    // Implementar la lógica de cruce EAX

    std::vector<Segmento> miniToursPadre1 = getMiniToursPadre1(padre1, padre2, nearestNeighbors);
    SatelliteList resultado= unionDeSegmentos(miniToursPadre1, nearestNeighbors, tspFile);

    return resultado; // Devolver el hijo resultante
}


std::vector<Segmento> Crossover::getMiniToursPadre1(SatelliteList& padre1, SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors) {
    // Implementar la lógica de cruce EAX hasta miitours


    CiclosABGenerator generador;
    std::vector<CicloAB> ciclosAB = generador.generarCiclosAB(padre1, padre2);
    std::vector<Segmento> miniToursPadre1 = padre1.divideTourConCiclosAB(ciclosAB);
    std::vector<Segmento> coleccionDeSegmentos;
    
  


    return miniToursPadre1;
}

std::vector<Segmento> Crossover::getCiclosAB(SatelliteList& padre1, SatelliteList& padre2, std::vector<std::vector<int>>& nearestNeighbors) {
    // Implementar la lógica de cruce EAX hasta miitours


    CiclosABGenerator generador;
    std::vector<CicloAB> ciclosAB = generador.generarCiclosAB(padre1, padre2);
    std::vector<Segmento> coleccionDeSegmentos;

    for (const CicloAB& ciclo : ciclosAB) {
        std::copy(ciclo.segmentos.begin(), ciclo.segmentos.end(), std::back_inserter(coleccionDeSegmentos));
    }


    return coleccionDeSegmentos;
}


// Método principal que se encargará de unir los segmentos en un único ciclo cerrado.
SatelliteList Crossover::unionDeSegmentos(std::vector<Segmento>& miniToursPadre1, std::vector<std::vector<int>>& nearestNeighbors, TspFile tspFile) {
    // Punto 1
    std::vector<CicloAB> vciclos = identificarCiclos(miniToursPadre1);

    // Punto 2
    ciclos.clear();
    for each (CicloAB cicloAB  in vciclos)
    {
        idCicloClass++;
        cicloAB.id = idCicloClass;
        ciclos[idCicloClass] = cicloAB;
    }



    // Punto 4
     nodoACiclo = asociarNodosConCiclos();

    // Llamada al nuevo método para conectar ciclos abiertos
    conectarCiclosAbiertos( nearestNeighbors);

    if (ciclos.size() > 1) {
        // Llamada al método para conectar ciclos cerrados
        conectarCiclosCerrados(nearestNeighbors);
    }

    SatelliteList tourResultado;
    auto it = ciclos.begin();
    CicloAB primerCiclo = it->second;


    tourResultado.addPoints(primerCiclo,tspFile);
    return tourResultado;

}

// Punto 1
std::vector<CicloAB> Crossover::identificarCiclos(std::vector<Segmento>& miniToursPadre1) {
    std::vector<CicloAB> vciclos;
    std::unordered_map<long, std::vector<long>> grafo;

    // Construir el grafo a partir de los segmentos
    for (const auto& segmento : miniToursPadre1) {
        grafo[segmento.nodo_anterior].push_back(segmento.nodo_siguiente);
        grafo[segmento.nodo_siguiente].push_back(segmento.nodo_anterior); // Grafo no dirigido
    }

    std::unordered_set<long> visitados;

    // Función DFS para explorar cada ciclo
    std::function<void(long, long, CicloAB&)> dfs = [&](long nodoActual, long nodoPadre, CicloAB& cicloActual) {
        visitados.insert(nodoActual);
        for (long vecino : grafo[nodoActual]) {
            if (vecino == nodoPadre) continue; // Evitar volver al nodo padre en el grafo no dirigido
            if (visitados.find(vecino) == visitados.end()) {
                cicloActual.agregarSegmento(nodoActual, vecino, true); // Aquí asumimos que es_padre_A es verdadero, ajusta según tu caso
                dfs(vecino, nodoActual, cicloActual);
            }
        }
    };

    // Iniciar DFS desde cada nodo no visitado
    for (const auto& par : grafo) {
        if (visitados.find(par.first) == visitados.end()) {
            CicloAB cicloActual;
            dfs(par.first, -1, cicloActual); // -1 indica que no hay nodo padre
            
            if(cicloActual.segmentos.size()>0)  vciclos.push_back(cicloActual);
        }
    }

    return vciclos;
}




// Punto 3: Para los ciclos abiertos, identifica los nodos extremos.
std::unordered_map<long, std::unordered_set<long>> Crossover::identificarNodosExtremos() {
    // Crea un mapa desordenado para almacenar los nodos extremos de cada ciclo.
    std::unordered_map<long, std::unordered_set<long>> nodosExtremos;
    // Itera a través de cada ciclo en la lista de ciclos.
    
    for (auto& pair : ciclos) {
        long key = pair.first;
        CicloAB& ciclo = pair.second;
         // Verifica si el ciclo es abierto.
        if (!ciclo.esCerrado()) {
            // Inserta el nodo anterior del primer segmento del ciclo como un nodo extremo.
            nodosExtremos[ciclo.id].insert(ciclo.segmentos.front().nodo_anterior);
            // Inserta el nodo siguiente del último segmento del ciclo como otro nodo extremo.
            nodosExtremos[ciclo.id].insert(ciclo.segmentos.back().nodo_siguiente);
        }
    }
    // Devuelve el mapa de nodos extremos.
    return nodosExtremos;
}

// Punto 4: Crea un mapa o una estructura de datos que asocie cada nodo con el número de ciclo al que pertenece.
std::unordered_map<long, long> Crossover::asociarNodosConCiclos() {
    
    for (auto& pair : ciclos) {
        long key = pair.first;
        CicloAB& ciclo = pair.second;
        for ( auto& segmento : ciclo.segmentos) {
            nodoACiclo[segmento.nodo_anterior] = ciclo.id;
            nodoACiclo[segmento.nodo_siguiente] = ciclo.id;
        }
    }
    return nodoACiclo;
}


// Método para conectar ciclos abiertos en un conjunto de ciclos
void Crossover::conectarCiclosAbiertos( std::vector<std::vector<int>>& nearestNeighbors) {
    while (true) { // Loop infinito que se romperá cuando no haya más ciclos abiertos
        bool hayCiclosAbiertos = false;
        if ( ciclos.size() == 1) break; // Salir del bucle while si queda un solo ciclo

        for (auto& pair : ciclos) {
            long cicloId1 = pair.first;
            CicloAB& ciclo1 = pair.second;

            if (!ciclo1.esCerrado()) { // Verifica si el ciclo está abierto
                hayCiclosAbiertos = true;

                // Identificar nodos extremos del ciclo1
                long nodoExtremo1_1 = ciclo1.segmentos.front().nodo_anterior;
                long nodoExtremo1_2 = ciclo1.segmentos.back().nodo_siguiente;

                long nodoMasCercano = -1;
                long cicloIdMasCercano = -1;

                // Buscar el nodo más cercano que pertenezca a un ciclo diferente
                for (int vecino : nearestNeighbors[nodoExtremo1_1]) {
                    auto itCicloVecino = nodoACiclo.find(vecino);
                    if (itCicloVecino != nodoACiclo.end() && itCicloVecino->second != cicloId1) {
                        nodoMasCercano = vecino;
                        cicloIdMasCercano = itCicloVecino->second;
                        break;
                    }
                }

                if (nodoMasCercano != -1 && cicloIdMasCercano != -1) {
                    CicloAB& ciclo2 = ciclos[cicloIdMasCercano];

                    // Identificar nodos extremos del ciclo2 abierto
                    long nodoExtremo2_1 = ciclo2.segmentos.front().nodo_anterior;
                    long nodoExtremo2_2 = ciclo2.segmentos.back().nodo_siguiente;

                    if (ciclo2.esCerrado()) {
                        // Identificar nodos extremos del ciclo2 cerrado en el punto de insercion
                        std::vector<Segmento> segmentosOrdenadosAnteriores;
                        std::vector<Segmento> segmentosOrdenadosPosteriores;
                        bool encontroPuntoInsercion = false;
                        for each (Segmento segmento in ciclo2.segmentos)
                        {
                            if (segmento.nodo_anterior == nodoMasCercano) {// al encontrarlo no lo inserta por lo tanto hace un hueco
                                encontroPuntoInsercion = true;
                            }
                            else {// sino lo encuentra los inserta el la lista de anterior o de posterior al hueco
                              if (!encontroPuntoInsercion)  segmentosOrdenadosAnteriores.push_back(segmento);
                              else segmentosOrdenadosPosteriores.push_back(segmento);
                            }
                        }
                        std::vector<Segmento> segmentosOrdenadosPosEliminacionPtoInsercion;
                        // Aquí puedes reinsertar los segmentos en orden 
                        // Inserta todos los elementos de 'segmentosOrdenadosPosEliminacionPtoInsercion' al final de 'segmentosOrdenadosPosEliminacionPtoInsercion'
                        segmentosOrdenadosPosEliminacionPtoInsercion.insert(segmentosOrdenadosPosEliminacionPtoInsercion.end(), segmentosOrdenadosPosteriores.begin(), segmentosOrdenadosPosteriores.end());
                        segmentosOrdenadosPosEliminacionPtoInsercion.insert(segmentosOrdenadosPosEliminacionPtoInsercion.end(), segmentosOrdenadosAnteriores.begin(), segmentosOrdenadosAnteriores.end());
                        ciclo2.segmentos = segmentosOrdenadosPosEliminacionPtoInsercion;
                        // Identificar nodos extremos del ciclo2 abierto
                         nodoExtremo2_1 = ciclo2.segmentos.front().nodo_anterior;
                         nodoExtremo2_2 = ciclo2.segmentos.back().nodo_siguiente;
                    }
                    //CicloAB padre2, long desdeNodoPadre1, long hastaNodoPadre2, long desdeNodoPadre2, long hastaNodoPadre1
                    CicloAB nuevoCiclo = ciclo1.unir(ciclo2,nodoExtremo1_2,  nodoExtremo2_1,nodoExtremo2_2, nodoExtremo1_1 );
                    idCicloClass++;
                    nuevoCiclo.id = idCicloClass;
                    for (const auto& segmento : nuevoCiclo.segmentos) {
                        nodoACiclo[segmento.nodo_anterior] = nuevoCiclo.id;
                        nodoACiclo[segmento.nodo_siguiente] = nuevoCiclo.id;
                    }
                    //actualiza el mapa de ciclos
                    ciclos.erase(ciclo1.id);
                    ciclos.erase(ciclo2.id);
                    if(nuevoCiclo.segmentos.size()>0)     ciclos[idCicloClass] = nuevoCiclo;
                    break; // Salir del bucle for para empezar a buscar el siguiente ciclo abierto
                }
            }
        }

        if (!hayCiclosAbiertos ) {
            break; // Salir del bucle while si no hay más ciclos abiertos
        }
    }
}



// Método para conectar ciclos cerrados
void Crossover::conectarCiclosCerrados(std::vector<std::vector<int>>& nearestNeighbors) {
    int k = 0;

    while (ciclos.size() > 1) {
        bool cicloConectado = false;

        for (auto& pair : ciclos) {
            long key = pair.first;
            CicloAB& ciclo = pair.second;
            for (const auto& segmento : ciclo.segmentos) {
                long nodoActual = segmento.nodo_anterior; 

              
                    long nodoCercano = nearestNeighbors[nodoActual][k];
                    long cicloIdCercano = nodoACiclo[nodoCercano];

                    if (cicloIdCercano != ciclo.id) {//los ciclos son diferentes
                        // Conectar los ciclos
                        CicloAB& ciclo1 = ciclos[ciclo.id];
                        CicloAB& ciclo2 = ciclos[cicloIdCercano];


                        long nodoExtremo1_1;
                        long nodoExtremo1_2;
                        long nodoExtremo2_1;
                        long nodoExtremo2_2;


                        // partir ciclo 1
                        // Identificar nodos extremos del ciclo1 cerrado en el punto de insercion
                        std::vector<Segmento> segmentosOrdenadosAnterioresCiclo1;
                        std::vector<Segmento> segmentosOrdenadosPosterioresCiclo1;
                        bool encontroPuntoInsercion = false;
                        for each (Segmento segmento in ciclo1.segmentos)
                        {


                            if (segmento.nodo_anterior == nodoActual) {// al encontrarlo no lo inserta por lo tanto hace un hueco
                                encontroPuntoInsercion = true;
                            }
                            else {// sino lo encuentra los inserta el la lista de anterior o de posterior al hueco
                                if (!encontroPuntoInsercion)  segmentosOrdenadosAnterioresCiclo1.push_back(segmento);
                                else segmentosOrdenadosPosterioresCiclo1.push_back(segmento);
                            }
                        }
                        std::vector<Segmento> segmentosOrdenadosPosEliminacionPtoInsercionCiclo1;
                        // Aquí reinsertar los segmentos en orden 
                        // Inserta todos los elementos de 'segmentosOrdenadosPosEliminacionPtoInsercion' al final de 'segmentosOrdenadosPosEliminacionPtoInsercion'
                        segmentosOrdenadosPosEliminacionPtoInsercionCiclo1.insert(segmentosOrdenadosPosEliminacionPtoInsercionCiclo1.end(), segmentosOrdenadosPosterioresCiclo1.begin(), segmentosOrdenadosPosterioresCiclo1.end());
                        segmentosOrdenadosPosEliminacionPtoInsercionCiclo1.insert(segmentosOrdenadosPosEliminacionPtoInsercionCiclo1.end(), segmentosOrdenadosAnterioresCiclo1.begin(), segmentosOrdenadosAnterioresCiclo1.end());
                        ciclo1.segmentos = segmentosOrdenadosPosEliminacionPtoInsercionCiclo1;
                        // Identificar nodos extremos del ciclo2 abierto
                        nodoExtremo1_1 = ciclo1.segmentos.front().nodo_anterior;
                        nodoExtremo1_2 = ciclo1.segmentos.back().nodo_siguiente;


                        // partir ciclo 2
                        // Identificar nodos extremos del ciclo2 cerrado en el punto de insercion
                        std::vector<Segmento> segmentosOrdenadosAnterioresCiclo2;
                        std::vector<Segmento> segmentosOrdenadosPosterioresCiclo2;
                        bool encontroPuntoInsercion2 = false;
                        for each (Segmento segmento in ciclo2.segmentos)
                        {
                            if (segmento.nodo_anterior == nodoCercano) {// al encontrarlo no lo inserta por lo tanto hace un hueco
                                encontroPuntoInsercion2 = true;
                            }
                            else {// sino lo encuentra los inserta el la lista de anterior o de posterior al hueco
                                if (!encontroPuntoInsercion2)  segmentosOrdenadosAnterioresCiclo2.push_back(segmento);
                                else segmentosOrdenadosPosterioresCiclo2.push_back(segmento);
                            }
                        }
                        std::vector<Segmento> segmentosOrdenadosPosEliminacionPtoInsercionCiclo2;
                        // Aquí reinsertar los segmentos en orden 
                        // Inserta todos los elementos de 'segmentosOrdenadosPosEliminacionPtoInsercion' al final de 'segmentosOrdenadosPosEliminacionPtoInsercion'
                        segmentosOrdenadosPosEliminacionPtoInsercionCiclo2.insert(segmentosOrdenadosPosEliminacionPtoInsercionCiclo2.end(), segmentosOrdenadosPosterioresCiclo2.begin(), segmentosOrdenadosPosterioresCiclo2.end());
                        segmentosOrdenadosPosEliminacionPtoInsercionCiclo2.insert(segmentosOrdenadosPosEliminacionPtoInsercionCiclo2.end(), segmentosOrdenadosAnterioresCiclo2.begin(), segmentosOrdenadosAnterioresCiclo2.end());
                        ciclo2.segmentos = segmentosOrdenadosPosEliminacionPtoInsercionCiclo2;
                        // Identificar nodos extremos del ciclo2 abierto
                        nodoExtremo2_1 = ciclo2.segmentos.front().nodo_anterior;
                        nodoExtremo2_2 = ciclo2.segmentos.back().nodo_siguiente;


                        //CicloAB padre2, long desdeNodoPadre1, long hastaNodoPadre2, long desdeNodoPadre2, long hastaNodoPadre1
                        CicloAB nuevoCiclo = ciclo1.unir(ciclo2, nodoExtremo1_2, nodoExtremo2_1, nodoExtremo2_2, nodoExtremo1_1);
                        idCicloClass++;
                        nuevoCiclo.id = idCicloClass;
                        for (const auto& segmento : nuevoCiclo.segmentos) {
                            nodoACiclo[segmento.nodo_anterior] = nuevoCiclo.id;
                            nodoACiclo[segmento.nodo_siguiente] = nuevoCiclo.id;
                        }
                        //actualiza el mapa de ciclos
                        ciclos.erase(ciclo1.id);
                        ciclos.erase(ciclo2.id);
                        if (nuevoCiclo.segmentos.size() > 0)  ciclos[idCicloClass] = nuevoCiclo;
                        cicloConectado = true;
                        k = 0;// reinicia desde el mas cercano
                    }
              

                if (cicloConectado) break;
            }

            if (cicloConectado) break;
        }

        if (!cicloConectado) ++k;
    }
}
