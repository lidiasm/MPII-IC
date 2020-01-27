#include "busquedalocal.h"

BusquedaLocal::BusquedaLocal(DatosFichero &dat) {
  datos = dat;
  // Inicializamos una solución de forma aleatoria
  solucionBL.InicializarSolucion(datos);
}

BusquedaLocal::BusquedaLocal(DatosFichero &dat, Cromosoma &c) {
  datos = dat;
  // La solución inicial se pasa como argumento
  solucionBL = c;
}

void BusquedaLocal::BL(int iteraciones) {
  // Reiniciamos el contador de iteraciones
  nIteraciones = 0;
  // Criterios de parada
  bool improveFlag, mejorSol = false;
  // DON'T LOOK BITS: 0 = disponible, 1 = no hay mejoras para esta unidad
  vector<int> dontLookBits;
  // Inicializamos la máscara a 0
  dontLookBits.resize(datos.nInstalaciones, 0);

  while (!mejorSol && nIteraciones < iteraciones) {
    mejorSol = false;
    // Exploramos el vecindario de la solución actual
    for (int i=0; i<datos.nInstalaciones && nIteraciones<iteraciones; i++) {
      // Comprobamos si hay soluciones por mejorar
      bool hayMejora = true;
      for (int j=0; j<dontLookBits.size() && hayMejora; j++) {
        if (dontLookBits[j] == 0) {
          hayMejora = false;
        }
      }
      // Si todas están a 1 significa que ya llegamos a la solución
      if (hayMejora) {
        mejorSol = true;
      }
      // Si la unidad actual se puede mejorar
      if (dontLookBits[i] == 0) {
        improveFlag = false;
        for (int j=0; j<datos.nInstalaciones; j++) {
          // CheckMove: comprobamos si mejora el fitness si intercambiamos dos unidades
          if (solucionBL.CalcularDiferenciaFitness(datos, i, j) < 0) {
            solucionBL.IntercambiarGenes(i, j);
            mejorSol = improveFlag = true;
            dontLookBits[i] = dontLookBits[j] = 0;
          }
          nIteraciones++;
        }
      }
      // Si no se ha conseguido mejorar la solución actual ponemos la mascara a 1
      if (!improveFlag) dontLookBits[i] = 1;
    }
  }

  // Calculamos el coste de la nueva solución
  solucionBL.CalcularFitness(datos);
}