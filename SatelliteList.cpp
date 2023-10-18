#include "pch.h"
#include "SatelliteList.h"
#include "Point2D.h"
#include "SatelliteListIterator.h" 
#include <iostream>

// Based on Colin Osterman Cesar Rego Satellite List
/* SatelliteList
Estructura de Satélites : Cada "satélite" en la lista representa una ciudad y tiene dos componentes : un enlace al siguiente satélite(next) y un enlace complementario que apunta a la ciudad previa(complement).Cada ciudad está representada por dos satélites en la lista.
Índices de Ciudades y Satélites : Los índices de las ciudades se multiplican por 2 para acceder a sus satélites correspondientes.El satélite en el índice k * 2 está asociado con la conexión hacia la siguiente ciudad, mientras que el satélite en el índice(k * 2) + 1 está asociado con la conexión hacia la ciudad previa.
Método Reverse_Subpath : Esta función invierte un subcamino entre cuatro ciudades dadas(city_index_a, city_index_b, city_index_c, city_index_d), donde city_index_a es el inicio del subcamino, city_index_d es el final, y city_index_b y city_index_c definen el segmento a invertir.
a.Iniciar Inversión : La variable k se inicializa con el city_order del próximo satélite de city_index_b.
b.Invertir Segmento : Un bucle while invierte el segmento entre city_index_b y city_index_c, actualizando los enlaces next y complement de los satélites correspondientes.
c.Actualizar Enlaces : Fuera del bucle, la función actualiza los enlaces next y complement de los satélites en los extremos del subcamino invertido(city_index_a, city_index_b, city_index_c, city_index_d), asegurando que el subcamino invertido esté correctamente enlazado con el resto de la ruta.
Resultado Final : El subcamino entre city_index_b y city_index_c se ha invertido, y la estructura doblemente enlazada permite esta inversión eficiente, manteniendo la coherencia en los enlaces en toda la ruta.
city_order sirve como una identificación única o como un índice para la ciudad correspondiente en la lista de ciudades (identicoal del vector points (y obtener el x,y)). Esto permite acceder rápidamente a la información de la ciudad asociada con un satélite en particular.
Relación con Satélites: Dado que hay dos satélites por ciudad (uno para el enlace next y otro para el complemento), city_order proporciona una manera consistente de relacionar estos satélites con la ciudad que representan.
Manipulación de Rutas: En algoritmos que manipulan o modifican la ruta (como la inversión de un subcamino en Reverse_Subpath), city_order se puede utilizar para determinar cómo deben actualizarse los enlaces entre los satélites para reflejar los cambios en la ruta.
En resumen, city_order es una pieza clave en la estructura de datos, que vincula los nodos satélites con las ciudades que representan y facilita las operaciones en la ruta.

*/





void SatelliteList::addPoints(const CicloAB& ciclo,TspFile tspFile) {
    std::vector<Point2D> pointsToAdd;
   
    // Recorremos cada Segmento en CicloAB
    for (const auto& segmento : ciclo.segmentos) {
        Point2D punto= tspFile.getSetCities()[segmento.nodo_anterior];
        pointsToAdd.push_back(punto);
    }
    // Añadimos el último nodo_siguiente solo si el ciclo no está cerrado
    if (!ciclo.esCerrado() && !ciclo.segmentos.empty()) {
        Point2D puntoFinal = tspFile.getSetCities()[ciclo.segmentos.back().nodo_siguiente];
        pointsToAdd.push_back(puntoFinal);
    }
    // Utilizamos el método existente para añadir los puntos
    addPoints(pointsToAdd);
}

SatelliteList SatelliteList::clone() {
    SatelliteList newSatelliteList ;

    SatelliteListIterator iterator(this);
    std::vector <Point2D> vPoint;
    while (iterator.hasNext()) {
        Point2D siguienteNodo = iterator.next();
        vPoint.push_back(siguienteNodo);
    }
    newSatelliteList.addPoints(vPoint);

    return newSatelliteList;
}

void SatelliteList::addPoints(std::vector<Point2D> points) {


    for each (Point2D point  in points)
    {
        mapaNodo_point[point.order] = point;
    }

    

    long DN = points.size() << 1; // Número total de satélites (2 por ciudad)
    satellites.resize(DN);

    // Ajuste de la inicialización del primer y último enlace para que sea coherente con init()
    satellites[1] = DN - 1;
    for (long i = 0; i < DN; i += 2)
    {
        if (i != DN - 2) satellites[i] = i + 2;
        if (i != 0) satellites[i + 1] = i - 1;
        mapaNodo_city[points[i / 2].order] = i;
        mapaCity_nodo[i] = points[i / 2].order;
        mapaCity_nodo[i+1] = points[i / 2].order;
    }
    satellites[DN - 2] = 0;

    //seteo el numero de nodo del vectorPuntos
   /* SatelliteList::SatelliteNode nodoInicial = nextNodo(0);
   
    for (size_t i = 0; i < points.size() ; i++)
    {
        nodoInicial = next(nodoInicial.city_order);
        mapaNodo_city[nodoInicial.point2D.order] = nodoInicial.city_order;
    }
//verificacion test

    nodoInicial= nextNodo(0);
    std::cout << nodoInicial.point2D.order << "," << std::endl;
    for (size_t i = 0; i < points.size()+4; i++)
    {
        nodoInicial = next(nodoInicial.city_order);
        System::Diagnostics::Debug::Write(nodoInicial.point2D.order + ",");
    }

    System::Diagnostics::Debug::WriteLine("");

    std::cout << nodoInicial.point2D.order << "," << std::endl;
    for (size_t i = 0; i < points.size() + 4; i++)
    {
        nodoInicial = previous(nodoInicial.city_order);
        System::Diagnostics::Debug::Write(nodoInicial.point2D.order + ",");
    }

    System::Diagnostics::Debug::WriteLine("");*/




}

Point2D SatelliteList::getSatelliteNode(long nodo) {
    return mapaNodo_point[nodo];
}


Point2D SatelliteList::nextNodo(long nodo) {
    return mapaNodo_point[mapaCity_nodo[next(mapaNodo_city[nodo])]];
}



Point2D SatelliteList::previousNodo(long nodo) {
    return mapaNodo_point[mapaCity_nodo[previous(mapaNodo_city[nodo])]];
}


/* Returns satellite of the “next” city in the tour. */
long SatelliteList::next(long satellite_index)
{
    return satellites[satellite_index];
}
/* Returns satellite of the “previous” city. */
long SatelliteList::previous(long satellite_index)
{
    return satellites[satellite_index ^ 1] ^ 1;
}
/* Returns the city indexed (in this case, return != parameter). */
long SatelliteList::city(long satellite_index)
{
    return satellite_index >> 1;
}
/* N/A to LL implementation. */
long SatelliteList::complement(long satellite_index)

{
    return satellite_index ^ 1;
}
/* Replaces arcs ab and cd with arcs ac and bd. Implies the bc-path is
reversed. */
void SatelliteList::Reverse_Subpath(long satellite_index_a, long satellite_index_b, long satellite_index_c,long satellite_index_d)
{
    satellites[satellite_index_a] = satellite_index_c ^ 1;
    satellites[satellite_index_c] = satellite_index_a ^ 1;
    satellites[satellite_index_d ^ 1] = satellite_index_b; 
    satellites[satellite_index_b ^ 1] = satellite_index_d;
    // There are no intermediate pointers to flip 
}


//Paso de EAX
// me devuelve un vector con segmentos que pueden crear varios tours cerrados y algunos abiertos
// basicamente saca los segmentos del satellitelist que estan en el ciclo y son del padre A
std::vector<Segmento> SatelliteList::divideTourConCiclosAB(const std::vector<CicloAB>& ciclosAB)  {
  
    std::vector<Segmento> tourDividido;
    std::unordered_set<Segmento> segmentosExcluidos;
    
    
    //genero un set con los segmentos excluidos
        for (const CicloAB& ciclo : ciclosAB) {
            for (const Segmento& segmento : ciclo.segmentos) {
                if (segmento.es_padre_A) {
                    segmentosExcluidos.insert(segmento);
                }
            }
        }

   

    // inserto los segementos del tour original menos los excluidos
    long nodoInicial = nextNodo(0).order;
    long nodoAnterior = nodoInicial;
    long nodoSiguiente = nextNodo(nodoAnterior).order;
    while (nodoInicial != nodoSiguiente) {
        Segmento segmento;
        segmento.nodo_anterior = nodoAnterior;
        segmento.nodo_siguiente = nodoSiguiente;
        if (segmentosExcluidos.find(segmento) == segmentosExcluidos.end()) {//el segmento no existe en los excluidos
        tourDividido.push_back(segmento);
        }
        nodoAnterior = nodoSiguiente;
        nodoSiguiente = nextNodo(nodoSiguiente).order;
    }

    //para el cierre de la lista satellite
    long nodoCierre= previousNodo(nodoInicial).order;
    Segmento segmento;
    segmento.nodo_anterior = nodoInicial;
    segmento.nodo_siguiente = nodoCierre;
    if (segmentosExcluidos.find(segmento) == segmentosExcluidos.end()) {//el segmento no existe en los excluidos
        tourDividido.push_back(segmento);
    }

    // Insertar los segmentos de ciclosAB con es_padre_A = false en el tour dividido
    for (const CicloAB& ciclo : ciclosAB) {
        for (const Segmento& segmento : ciclo.segmentos) {
            if (!segmento.es_padre_A) {
                tourDividido.push_back(segmento);
            }
        }
    }

    return tourDividido;
   
}

long  SatelliteList::getFitness() {

    if (cacheFitness != -1) return cacheFitness;


    SatelliteListIterator iter= SatelliteListIterator(this);
    Point2D puntoAnterior;
    Point2D primerPunto;
    long distancia = 0;
    if (iter.hasNext()) {
        puntoAnterior= iter.next();
    }
    Point2D pointActual;
    while (iter.hasNext()) {
        pointActual=  iter.next();

        distancia= distancia+ puntoAnterior.distanceTo(pointActual);
        puntoAnterior = pointActual;
    }

    distancia = distancia + primerPunto.distanceTo(pointActual);//cierre del ciclo
    if (cacheFitness == -1) cacheFitness = distancia;
    return distancia;
}


void SatelliteList::Reverse_SubpathNodos(long nodoA,long nodoB,long nodoC, long nodoD) {

    long satellite_index_a = mapaNodo_city[nodoA];
    long satellite_index_b = mapaNodo_city[nodoB];
    long satellite_index_c = mapaNodo_city[nodoC];
    long satellite_index_d = mapaNodo_city[nodoD];
    Reverse_Subpath(satellite_index_a, satellite_index_b, satellite_index_c, satellite_index_d);
}

/* calcula la ganancia de reemplazar los segmentos  ab and cd por  ac and bd. */
bool SatelliteList::hayGananciaReverse_SubpathNodos(long a, long b, long c, long d) {


    Point2D pointA = mapaNodo_point[a];
    Point2D pointB = mapaNodo_point[b];
    Point2D pointC = mapaNodo_point[c];
    Point2D pointD = mapaNodo_point[d];

    long distanciaAB = pointA.distanceTo(pointB);
    long distanciaCD = pointC.distanceTo(pointD);

    long distanciaAC = pointA.distanceTo(pointC);
    long distanciaBD = pointB.distanceTo(pointD);
    long diferencia = (distanciaAC + distanciaBD) - (distanciaAB + distanciaCD);// disminuye la distancia total
    if (diferencia < 0) return true;
    return false;
}