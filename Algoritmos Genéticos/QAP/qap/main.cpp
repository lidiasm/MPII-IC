#include "datosfichero.h"
#include "geneticos.h"
#include "busquedalocal.h"
#include "greedy.h"

using namespace std;

int main(int argc, char *argv[]) {
  int iteraciones = 50000;
  float probCruceAGG = 0.7;
  float probMutacion = 0.001;
  int tamPoblacion = 50;
  int semillaMax = 30;
  int semilla = 29; // Semilla por defectos
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
    // /////////////////////////////////////////////////////// AGG POSICIÓN
    // cout << endl << "AGG POSICION:" << endl;
    // Cromosoma::SetSemilla(semilla);
    // Geneticos aggPosicion(datos, probCruceAGG, probMutacion, tamPoblacion, false, "S");
    // aggPosicion.AlgoritmoGeneracional(iteraciones, "POSICION");
    // aggPosicion.poblacion[0].ImprimirCromosoma();

    cout << endl << "AGG POSICION baldwiniana:" << endl;
    Cromosoma::SetSemilla(semilla);
    Geneticos aggPosicion(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    aggPosicion.AlgoritmoGeneracional(iteraciones, "POSICION");
    aggPosicion.poblacion[0].ImprimirCromosoma();

    cout << endl << "AGG OX baldwiniana:" << endl;
    Cromosoma::SetSemilla(semilla);
    Geneticos aggPosicion2(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    aggPosicion2.AlgoritmoGeneracional(iteraciones, "OX");
    aggPosicion2.poblacion[0].ImprimirCromosoma();

    cout << endl << "AGE POSICION baldwiniana:" << endl;
    Cromosoma::SetSemilla(semilla);
    Geneticos agePosicion(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    agePosicion.AlgoritmoEstacionario(iteraciones, "POSICION");
    agePosicion.poblacion[0].ImprimirCromosoma();

    cout << endl << "AGE OX baldwiniana:" << endl;
    Cromosoma::SetSemilla(semilla);
    Geneticos agePosicion2(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    agePosicion2.AlgoritmoEstacionario(iteraciones, "OX");
    agePosicion2.poblacion[0].ImprimirCromosoma();
    // /////////////////////////////////////////////////////// AGG OX
    // Cromosoma::SetSemilla(semilla);
    // Geneticos aggOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    // aggOX.AlgoritmoGeneracional(iteraciones, "OX");
    // cout << endl << "AGG OX:" << endl;
    // aggOX.poblacion[0].ImprimirCromosoma();
    // /////////////////////////////////////////////////////// AGE POSICIÓN
    // Cromosoma::SetSemilla(semilla);
    // Geneticos agePosicion(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    // agePosicion.AlgoritmoEstacionario(iteraciones, "POSICION");
    // cout << endl << "AGE POSICIÓN: " << endl;
    // agePosicion.poblacion[0].ImprimirCromosoma();
    // /////////////////////////////////////////////////////// AGE OX
    // Cromosoma::SetSemilla(semilla);
    // Geneticos ageOX(datos, probCruceAGG, probMutacion, tamPoblacion, false, "B");
    // ageOX.AlgoritmoEstacionario(iteraciones, "OX");
    // cout << endl << "AGE OX: " << endl;
    // ageOX.poblacion[0].ImprimirCromosoma();
  // }
    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////// MEMÉTICO AGG POSICIÓN
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoTotalAGGP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoTotalAGGP.MemeticoAGG(iteraciones, generacionMemetico, true, "1.0");
    // cout << endl << "MEMÉTICO TOTAL AGG POSICIÓN" << endl;
    // memeticoTotalAGGP.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoRandomAGGP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoRandomAGGP.MemeticoAGG(iteraciones, generacionMemetico, true, "0.1");
    // cout << endl << "MEMÉTICO 10% AGG POSICIÓN" << endl;
    // memeticoRandomAGGP.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoMejoresAGGP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoMejoresAGGP.MemeticoAGG(iteraciones, generacionMemetico, true, "0.1M");
    // cout << endl << "MEMÉTICO 10% MEJORES AGG POSICIÓN" << endl;
    // memeticoMejoresAGGP.poblacion[0].ImprimirCromosoma();

    // //////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////// MEMÉTICO AGG OX
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoTotalAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoTotalAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "1.0");
    // cout << endl << "MEMÉTICO TOTAL AGG OX" << endl;
    // memeticoTotalAGGOX.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoRandomAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoRandomAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "0.1");
    // cout << endl << "MEMÉTICO 10% AGG OX" << endl;
    // memeticoRandomAGGOX.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoMejoresAGGOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoMejoresAGGOX.MemeticoAGG(iteraciones, generacionMemetico, false, "0.1M");
    // cout << endl << "MEMÉTICO 10% MEJORES AGG OX" << endl;
    // memeticoMejoresAGGOX.poblacion[0].ImprimirCromosoma();
    //
    // //////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////// MEMÉTICO AGE POSICIÓN
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoTotalAGEP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoTotalAGEP.MemeticoAGE(iteraciones, generacionMemetico, true, "1.0");
    // cout << endl << "MEMÉTICO TOTAL AGE POSICIÓN" << endl;
    // memeticoTotalAGEP.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoRandomAGEP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoRandomAGEP.MemeticoAGE(iteraciones, generacionMemetico, true, "0.1");
    // cout << endl << "MEMÉTICO 10% AGE POSICIÓN" << endl;
    // memeticoRandomAGEP.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoMejoresAGEP(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoMejoresAGEP.MemeticoAGE(iteraciones, generacionMemetico, true, "1.0M");
    // cout << endl << "MEMÉTICO 10% MEJORES AGE POSICIÓN" << endl;
    // memeticoMejoresAGEP.poblacion[0].ImprimirCromosoma();
    //
    // //////////////////////////////////////////////////////////////////////////////
    // ///////////////////////////////////// MEMÉTICO AGE OX
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoTotalAGEOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoTotalAGEOX.MemeticoAGE(iteraciones, generacionMemetico, false, "1.0");
    // cout << endl << "MEMÉTICO TOTAL AGE OX" << endl;
    // memeticoTotalAGEOX.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoRandomAGEOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoRandomAGEOX.MemeticoAGE(iteraciones, generacionMemetico, false, "0.1");
    // cout << endl << "MEMÉTICO 10% AGE OX" << endl;
    // memeticoRandomAGEOX.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoMejoresAGEOX(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoMejoresAGEOX.MemeticoAGE(iteraciones, generacionMemetico, false, "1.0M");
    // cout << endl << "MEMÉTICO 10% MEJORES AGE OX" << endl;
    // memeticoMejoresAGEOX.poblacion[0].ImprimirCromosoma();

    ///////////////////////////////////////////////////////////////////////////
    ////////////////////////////////// MEMÉTICO ORIGINAL
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoCompleto(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoCompleto.Memetico(iteraciones, generacionMemetico, "1.0");
    // cout << endl << "MEMÉTICO STANDARD COMPLETO" << endl;
    // memeticoCompleto.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoRandom(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoRandom.Memetico(iteraciones, generacionMemetico, "0.1");
    // cout << endl << "MEMÉTICO STANDARD RANDOM" << endl;
    // memeticoRandom.poblacion[0].ImprimirCromosoma();
    //
    // Cromosoma::SetSemilla(semilla);
    // Geneticos memeticoMejores(datos, probCruceAGG, probMutacion, tamPoblacion);
    // memeticoMejores.Memetico(iteraciones, generacionMemetico, "0.1M");
    // cout << endl << "MEMÉTICO STANDARD MEJORES" << endl;
    // memeticoMejores.poblacion[0].ImprimirCromosoma();

  //}
  return 0;
}
