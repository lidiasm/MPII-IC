#ifndef BL_H
#define BL_H

#include "cromosoma.h"

class BusquedaLocal {
public:
  Cromosoma solucionBL;
  DatosFichero datos;
  int nIteraciones;

  ///////////////////////// CONSTRUCTORES
  BusquedaLocal(DatosFichero &dat);
  BusquedaLocal(DatosFichero &dat, Cromosoma &c);
  ///////////////////////// MÉTODOS
  void BL(int iteraciones);
};

#endif