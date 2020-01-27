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

void Cromosoma::ImprimirCromosoma() {
  cout << "Coste: " << fitness << endl;
  cout << "Solución: ";
  for (int i=0; i<solucion.size(); i++) {
    cout << solucion[i] << " ";
  }
  cout << endl;
}