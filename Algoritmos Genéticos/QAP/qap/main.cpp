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
    Solucion cambiarSemilla(semilla);
    //for (int semilla=1; semilla<=30; semilla++) {
      //----------------------------------------------------------------------------------------------------
      cambiarSemilla = Solucion(semilla);
      AlgoritmoGenetico generacionalPosicional(datos,0.7,0.001,50,0);
      Solucion sol_generacionalPosicional = generacionalPosicional.AlgoritmoGeneracional_Posicional();
      cout << endl << "AGG POSICION:" << endl;
      for(int i=0; i<datos.nInstalaciones ; i++){
          cout << sol_generacionalPosicional.permutacion[i] << " ";
      }
      cout << endl;
      cout << "Coste de la solución: " << sol_generacionalPosicional.coste << endl;
      //----------------------------------------------------------------------------------------------------
      cambiarSemilla = Solucion(semilla);
      AlgoritmoGenetico generacionalOX(datos,0.7,0.001,50,0);
      Solucion sol_generacionalOX = generacionalOX.AlgoritmoGeneracional_OX();
      cout << endl << "AGG OX:" << endl;
      for(int i=0; i<datos.nInstalaciones ; i++){
          cout << sol_generacionalOX.permutacion[i] << " ";
      }
      cout << endl;
      cout << "Coste de la solución: " << sol_generacionalOX.coste << endl;
    //}

    return 0;
}
