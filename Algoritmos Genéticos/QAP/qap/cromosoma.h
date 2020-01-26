#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include "datosfichero.h"
#include <algorithm>

using namespace std;



class Solucion
{
public:
    vector<int> permutacion;
    int coste = 0;
    Solucion();
    Solucion(int &semilla);
    void calcularCoste(DatosFichero &datos);
    void solucionRandom(DatosFichero &datos);
    void OperadorIntercambio(int r, int s);

    int ValorAleatorio(int topeInferior, int topeSuperior);


};

#endif // SOLUCION_H
