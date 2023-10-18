#pragma once
#include "Poblacion.h"
#include "Crossover.h"
#include "Mutacion.h"

class AlgoritmoGenetico {
    Poblacion poblacion;
    Crossover crossover;
    Mutacion mutacion;

public:
    void evolucionar();
    // Otros métodos según sea necesario
};

