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
  
  ////////////////////////////////////
  // CONSTRUCTORES
  DatosFichero(char* fichero);
  DatosFichero();

  ///////////////////////////////////
  // MÉTODOS
  void MostrarDatos();
};

#endif