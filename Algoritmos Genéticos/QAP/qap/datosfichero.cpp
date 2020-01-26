#include "datosfichero.h"
#include <iostream>

DatosFichero::DatosFichero() { }

DatosFichero::DatosFichero(char* fichero) {
  // Abrimos el fichero
  ifstream fich;
  fich.open(fichero, ifstream::in);
  // Leemos el fichero: número de instalaciones.
  fich >> nInstalaciones;
  // Reservamos espacio para guardar los flujos y distnacias de las instalaciones
  flujos.resize(nInstalaciones);
  distancias.resize(nInstalaciones);
  for (int i=0; i<nInstalaciones; i++) {
    flujos[i].resize(nInstalaciones);
    distancias[i].resize(nInstalaciones);
  }
  // Leemos las matrices
  for (int i=0; i<nInstalaciones; i++) {
    for (int j=0; j<nInstalaciones; j++) {
      fich >> flujos[i][j];
    }
  }
  for (int i=0; i<nInstalaciones; i++) {
    for (int j=0; j<nInstalaciones; j++) {
      fich >> distancias[i][j];
    }
  }
  // Cerramos el fichero
  fich.close();
}

void DatosFichero::MostrarDatos() {
  cout << "Nº instalaciones: " << nInstalaciones << endl;
  cout << "Flujos" << endl;
  for (int i=0; i<nInstalaciones; i++) {
    for (int j=0; j<nInstalaciones; j++) {
      cout << flujos[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl << "Distancias" << endl;
  for (int i=0; i<nInstalaciones; i++) {
    for (int j=0; j<nInstalaciones; j++) {
      cout << distancias[i][j] << " ";
    }
    cout << endl;
  }
}