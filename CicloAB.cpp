#include "pch.h"
#include "CicloAB.h"

void CicloAB::agregarSegmento(long nodo_anterior, long nodo_siguiente, bool es_padre_A) {
    Segmento segmento{ nodo_anterior, nodo_siguiente, es_padre_A };
    segmentos.push_back(segmento);
}
void CicloAB::agregarSegmento(Segmento segmento) {
        segmentos.push_back(segmento);
}