#ifndef GREEDY_H
#define GREEDY_H

#include "cromosoma.h"
#include "datosfichero.h"
#include <limits.h>
#include <iostream>

class Greedy {
public:
  Cromosoma solucionGreedy;

  //////////////////////////
  // Construtor
  Greedy(DatosFichero &datos);
};

#endif