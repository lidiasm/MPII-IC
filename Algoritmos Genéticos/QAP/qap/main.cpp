#include "datosfichero.h"
#include "geneticos.h"

using namespace std;

void testSemillas() {

}

int main(int argc, char *argv[]) {
  int iteraciones = 50000;
  float probCruceAGG = 0.7;
  float probMutacion = 0.001;
  int tamPoblacion = 50;
  int semillaMax = 30;
  int semilla = 29; // Semilla por defectos

  // Se le deben pasar al menos dos argumentos: el nombre del programa y el del fichero.
  if (argc < 2) {
   cout << "Número incorrecto de argumentos" << endl;
   return 0;
  }
  // Si se le pasan 3 es que además se proporciona la semilla
  else if (argc == 3) {
   semilla = atoi(argv[2]);
  }
  cout << "Semilla establecida " << semilla << endl;
  // Leemos el fichero
  char* fichero = argv[1];
  DatosFichero datos(fichero);
  //for (int semilla=1; semilla<=semillaMax; semilla++) {
    //cout << endl << "semilla " << semilla << endl;
    /////////////////////////////////////////////////////// AGG POSICIÓN
    Cromosoma::SetSemilla(semilla);
    Geneticos aggPosicion(datos, probCruceAGG, probMutacion, tamPoblacion);
    aggPosicion.AGGPosicion(iteraciones);
    cout << endl << "AGG POSICION:" << endl;
    aggPosicion.poblacion[0].ImprimirCromosoma();
    /////////////////////////////////////////////////////// AGG OX
    Cromosoma::SetSemilla(semilla);
    Geneticos aggOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    aggOX.AGGOX(iteraciones);
    cout << endl << "AGG OX:" << endl;
    aggOX.poblacion[0].ImprimirCromosoma();
  //}
  return 0;
}
