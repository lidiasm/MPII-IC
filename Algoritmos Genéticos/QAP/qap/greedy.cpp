#include "greedy.h"

Greedy::Greedy(DatosFichero &datos) {
  // Inicializamos la solución
  solucionGreedy.solucion.resize(datos.nInstalaciones, -1);
  // Calculamos los dos vectores potenciales de la matriz de flujo y distancia
  vector<int> potencialFlujo(datos.nInstalaciones, 0);
  vector<int> potencialDistancia(datos.nInstalaciones, 0);

  for (int i=0; i<datos.nInstalaciones; i++) {
    for (int j=0; j<datos.nInstalaciones; j++) {
      potencialFlujo[i] += datos.flujos[i][j];
      potencialDistancia[i] += datos.distancias[i][j];
    }
  }
  // Con estos dos vectores controlamos las unidades y localizaciones asignadas
  vector<bool> unidadesAsignadas(datos.nInstalaciones, false);
  vector<bool> localizacionesAsignadas(datos.nInstalaciones, false);
  int flujoMax, flujoPos, distanciaMin, distanciaPos;
  for (int i=0; i<datos.nInstalaciones; i++) {
    flujoMax = INT_MIN;
    distanciaMin = INT_MAX;
    // Flujo máximo
    for (int f=0; f<datos.nInstalaciones; f++) {
      if (potencialFlujo[f] > flujoMax && !unidadesAsignadas[f]) {
        flujoMax = potencialFlujo[f];
        flujoPos = f;
      }
    }
    // Distancia mínima
    for (int d=0; d<datos.nInstalaciones; d++) {
      if (potencialDistancia[d] < distanciaMin && !localizacionesAsignadas[d]) {
        distanciaMin = potencialDistancia[d];
        distanciaPos = d;
      }
    }
    // Asignamos la pareja escogida
    solucionGreedy.solucion[flujoPos] = distanciaPos;
    unidadesAsignadas[flujoPos] = true;
    localizacionesAsignadas[distanciaPos] = true;
  }
  // Calculamos el fitness de la solución
  solucionGreedy.CalcularFitness(datos);
}