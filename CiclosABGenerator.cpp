#include "pch.h"
#include "CiclosABGenerator.h"
#include <unordered_map>
#include <stack>
#include "SatelliteListIterator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

std::vector<CicloAB> CiclosABGenerator::generarCiclosAB(SatelliteList& padreA, SatelliteList& padreB) {
    std::vector<CicloAB> eSetCiclosAB; // Vector para almacenar los ciclos resultantes
    std::unordered_set<long> nodosAnalizadosLoopActual; // Conjunto para almacenar los nodos ya analizados en el loop actual
    std::unordered_set<long> nodosAnalizadosCompartidos; // Conjunto para almacenar los nodos con dosd segmentos compartidos de ambos lados
    
    //falta salir cuando detecta que los dos padres son iguales

    // Selecciona un nodo inicial aleatorio para empezar el ciclo.
    std::srand(std::time(0));  // Usar la hora actual como semilla
    long indiceInicio = std::rand() % padreA.mapaNodo_city.size();  // Generar un número aleatorio entre 0 y el numero de nodos Punto de inicio
    int limit = padreA.mapaNodo_city.size(); // Límite superior (exclusivo)

    bool masNodosPorProcesar = true;
    bool segmentoPadreA = true;// este alterna entre A y B
   
    

         // Iterar a través de los nodos
        for (long indice = 0; indice < padreA.mapaNodo_city.size(); indice++) {
            nodosAnalizadosLoopActual.clear();// limpio para una nueva pasada

            // Si el nodo es el pen-ultimo, con un dos nodos no se puede formar un ciclo, continuar con el siguiente
            if (indice > padreA.mapaNodo_city.size() - 3) {
                masNodosPorProcesar = false;
                continue;
            }


            long nodoActual = (indiceInicio + indice) % limit;//hace el for circular
            if (nodosAnalizadosCompartidos.find(nodoActual) != nodosAnalizadosCompartidos.end()) continue;// no usar nodos compartidos por segmentos de ambos padres 2 veces
            /*nucleo central de generar ciclosAB:
             selecionar segmentos validos segun las reglas hasta formar un ciclo 
             luego recortar el tail
             luego verificar que el ciclo es valido 
             insertar el ciclo en el eSetCiclosAB
            */
            nodosAnalizadosLoopActual.insert(nodoActual);

            //este metodo selecciona segmentos alternativamente del padre A y B
            SegmentoSelected segmentoSInicial = select_edge(-1,nodoActual, padreA, padreB, segmentoPadreA, nodosAnalizadosLoopActual);
            SegmentoSelected segmentoS = segmentoSInicial;
            CicloAB cicloAB;
            bool cicloArmado = true;
            while (!segmentoS.cerrado) {
                segmentoPadreA = !segmentoPadreA;// para alternar padres
                nodosAnalizadosLoopActual.insert(segmentoS.segmento.nodo_siguiente);//reveer en el futuro porque esto marca los nodos para no volver a analizarlos
                
                segmentoS = select_edge(segmentoS.segmento.nodo_anterior, segmentoS.segmento.nodo_siguiente, padreA, padreB, segmentoPadreA, nodosAnalizadosLoopActual);
                if (!juzgarSegmento(segmentoS.segmento, eSetCiclosAB)) {
                    cicloArmado = false;// los diferentes ciclosAB no pueden compartir segmentos
                    break; 
                }

                if (getNodoSuperCompartido(segmentoS.segmento.nodo_anterior, padreA, padreB)) {
                    nodosAnalizadosCompartidos.insert(segmentoS.segmento.nodo_anterior);
                }

                cicloAB.agregarSegmento(segmentoS.segmento);
            }

            //solo cuando genero un ciclo cerrado
            if (cicloArmado && cicloAB.segmentos.size()>3) {
                CicloAB cicloinTail= obtenerCicloSinTail(cicloAB);
                if (juzgarCiclo(cicloinTail)) eSetCiclosAB.push_back(cicloinTail); // Agregar el ciclo actual al vector de ciclos resultantes
            }
        }
            return eSetCiclosAB; // Devolver los ciclos generados
 }
//devuelve true si los segmentod de ambos padres no solo comparten el nodo(eso es seguro), sino que comparten tanto el nodo next como el previous
// osea que si hacemos next y previous desde ese nodo en ambos padres en un set solo se obtendran dos nodos (set.size()=2).
//sino devuelve false
bool CiclosABGenerator::getNodoSuperCompartido(long nodoCentral,SatelliteList& padreA, SatelliteList& padreB) {
    std::unordered_set<long> nodosAnalizados;
    nodosAnalizados.insert(padreA.nextNodo(nodoCentral).order);
    nodosAnalizados.insert(padreA.previousNodo(nodoCentral).order);
    nodosAnalizados.insert(padreB.nextNodo(nodoCentral).order);
    nodosAnalizados.insert(padreB.previousNodo(nodoCentral).order);
    if (nodosAnalizados.size() == 2) return true;

    return false;

}

        /*selecciona un segmento que cumple con las condiciones de
        1) este metodo selecciona segmentos alternativamente del padre A y B
        2) El segmento no ha sido seleccionado anteriormente ni por Padre A o B (para eso verifica sus nodos finales)
        3) Si tiene dos segmentos no usados a seguir selecciona uno al azar
        4) Si encuentra un nodo ya visitado(tiene 3 segmentos o mas ) devuelve true en cerrado
        */
        CiclosABGenerator::SegmentoSelected CiclosABGenerator::select_edge(long nodoAnterior,long nodoActual, SatelliteList& padreA, SatelliteList& padreB, bool segmentoPadreA, std::unordered_set<long> nodosAnalizadosLoopActual){
            Point2D nextPoint;
            Point2D previousPoint;
            CiclosABGenerator::SegmentoSelected segmento;
            //alterna entre padre A y B
            if (segmentoPadreA) {
                segmento.segmento.es_padre_A = true;
                nextPoint= padreA.nextNodo(nodoActual);
                previousPoint = padreA.previousNodo(nodoActual);
            }
            else
            {
                segmento.segmento.es_padre_A = false;
                nextPoint = padreB.nextNodo(nodoActual);
                previousPoint = padreB.previousNodo(nodoActual);
            }

            std::srand(std::time(0));  // usar la hora actual como semilla
            bool isNextRand = std::rand() % 2;  // generará 0 o 1

            

            //aletoriamente elige camino
            if (isNextRand) {
                if (nextPoint.order != nodoAnterior) {
                    segmento.segmento.nodo_anterior = nodoActual;
                    segmento.segmento.nodo_siguiente = nextPoint.order;
                }
                else {//sino usa el previo para no volver a el mismo segmento que trazo antes
                    segmento.segmento.nodo_anterior = nodoActual;
                    segmento.segmento.nodo_siguiente = previousPoint.order;
                }
            }
            else {

                if (previousPoint.order != nodoAnterior) {
                    segmento.segmento.nodo_anterior = nodoActual;
                    segmento.segmento.nodo_siguiente = previousPoint.order;
                }
                else {//sino usa el nest para no volver a el mismo segmento que trazo antes
                    segmento.segmento.nodo_anterior = nodoActual;
                    segmento.segmento.nodo_siguiente = nextPoint.order;
                }
            }

            //cierra ciclo
            if (nodosAnalizadosLoopActual.find(segmento.segmento.nodo_siguiente) != nodosAnalizadosLoopActual.end()) {
                segmento.cerrado = true;
            }
            
            return segmento;
        }
    
        //devuelve false si el segmento que ya esten en otro ciclo
        bool CiclosABGenerator::juzgarSegmento(Segmento segmento, std::vector<CicloAB> ciclosAB) {
            // Recorrer el vector usando un bucle for-each
            for (const auto& ciclo : ciclosAB) {
                for each (Segmento segmentoCiclo  in ciclo.segmentos)
                {
                    if (segmentoCiclo == segmento) return false;
                }
            }
            return true;
        }
        //devuelve el ciclo cerrado cortando la cola si es necesario
        CicloAB CiclosABGenerator::obtenerCicloSinTail(CicloAB cicloConTail) {
           /*en principio la logica de este metodo es que debido a al aforma en que se van isertando los segmentos
           * al momento de llamar este metodo se cumple lo siguiente: El ultimo punto del ultimo segmento del ciclo es en realidad el comienzo del ciclo 
           * dado que lo cierra
           * por lo tanto si lo recorremos buscando el segmento que tiene como nodo inicial este nodo(el ultmo nodo del ultimo segmento)
           * obtendremos el ciclo cerrado.
           * Si tiene tail(cola) es decir segmentos fuera del ciclo, estos no seran insertados en el ciclo
           */

            CicloAB cicloCerrado;
            Segmento ultimoElemento = cicloConTail.segmentos.back();
            long ultimoNodo = ultimoElemento.nodo_siguiente;
            bool agregarSegmento = false;
            for each (Segmento segmentoCiclo  in cicloConTail.segmentos)
            {
                if (segmentoCiclo.nodo_anterior == ultimoNodo) agregarSegmento = true;
                if (agregarSegmento) cicloCerrado.agregarSegmento(segmentoCiclo);
            }

            return cicloCerrado;
        }
        //devuelve false si el ciclo tiene numero de segmentos impar
        bool CiclosABGenerator::juzgarCiclo(CicloAB ciclo) {
            if (ciclo.segmentos.size()>3 && ciclo.segmentos.size() % 2 == 0) {//Par
                return true;
            }
            return false;
        }