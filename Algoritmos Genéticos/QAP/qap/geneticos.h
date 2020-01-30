#ifndef GENETICOS_H
#define GENETICOS_

#include "cromosoma.h"
#include "datosfichero.h"
#include "busquedalocal.h"
#include "greedy.h"

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
    // Posibles variantes: standard, baldwiniana
    // En función de la variante establecida se calculará el fitness con un método
    // distinto
    string variante;
    // Objeto que nos permitirá acceder a los métodos Greedy, en particular a
    // la variante 2-opt para ejecutar la variante baldwiniana.
    Greedy algGreedy;

    ////////////////////////////////////////////////////////////////////////////
    // MÉTODOS
    Geneticos(DatosFichero &dat, float pC, float pM, int tam, bool iniciarGreedy, string var);
    void OrdenarPoblacion(vector<Cromosoma> &pob);
    // Operador de selección de los padres
    int TorneoBinario();
    // Operadores de cruce
    Cromosoma CrucePosicion(Cromosoma c1, Cromosoma c2);
    Cromosoma CruceOX(Cromosoma c1, Cromosoma c2);
    // Operadores de mutación
    void Mutacion(vector<Cromosoma> &pob);
    void MutacionEstacionarios(vector<Cromosoma> &pob);

    ////////////////////////////////////////////////////////////////////////////
    // Algoritmos Genéticos Generacionales: cruce posición y OX
    void AlgoritmoGeneracional(int iteracionesTotal, string cruce);
    // Algoritmos Genéticos Estacionarios: cruce posición y OX
    void AlgoritmoEstacionario(int iteracionesTotal, string cruce);
    ////////////////////////////////////////////////////////////////////////////

    // MEMÉTICOS
    void MemeticoAGG(int iteracionesTotal, int generacionesBL,
      bool crucePosicion, string pLS);
    void MemeticoAGE(int iteracionesTotal, int generacionesBL,
      bool crucePosicion, string pLS);


    void CalcularFitnessBaldwiniano(vector<Cromosoma> &pob);
};

#endif
