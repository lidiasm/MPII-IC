#include "cromosoma.h"
#include "pseudoaleatorio.h"
#include "datosfichero.h"
#include <iostream>

Cromosoma::Cromosoma() {
  coste = 0;
  solucion = vector<int>(0);
  Seed = 29;
}

Cromosoma::Cromosoma(int &semilla) {
  Seed = semilla;
}

void Cromosoma::CalcularCoste(DatosFichero &datos) {
  coste = 0;
  for (int i=0; i<datos.n_instalaciones; i++) {
    for (int j=0; j<solucion.size(); j++) {
      if (i != j) {
        // Función objetivo
        coste += datos.flujos[i][j] * datos.distancias[solucion[i]][solucion[j]];
      }
    }
  }
}

void Cromosoma::InicializarSolucion(DatosFichero &datos) {
  int numero;
  // Tamaño de la solución
  solucion.resize(datos.n_instalaciones, datos.n_instalaciones);
  // Iterador para comprobar si el número ya existe
  vector<int>::iterator it = solucion.begin();
  for (int i=0; i<datos.n_instalaciones; i++) {
    numero = Randint(0, datos.n_instalaciones);
    it = find(solucion.begin(), solucion.end(), numero);
    // Sin repetidos
    while (it != solucion.end()) {
      numero = Randint(0, datos.n_instalaciones);
      it = find(solucion.begin(), solucion.end(), numero);
    }
    solucion[i] = numero;
  }
  CalcularCoste(datos);
}

void Cromosoma::Intercambio(int pos1, int pos2) {
  swap(solucion[pos1], solucion[pos2]);
}

void Cromosoma::ImprimirCromosoma() {
  cout << "Coste: " << coste << endl;
  cout << "Solución: ";
  for (int i=0; i<solucion.size(); i++) {
    cout << solucion[i] << " ";
  }
  cout << endl;
}