#pragma once
#include <vector>
#include <functional> // para std::hash
#include <algorithm>  // para std::min y std::max

// Primero, definimos la estructura Segmento fuera de la clase CicloAB.
struct Segmento {
    long nodo_anterior;
    long nodo_siguiente;
    bool es_padre_A;
    bool operator==(const Segmento& otro) const {
        return (nodo_anterior == otro.nodo_anterior && nodo_siguiente == otro.nodo_siguiente)
            || (nodo_anterior == otro.nodo_siguiente && nodo_siguiente == otro.nodo_anterior);
    }
};

// Ahora, especializamos std::hash para Segmento a nivel global.
namespace std {
    template <>
    struct hash<Segmento> {
        std::size_t operator()(const Segmento& s) const {
            long menor = std::min(s.nodo_anterior, s.nodo_siguiente);//esto es para hacer un hash en el qu eno importe el orden de los nodos para identificar un segmento
            long mayor = std::max(s.nodo_anterior, s.nodo_siguiente);//esto es para hacer un hash en el qu eno importe el orden de los nodos para identificar un segmento
            std::size_t h1 = std::hash<long>{}(menor);
            std::size_t h2 = std::hash<long>{}(mayor);
            return h1 ^ (h2 << 1);
        }
    };
}


class CicloAB {
public:






    // Almacena la secuencia de segmentos del ciclo
    std::vector<Segmento> segmentos;
    long id;// para identificar los ciclosAB
    void agregarSegmento(long nodo_anterior, long nodo_siguiente, bool es_padre_A);
    void CicloAB::agregarSegmento(Segmento segmento);

    bool esCerrado() const{
        if (segmentos.size()<3) return false;
        return segmentos.front().nodo_anterior == segmentos.back().nodo_siguiente;
    }


    void eliminarSegmento(Segmento segmento) {
        segmentos.erase(
            std::remove_if(
                segmentos.begin(), segmentos.end(),
                [&segmento](const Segmento& s) { return s == segmento; }
            ),
            segmentos.end()
        );
    }


    CicloAB CicloAB::unir(CicloAB padre2, long desdeNodoPadre1, long hastaNodoPadre2, long desdeNodoPadre2, long hastaNodoPadre1) {
        CicloAB resultado;

        // Copia todos los segmentos del objeto actual (Padre A)
        resultado.segmentos = this->segmentos;

        // Paso 1: Crear los segmentos
        Segmento segmentoDesdePadre1APadre2{ desdeNodoPadre1, hastaNodoPadre2, true };
        Segmento segmentoDesdePadre2APadre1{ desdeNodoPadre2, hastaNodoPadre1, false };

        resultado.segmentos.push_back(segmentoDesdePadre1APadre2);


        // Inserta todos los elementos de 'otroVector' al final de 'segmentosOrdenadosPosteriores'
        resultado.segmentos.insert(resultado.segmentos.end(), padre2.segmentos.begin(), padre2.segmentos.end());
        resultado.segmentos.push_back(segmentoDesdePadre2APadre1);

        return resultado;
    }


};

