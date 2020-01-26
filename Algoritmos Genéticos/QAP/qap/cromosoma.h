#ifndef CROMOSOMA_H
#define CROMOSOMA_H

#include <vector>
#include <algorithm>
#include "datosfichero.h"

using namespace std;

class Cromosoma {
public:
    vector<int> solucion;
    int fitness;
    
    ///////////////////////////////////////////////////////////////
    // CONSTRUCTORES
    Cromosoma();
    Cromosoma(int &semilla);

    //////////////////////////////////////////////////////////////
    // MÉTODOS
    void CalcularFitness(DatosFichero &datos);
    void InicializarSolucion(DatosFichero &datos);
    void IntercambiarGenes(int gen1, int gen2);
    static int GenerarNumeroRandom(int limInf, int limSup);
    void ImprimirCromosoma();
};

#endif
