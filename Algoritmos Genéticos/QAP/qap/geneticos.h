#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include "cromosoma.h"
#include "datosfichero.h"

class AlgoritmoGenetico
{
public:
    vector<Solucion> poblacionInicial, poblacion;
    Datos datos;
    float probabilidadCruce;
    float probabilidadMutacion;
    int nEsperadoCruces;
    int nEsperadoGenesMutados;
    float probabilidadPLS;
    float tiempo;
    int llamadasFuncionObjetivo; //condición de parada

    int tamPoblacion; //numero de individuos en la población

    void ordenarPoblacion(vector<Solucion>&pobl);

    AlgoritmoGenetico(Datos &dat, float probCruce, float probMutacion, int n, float pls);

    Solucion AlgoritmoGeneracional_Posicional();
    Solucion AlgoritmoEstacionario_Posicional();

    Solucion AlgoritmoGeneracional_OX();
    Solucion AlgoritmoEstacionario_OX();

    //Solucion AlgoritmoMemetico();

    //Función para selección
    int seleccionTorneoBinario();

    //Funciones para operadores de cruce
    Solucion OperadorCrucePosicion(Solucion padre1, Solucion padre2);
    Solucion OperadorCruceOX(Solucion padre1, Solucion padre2);
    //Función para mutación
    void Mutacion(vector<Solucion> & poblacionMutar);
};

#endif // ALGORITMOGENETICO_H
