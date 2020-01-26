#include "datosfichero.h"
#include "geneticos.h"

using namespace std;

int main(int argc, char *argv[]) {
  int iteraciones = 50000;
  float probCruceAGG = 0.7;
  float probMutacion = 0.001;
  int tamPoblacion = 50;

  // Leemos el fichero
  char* fichero = argv[1];
  DatosFichero datos(fichero);
  // Establecemos la semilla del argumento
  //int semilla = atoi(argv[2]);
  //Cromosoma cambiarSemilla(semilla);
  for (int semilla=1; semilla<=30; semilla++) {
    cout << endl << "semilla " << semilla << endl;
    //----------------------------------------------------------------------------------------------------
    Cromosoma cambiarSemilla(semilla);
    cambiarSemilla = Cromosoma(semilla);
    Geneticos aggPosicion(datos, probCruceAGG, probMutacion, tamPoblacion);
    aggPosicion.AGGPosicion(iteraciones);
    cout << endl << "AGG POSICION:" << endl;
    aggPosicion.poblacion[0].ImprimirCromosoma();
    //----------------------------------------------------------------------------------------------------
    cambiarSemilla = Cromosoma(semilla);
    Geneticos aggOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    aggOX.AGGOX(iteraciones);
    cout << endl << "AGG OX:" << endl;
    aggOX.poblacion[0].ImprimirCromosoma();
  }

    return 0;
}
