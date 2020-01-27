#ifndef GENETICOS_H
#define GENETICOS_

#include "cromosoma.h"
#include "datosfichero.h"

class Geneticos
{
public:
    vector<Cromosoma> poblacion;
    DatosFichero datos;
    float probCruce;
    float probMutacion;
    int crucesARealizar;
    int genesAMutar;
    // Lo ponemos como atributo para que cada vez que se llame a la función objetivo
    // se aumente una unidad. Este es el criterio de parada.
    int nIteraciones;

    ////////////////////////////////////////////////////////////////////////////
    // MÉTODOS
    Geneticos(DatosFichero &dat, float pC, float pM, int tam);
    void OrdenarPoblacion(vector<Cromosoma> &pob);
    // Operador de selección de los padres
    int TorneoBinario();
    // Operadores de cruce
    Cromosoma CrucePosicion(Cromosoma c1, Cromosoma c2);
    Cromosoma CruceOX(Cromosoma c1, Cromosoma c2);
    // Operador de mutación
    void Mutacion(vector<Cromosoma> &pob);

    // ALGORITMO GENERACIONAL CON CRUCE BASADO EN POSICIÓN
    Cromosoma AGGPosicion(int iteracionesTotal);
    // ALGORITMO GENERACIONAL CON CRUCE OX
    Cromosoma AGGOX(int iteracionesTotal);
    // ALGORITMO ESTACIONARIO CON CRUCE BASADO EN POSICIÓN
    Cromosoma AGEPosicion(int iteracionesTotal);
};

#endif
