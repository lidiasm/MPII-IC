#include "datosfichero.h"
#include "geneticos.h"

using namespace std;

int main(int argc, char *argv[])
{
    //Abrir fichero y almacenar su información
    char * nombre=argv[1];
    DatosFichero datos(nombre);

    //Establecer semilla
    int semilla = atoi(argv[2]);
    Cromosoma cambiarSemilla(semilla);
    //for (int semilla=1; semilla<=30; semilla++) {
      //----------------------------------------------------------------------------------------------------
      cambiarSemilla = Cromosoma(semilla);
      AlgoritmoGenetico generacionalPosicional(datos,0.7,0.001,50,0);
      Cromosoma sol_generacionalPosicional = generacionalPosicional.AlgoritmoGeneracional_Posicional();
      cout << endl << "AGG POSICION:" << endl;
      for(int i=0; i<datos.nInstalaciones ; i++){
          cout << sol_generacionalPosicional.solucion[i] << " ";
      }
      cout << endl;
      cout << "fitness de la solución: " << sol_generacionalPosicional.fitness << endl;
      //----------------------------------------------------------------------------------------------------
      cambiarSemilla = Cromosoma(semilla);
      AlgoritmoGenetico generacionalOX(datos,0.7,0.001,50,0);
      Cromosoma sol_generacionalOX = generacionalOX.AlgoritmoGeneracional_OX();
      cout << endl << "AGG OX:" << endl;
      for(int i=0; i<datos.nInstalaciones ; i++){
          cout << sol_generacionalOX.solucion[i] << " ";
      }
      cout << endl;
      cout << "fitness de la solución: " << sol_generacionalOX.fitness << endl;
    //}

    return 0;
}
