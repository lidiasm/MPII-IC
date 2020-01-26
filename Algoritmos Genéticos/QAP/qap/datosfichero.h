#ifndef DATOS_FICHERO
#define DATOS_FICHERO

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class DatosFichero {

public:
  int nInstalaciones;
  vector<vector<int> > flujos;
  vector<vector<int> > distancias;

  DatosFichero(char* fichero);
  DatosFichero();
  void MostrarDatos();
};

#endif