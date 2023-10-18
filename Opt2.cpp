#include "pch.h"
#include "Opt2.h"
#include "SatelliteListIterator.h"
#include <random>



std::pair<SatelliteList, bool>  Opt2::localOpt2(SatelliteList tour, std::vector<std::vector<int>>& nearestNeighbors) {


	SatelliteList nuevoTourAmejorar;
	SatelliteList nuevoTourDirecto;
	bool hayMejoraOpt2=false;
	std::unordered_set<long> nodos_unicos;;
	for (long i = 0; i < tour.mapaCity_nodo.size(); i++)
	{

		long nodoA = getRandonNumber(tour.mapaNodo_city.size()-1);
		long nodoB = tour.nextNodo(nodoA).order;
		for (long i = 0; i < 20; i++)// los 20 mas cercanos
		{
			long nodoC = nearestNeighbors[nodoA][i];
			if (nodoC == nodoB) break;// el cercano es el siguiente
			long nodoD = tour.nextNodo(nodoC).order;
			nodos_unicos.clear();
			nodos_unicos.insert(nodoA);
			nodos_unicos.insert(nodoB);
			nodos_unicos.insert(nodoC);
			nodos_unicos.insert(nodoD);

			if (nodos_unicos.size() == 4) {

				if (tour.hayGananciaReverse_SubpathNodos(nodoA, nodoB, nodoC, nodoD)) {
					hayMejoraOpt2 = true;
					nuevoTourAmejorar = tour.clone();
					//debug(nuevoTourAmejorar);
					nuevoTourAmejorar.Reverse_SubpathNodos(nodoA, nodoB, nodoC, nodoD);
					//debug(nuevoTourAmejorar);
					nuevoTourAmejorar.getFitness();
					break;
				}
			}
        }

		if(hayMejoraOpt2)
		{
			SatelliteListIterator iterator(&nuevoTourAmejorar);
			std::vector <Point2D> vPoint;
			while (iterator.hasNext()) {
				Point2D siguienteNodo = iterator.next();
				vPoint.push_back(siguienteNodo);
			}
			nuevoTourDirecto.addPoints(vPoint);
			nuevoTourDirecto.getFitness();
			break;
		}
    }
	return std::make_pair(nuevoTourDirecto, hayMejoraOpt2);;
}

void Opt2::debug(SatelliteList tour) {
	System::Diagnostics::Debug::WriteLine("Tour  ");
	SatelliteListIterator it(&tour);
	while (it.hasNext()) {
		Point2D siguienteNodo = it.next();
        System::Diagnostics::Debug::Write(siguienteNodo.order + ",");
	}

	


}


long Opt2::getRandonNumber(long cant) {

	// Inicializar generador de números aleatorios
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, cant);

	// Generar un número aleatorio entre 0 y cant
	int numero_aleatorio = distrib(gen);
	return numero_aleatorio;
}