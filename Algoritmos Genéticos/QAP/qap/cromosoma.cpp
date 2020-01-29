#include "cromosoma.h"
#include "datosfichero.h"
#include "pseudoaleatorio.h"

Cromosoma::Cromosoma() {
  solucion = vector<int>(0);
  fitness = 0;
}

// Método estático para poder establecer una semilla para generar los números
// aleatorios de forma que los resultados sean reproducibles
void Cromosoma::SetSemilla(int &semilla) {
  Seed = semilla;
}
// Calcular el coste de la solución.
void Cromosoma::CalcularFitness(DatosFichero &datos) {
  // Reinicializamos el coste de la solución a 0 para que no se acumule.
  fitness = 0;
  for(int i=0; i<datos.nInstalaciones; i++) {
    for (int j=0; j<solucion.size(); j++) {
      if (i != j) {
        fitness += datos.flujos[i][j]*datos.distancias[solucion[i]][solucion[j]];
      }
    }
  }
}

// Calcular la diferencia de fitness dadas dos asociaciones de instalaciones.
// Si el coste es negativo la solución actual es peor que la sugerida
int Cromosoma::CalcularDiferenciaFitness(DatosFichero &datos, int i1, int i2) {
  int diferenciaFitness = 0;
  for (int i=0; i<datos.nInstalaciones; i++) {
    if (i != i1 && i != i2) {
      diferenciaFitness +=
      datos.flujos[i1][i]*(datos.distancias[solucion[i2]][solucion[i]]-datos.distancias[solucion[i1]][solucion[i]]) +
      datos.flujos[i2][i]*(datos.distancias[solucion[i1]][solucion[i]]-datos.distancias[solucion[i2]][solucion[i]]) +
      datos.flujos[i][i1]*(datos.distancias[solucion[i]][solucion[i2]]-datos.distancias[solucion[i]][solucion[i1]]) +
      datos.flujos[i][i2]*(datos.distancias[solucion[i]][solucion[i1]]-datos.distancias[solucion[i]][solucion[i2]]);
    }
  }
  return diferenciaFitness;
}

void Cromosoma::InicializarSolucion(DatosFichero &datos) {
  int numero;
  // Inicializamos la solución a -1 con el tamaño de los datos actuales
  solucion.resize(datos.nInstalaciones, -1);
  for (int i=0; i<datos.nInstalaciones; i++) {
    numero = Randint(0, datos.nInstalaciones-1);
    // Sin repetidos
    while (find(solucion.begin(), solucion.end(), numero) != solucion.end()) {
      numero = Randint(0, datos.nInstalaciones-1);
    }
    solucion[i] = numero;
  }
  // Evaluamos la nueva solución generada
  CalcularFitness(datos);
}
// Añadimos esta función para generar un entero aleatorio y así no tener que
// incluir el fichero "pesudoaleatorio.h" y nos de un error relacionado con las
// múltiples definiciones
int Cromosoma::GenerarNumeroRandom(int limInf, int limSup) {
  return Randint(limInf, limSup);
}

void Cromosoma::IntercambiarGenes(int gen1, int gen2) {
  swap(solucion[gen1], solucion[gen2]);
}

Cromosoma Cromosoma::SimuladorIntercambioGenes(DatosFichero &datos, int gen1, int gen2) {
  Cromosoma copiaCromosoma;
  copiaCromosoma.solucion = solucion;
  swap(copiaCromosoma.solucion[gen1], copiaCromosoma.solucion[gen2]);
  copiaCromosoma.CalcularFitness(datos);
  return copiaCromosoma;
}

void Cromosoma::ImprimirCromosoma() {
  cout << "Coste: " << fitness << endl;
  cout << "Solución: ";
  for (int i=0; i<solucion.size(); i++) {
    cout << solucion[i] << " ";
  }
  cout << endl;
}