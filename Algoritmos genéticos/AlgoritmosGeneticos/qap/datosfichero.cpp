#include "datosfichero.h"
#include <iostream>

DatosFichero::DatosFichero() { }

DatosFichero::DatosFichero(char* fichero) {
  // Abrimos el fichero
  ifstream fich;
  fich.open(fichero, ifstream::in);
  // Leemos el fichero: número de instalaciones.
  fich >> n_instalaciones;
  // Reservamos espacio para guardar los flujos y distnacias de las instalaciones
  flujos.resize(n_instalaciones);
  distancias.resize(n_instalaciones);
  for (int i=0; i<n_instalaciones; i++) {
    flujos[i].resize(n_instalaciones);
    distancias[i].resize(n_instalaciones);
  }
  // Leemos las matrices
  for (int i=0; i<n_instalaciones; i++) {
    for (int j=0; j<n_instalaciones; j++) {
      fich >> flujos[i][j];
    }
  }
  for (int i=0; i<n_instalaciones; i++) {
    for (int j=0; j<n_instalaciones; j++) {
      fich >> distancias[i][j];
    }
  }
  // Cerramos el fichero
  fich.close();
}

void DatosFichero::MostrarDatos() {
  cout << "Nº instalaciones: " << n_instalaciones << endl;
  cout << "Flujos" << endl;
  for (int i=0; i<n_instalaciones; i++) {
    for (int j=0; j<n_instalaciones; j++) {
      cout << flujos[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl << "Distancias" << endl;
  for (int i=0; i<n_instalaciones; i++) {
    for (int j=0; j<n_instalaciones; j++) {
      cout << distancias[i][j] << " ";
    }
    cout << endl;
  }
}