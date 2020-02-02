#include "datosfichero.h"
#include "geneticos.h"
#include "busquedalocal.h"
#include "greedy.h"

using namespace std;

int main(int argc, char *argv[]) {
  int iteracionesGeneticos = 200000;
  int iteracionesBaldwinianos = 50000;
  int iteracionesLamarckianos = 1000;
  float probCruceAGG = 0.7;
  float probMutacion = 0.001;
  int tamPoblacion = 20;
  int semillaMax = 35;
  int semilla = 33; // Semilla por defecto
  int generacionMemetico = 10; // Cada 10 generaciones se aplica la BL

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

  // MEJORES RESULTADOS
  cout << "AGE POSICIÓN LAMARCKIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageL(datos, probCruceAGG, probMutacion, tamPoblacion, false, "L");
  ageL.AlgoritmoEstacionario(iteracionesLamarckianos, "POSICION");
  ageL.poblacion[0].ImprimirCromosoma();

  cout << "AGE OX LAMARCKIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageLOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "L");
  ageLOX.AlgoritmoEstacionario(iteracionesLamarckianos, "OX");
  ageLOX.poblacion[0].ImprimirCromosoma();

  cout << "AGE POSICIÓN POBLACIÓN INICIAL GREEDY" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageP(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  ageP.AlgoritmoEstacionario(iteracionesGeneticos, "POSICION");
  ageP.poblacion[0].ImprimirCromosoma();

  cout << "AGE OX POBLACIÓN INICIAL GREEDY" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageOXGreedy(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  ageOXGreedy.AlgoritmoEstacionario(iteracionesGeneticos, "OX");
  ageOXGreedy.poblacion[0].ImprimirCromosoma();

  return 0;
}
