#include "datosfichero.h"
#include "geneticos.h"
#include "busquedalocal.h"
#include "greedy.h"

using namespace std;

int main(int argc, char *argv[]) {
  int iteraciones = 50000;
  float probCruceAGG = 0.7;
  float probMutacion = 0.001;
  int tamPoblacion = 20;
  int semillaMax = 35;
  int semilla = 33; // Semilla por defectos
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

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// G E N É T I C OS /////////////////////////////
  // cout << "AGG POSICIÓN POBLACIÓN INICIAL ALEATORIA" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos aggPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // aggPos.AlgoritmoGeneracional(iteraciones, "POSICION");
  // cout << aggPos.poblacion[0].fitness<< endl;
  // cout << "AGG POSICIÓN POBLACIÓN INICIAL GREEDY" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos aggPosGreedy(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  // aggPosGreedy.AlgoritmoGeneracional(iteraciones, "POSICION");
  // cout << aggPosGreedy.poblacion[0].fitness<< endl;
  //
  // cout << "AGG OX POBLACIÓN INICIAL ALEATORIA" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos aggOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // aggOX.AlgoritmoGeneracional(iteraciones, "OX");
  // cout << aggOX.poblacion[0].fitness<< endl;
  // cout << "AGG OX POBLACIÓN INICIAL GREEDY" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos aggOXGreedy(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  // aggOXGreedy.AlgoritmoGeneracional(iteraciones, "OX");
  // cout << aggOXGreedy.poblacion[0].fitness<< endl;

  // cout << "AGE POSICIÓN POBLACIÓN INICIAL ALEATORIA" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos agePos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // agePos.AlgoritmoEstacionario(iteraciones, "POSICION");
  // //cout << agePos.poblacion[0].fitness<< endl;
  // cout << "AGE POSICIÓN POBLACIÓN INICIAL GREEDY" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos agePosGreedy(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  // agePosGreedy.AlgoritmoEstacionario(iteraciones, "POSICION");
  // //cout << agePosGreedy.poblacion[0].fitness<< endl;
  //
  // cout << "AGE OX POBLACIÓN INICIAL ALEATORIA" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos ageOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // ageOX.AlgoritmoEstacionario(iteraciones, "OX");
  // //cout << ageOX.poblacion[0].fitness<< endl;
  // cout << "AGE OX POBLACIÓN INICIAL GREEDY" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos ageOXGreedy(datos, probCruceAGG, probMutacion, tamPoblacion, true, "S");
  // ageOXGreedy.AlgoritmoEstacionario(iteraciones, "OX");
  //cout << ageOXGreedy.poblacion[0].fitness<< endl;

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// M E M É T I C O S /////////////////////////////
  // cout << endl << "MEMÉTICO TOTAL AGG OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoTotalAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoTotalAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "1.0");
  // //cout << memeticoTotalAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% AGG OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoRandomAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoRandomAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "0.1");
  // //cout << memeticoRandomAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% MEJORES AGG OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoMejoresAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoMejoresAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "0.1M");
  // //cout << memeticoMejoresAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO TOTAL AGG POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoTotalAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoTotalAGGPos.MemeticoAGG(iteraciones, generacionMemetico, true, "1.0");
  // //cout << memeticoTotalAGGPos.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% AGG POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoRandomAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoRandomAGGPos.MemeticoAGG(iteraciones, generacionMemetico, true, "0.1");
  // //cout << memeticoRandomAGGPos.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% MEJORES AGG POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoMejoresAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoMejoresAGGPos.MemeticoAGG(iteraciones, generacionMemetico, true, "0.1M");
  //cout << memeticoMejoresAGGPos.poblacion[0].fitness<< endl;

  // cout << endl << "MEMÉTICO TOTAL AGE OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoTotalAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoTotalAGGOX.MemeticoAGE(iteraciones, generacionMemetico, false, "1.0");
  // //cout << memeticoTotalAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% AGE OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoRandomAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoRandomAGGOX.MemeticoAGE(iteraciones, generacionMemetico, false, "0.1");
  // //cout << memeticoRandomAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% MEJORES AGE OX" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoMejoresAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoMejoresAGGOX.MemeticoAGE(iteraciones, generacionMemetico, false, "0.1M");
  // //cout << memeticoMejoresAGGOX.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO TOTAL AGE POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoTotalAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoTotalAGGPos.MemeticoAGE(iteraciones, generacionMemetico, true, "1.0");
  // //cout << memeticoTotalAGGPos.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% AGE POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoRandomAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoRandomAGGPos.MemeticoAGE(iteraciones, generacionMemetico, true, "0.1");
  // //cout << memeticoRandomAGGPos.poblacion[0].fitness<< endl;
  //
  // cout << endl << "MEMÉTICO 10% MEJORES AGE POSICION" << endl;
  // Cromosoma::SetSemilla(semilla);
  // Geneticos memeticoMejoresAGGPos(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
  // memeticoMejoresAGGPos.MemeticoAGE(iteraciones, generacionMemetico, true, "0.1M");

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////////// B A L D W I N I A N O S /////////////////////////////
  cout << "AGG POSICIÓN BALDWINIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos aggBaldwiniano(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
  aggBaldwiniano.AlgoritmoGeneracional(iteraciones, "POSICION");

  cout << "AGG OX BALDWINIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos aggBaldwinianoOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
  aggBaldwinianoOX.AlgoritmoGeneracional(iteraciones, "OX");

  cout << "AGE POSICIÓN BALDWINIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageBaldwiniano(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
  ageBaldwiniano.AlgoritmoEstacionario(iteraciones, "POSICION");

  cout << "AGE OX BALDWINIANO" << endl;
  Cromosoma::SetSemilla(semilla);
  Geneticos ageBaldwinianoOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
  ageBaldwinianoOX.AlgoritmoEstacionario(iteraciones, "OX");

  // //////////////////////////////////////////////////////// GREEDY CONSTRUCTIVO
  // Greedy greedy();
  // greedy.GreedyConstructivo(datos);
  // cout << "GREEDY" << endl;
  // greedy.solucionGreedy.ImprimirCromosoma();
  // for (int semilla=1; semilla<=semillaMax; semilla++) {
  //   cout << endl << "semilla " << semilla << endl;
  //   /////////////////////////////////////////////////////// BL
  //   Cromosoma::SetSemilla(semilla);
  //   BusquedaLocal buquedaL(datos);
  //   buquedaL.BL(iteraciones);
  //   cout << "BL" << endl;
  //   buquedaL.solucionBL.ImprimirCromosoma();

  //}
  return 0;
}
