#ifndef GREEDY_H
#define GREEDY_H

#include "cromosoma.h"
#include "datosfichero.h"
#include <limits.h>
#include <iostream>

class Greedy {
public:
  Cromosoma solucionGreedy;
  int iteracion;
  //////////////////////////
  // Construtor
  Greedy();
  /////////////////////////
  // Greedy constructivo (clásico)
  void GreedyConstructivo(DatosFichero &datos);
  // Greedy de transposición: 2-opt
  void Greedy2opt(Cromosoma crom, DatosFichero &datos);
};

#endif