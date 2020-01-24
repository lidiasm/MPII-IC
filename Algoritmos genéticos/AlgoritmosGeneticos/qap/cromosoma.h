#ifndef CROMOSOMA_H
#define CROMOSOMA_H

#include <vector>
#include <algorithm>
#include "datosfichero.h"

using namespace std;

class Cromosoma {
public:
  int coste = 0;
  vector<int> solucion;
  Cromosoma();
  Cromosoma(int &semilla);
  void CalcularCoste(DatosFichero &datos);
  void InicializarSolucion(DatosFichero &datos);
  void Intercambio(int pos1, int pos2);
  void ImprimirCromosoma();
};

#endif