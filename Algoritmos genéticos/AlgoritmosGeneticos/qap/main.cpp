#include "datosfichero.h"
#include "cromosoma.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  // Abrimos el fichero
  char * f = argv[1];
  DatosFichero datos(f);
  datos.MostrarDatos();
  // Prueba a crear un cromosoma
  Cromosoma cromosoma;
  cromosoma.InicializarSolucion(datos);
  cromosoma.ImprimirCromosoma();
  return 0;
}