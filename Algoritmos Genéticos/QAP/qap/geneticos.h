#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include "cromosoma.h"
#include "datosfichero.h"

class AlgoritmoGenetico
{
public:
    vector<Cromosoma> poblacion;
    DatosFichero datos;
    float probabilidadCruce;
    float probabilidadMutacion;
    int nEsperadoCruces;
    int nEsperadoGenesMutados;
    float probabilidadPLS;
    float tiempo;
    int llamadasFuncionObjetivo; //condición de parada

    int tamPoblacion; //numero de individuos en la población

    void ordenarPoblacion(vector<Cromosoma>&pobl);

    AlgoritmoGenetico(DatosFichero &dat, float probCruce, float probMutacion, int n, float pls);

    Cromosoma AlgoritmoGeneracional_Posicional();
    Cromosoma AlgoritmoEstacionario_Posicional();

    Cromosoma AlgoritmoGeneracional_OX();
    Cromosoma AlgoritmoEstacionario_OX();

    //Cromosoma AlgoritmoMemetico();

    //Función para selección
    int seleccionTorneoBinario();

    //Funciones para operadores de cruce
    Cromosoma OperadorCrucePosicion(Cromosoma padre1, Cromosoma padre2);
    Cromosoma OperadorCruceOX(Cromosoma padre1, Cromosoma padre2);
    //Función para mutación
    void Mutacion(vector<Cromosoma> & poblacionMutar);
};

#endif // ALGORITMOGENETICO_H
