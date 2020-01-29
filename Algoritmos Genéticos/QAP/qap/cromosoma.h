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
    
    //////////////////////////////////////////////////////////////
    // MÉTODOS ESTÁTICOS
    static int GenerarNumeroRandom(int limInf, int limSup);
    static void SetSemilla(int &semilla);
    // MÉTODOS DE INSTANCIAS
    void CalcularFitness(DatosFichero &datos);
    int CalcularDiferenciaFitness(DatosFichero &datos, int i1, int i2);
    void InicializarSolucion(DatosFichero &datos);
    void IntercambiarGenes(int gen1, int gen2);
    Cromosoma SimuladorIntercambioGenes(DatosFichero &datos, int gen1, int gen2);
    void ImprimirCromosoma();
};

#endif
