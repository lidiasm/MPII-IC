#include "geneticos.h"

Geneticos::Geneticos(DatosFichero &dat, float pC, float pM, int tam,
  bool iniciarGreedy, string var) {
  datos = dat;
  probCruce = pC;
  probMutacion = pM;
  variante = var;
  // Inicializamos la población
  poblacion.resize(tam);
  // Población inicial aleatoria
  if (!iniciarGreedy) {
    for (int i=0; i<poblacion.size(); i++) {
      poblacion[i].InicializarSolucion(dat);
    }
  }
  else {
    // Población inicial a partir de soluciones Greedy
    for (int i=0; i<poblacion.size(); i++) {
      Greedy g;
      g.GreedyConstructivo(datos);
      poblacion[i] = g.solucionGreedy;
      poblacion[i].InicializarSolucion(dat);
    }
  }
  // Si la variante es baldwiniana, se calcula el fitness con el algoritmo 2-opt
  for (int i=0; i<poblacion.size(); i++) {
    algGreedy.Greedy2opt(poblacion[i], datos);
    // Actualizamos su fitness
    poblacion[i].fitness = algGreedy.solucionGreedy.fitness;
  }
  // Calculamos el número de cruces a realizar en función de la probabilidad establecida
  // y el tamaño de la población
  crucesARealizar = probCruce*(poblacion.size()/2) + 1;
  // Y calculamos cuántos genes se deben mutar por su probabilidad, tamaño de la
  // población y el número de datos recopilados
  genesAMutar = probMutacion*(poblacion.size()*datos.nInstalaciones);
}

// Ordenamos la población para que sea más fácil obtener la solución óptima (que será el primer cromosoma)
void Geneticos::OrdenarPoblacion(vector<Cromosoma> &pob) {
  Cromosoma temp;
  for (int i=1; i<pob.size(); i++) {
    for (int j=i; j>0; j--) {
      if (pob[j].fitness < pob[j-1].fitness) {
        temp = pob[j];
        pob[j] = pob[j-1];
        pob[j-1] = temp;
      }
    }
  }
}

// Selección del mejor entre dos. Como la población está ordenada por coste
// basta con quedarse con el número aleatorio menor de ambos.
int Geneticos::TorneoBinario() {
  int padre1 = Cromosoma::GenerarNumeroRandom(0, poblacion.size()-1);
  int padre2 = Cromosoma::GenerarNumeroRandom(0, poblacion.size()-1);
  while (padre1 == padre2) {
    padre2 = Cromosoma::GenerarNumeroRandom(0, poblacion.size()-1);
  }
  if (padre1 < padre2) return padre1;
  return padre2;
}

// Operador de cruce basado en la posición. Mantiene los genes coincidentes en
// el hijo y luego lo completa de forma aleatoria sin repetir.
Cromosoma Geneticos::CrucePosicion(Cromosoma c1, Cromosoma c2) {
  Cromosoma hijo;
  int gen;
  // Inicializamos el hijo a -1 con tantos elementos como los padres
  hijo.solucion.resize(c1.solucion.size(), -1);
  // Hereda las posiciones coincidentes de los padres
  for (int i=0; i<c1.solucion.size(); i++) {
    if (c1.solucion[i] == c2.solucion[i]) {
      hijo.solucion[i] = c1.solucion[i];
    }
  }
  // Completamos al hijo de forma aleatoria sin repetir
  vector<int>::iterator it = hijo.solucion.begin();
  for (int i=0; i<hijo.solucion.size(); i++) {
    if (hijo.solucion[i] == -1) {
      gen = Cromosoma::GenerarNumeroRandom(0, hijo.solucion.size()-1);
      it = find(hijo.solucion.begin(), hijo.solucion.end(), gen);
      // Sin genes repetidos
      while (it != hijo.solucion.end()) {
        gen = Cromosoma::GenerarNumeroRandom(0, hijo.solucion.size()-1);
        it = find(hijo.solucion.begin(), hijo.solucion.end(), gen);
      }
      hijo.solucion[i] = gen;
    }
  }
  hijo.CalcularFitness(datos);
  if (variante == "B") {
    algGreedy.Greedy2opt(hijo, datos);
    // Actualizamos su fitness
    hijo.fitness = algGreedy.solucionGreedy.fitness;
  }

  return hijo;
}

// Operador de cruce OX. Seleccionamos una subcadena central del primer padre y
// se la transmitimos al hijo. Después lo completamos con el padre2.
Cromosoma Geneticos::CruceOX(Cromosoma c1, Cromosoma c2) {
  Cromosoma hijo;
  int gen;
  // Inicializamos el hijo a -1 con tantos elementos como los padres
  hijo.solucion.resize(c1.solucion.size(), -1);
  // Obtenemos la subcadena central del padre 1
  int medio = c1.solucion.size()/2;
  int primero = medio - (medio/2);
  int ultimo = medio + (medio/2);
  for (int i=primero; i<=ultimo; i++) {
    hijo.solucion[i] = c1.solucion[i];
  }
  // Completamos al hijo con el segundo padre a partir del último gen añadido
  int indiceHijo = ultimo+1, indicePadre = ultimo+1;
  while (find(hijo.solucion.begin(), hijo.solucion.end(),-1) != hijo.solucion.end()) {
    if (indiceHijo == hijo.solucion.size()) indiceHijo = 0;
    if (indicePadre == c2.solucion.size()) indicePadre = 0;

    while (indiceHijo < hijo.solucion.size() && indicePadre < c2.solucion.size()) {
      if (hijo.solucion[indiceHijo] == -1) {
        if (find(hijo.solucion.begin(), hijo.solucion.end(), c2.solucion[indicePadre]) == hijo.solucion.end()) {
          hijo.solucion[indiceHijo] = c2.solucion[indicePadre];
          indiceHijo++;
        }
        indicePadre++;
      }
      else
        indiceHijo++;
    }
  }
  // Evaluamos al nuevo hijo generado
  hijo.CalcularFitness(datos);
  if (variante == "B") {
    algGreedy.Greedy2opt(hijo, datos);
    // Actualizamos su fitness
    hijo.fitness = algGreedy.solucionGreedy.fitness;
  }
  return hijo;
}

// Operador de mutación. Intercambia dos genes elegidos al azar de un hijo
// elegido también al azar.
void Geneticos::Mutacion(vector<Cromosoma> &pob) {
  int gen1, gen2, hijoAMutar;
  for (int i=0; i<genesAMutar; i++) {
    nIteraciones++;
    gen1 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
    gen2 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
    while (gen1 == gen2 ) {
      gen2 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
    }
    // Elegimos al hijo a mutar de forma aleatoria
    hijoAMutar = Cromosoma::GenerarNumeroRandom(0, pob.size()-1);
    pob[hijoAMutar].IntercambiarGenes(gen1, gen2);
    pob[hijoAMutar].CalcularFitness(datos);
    if (variante == "B") {
      algGreedy.Greedy2opt(pob[hijoAMutar], datos);
      // Actualizamos su fitness
      pob[hijoAMutar].fitness = algGreedy.solucionGreedy.fitness;
    }
  }
}
// Operador de mutación para los Algoritmos Genéticos en los que solamente
// se mutan dos genes de forma aleatoria.
void Geneticos::MutacionEstacionarios(vector<Cromosoma> &pob) {
  int gen1, gen2, hijoAMutar;
  nIteraciones++;
  gen1 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
  gen2 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
  while (gen1 == gen2 ) {
    gen2 = Cromosoma::GenerarNumeroRandom(0, datos.nInstalaciones-1);
  }
  // Elegimos al hijo a mutar de forma aleatoria
  hijoAMutar = Cromosoma::GenerarNumeroRandom(0, pob.size()-1);
  pob[hijoAMutar].IntercambiarGenes(gen1, gen2);
  pob[hijoAMutar].CalcularFitness(datos);
  if (variante == "B") {
    algGreedy.Greedy2opt(pob[hijoAMutar], datos);
    // Actualizamos su fitness
    pob[hijoAMutar].fitness = algGreedy.solucionGreedy.fitness;
  }
}

// Esquema generacional del Algoritmo Generacional.
// Puede utilizar un operador de cruce basado en posición u OX
// Puede utilizar una de las tres tipos de variantes: standard, baldwiniana
void Geneticos::AlgoritmoGeneracional(int iteracionesTotal, string cruce) {
  // Inicializamos a 0 el número de llamadas a la función objetivo.
  nIteraciones = 0;
  while (nIteraciones < iteracionesTotal) {
    vector<Cromosoma> padres, hijos;
    // Ordenamos la población actual
    OrdenarPoblacion(poblacion);
    // Selección de tantos padres como cromosomas haya en la población
    int padreSeleccionado;
    for (int i=0; i<poblacion.size(); i++) {
      padreSeleccionado = TorneoBinario();
      padres.push_back(poblacion[padreSeleccionado]);
    }
    // Cruzamos los padres con el operador de cruce basado en la posición
    Cromosoma hijo1, hijo2;
    int padresCruzados = 0;
    for (int i=0; i<crucesARealizar; i++) {
      if (cruce == "POSICION") {
        hijo1 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      }
      else {
        hijo1 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
      }
      hijos.push_back(hijo1);
      hijos.push_back(hijo2);
      // Dos padres cruzados
      padresCruzados += 2;
      // Dos hijos evaluados
      nIteraciones += 2;
    }

    // Completamos la población con los padres que no se han cruzado
    for (int i=padresCruzados; i<padres.size(); i++) {
      hijos.push_back(padres[i]);
    }
    // Mutamos la población actual
    Mutacion(hijos);
    // Ordenamos de nuevo la población
    OrdenarPoblacion(hijos);
    // Elitismo: el mejor padre debe sobrevivir y se sustituirá por el peor hijo
    bool mejorPadreEncontrado = false;
    for (int i=0; i<hijos.size() && !mejorPadreEncontrado; i++) {
      if (poblacion[0].solucion == hijos[i].solucion) {
        mejorPadreEncontrado = true;
      }
    }
    if (!mejorPadreEncontrado) {
      hijos[hijos.size()-1] = poblacion[0];
    }
    // Actualizamos la población
    poblacion = hijos;

    cout << "Mejor en la iteración " << nIteraciones << endl;
    poblacion[0].ImprimirCromosoma();
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}
// Esquema generacional del Algoritmo Estacionario con cruce basado en posición
void Geneticos::AlgoritmoEstacionario(int iteracionesTotal, string cruce) {
  // Inicializamos las iteraciones a realizar a 0
  nIteraciones = 0;
  // Calculamos cada cuántas generaciones se muta mediante la Esperanza Matemática.
  // Para ello consideramos la probabilidad de mutación y la suma de los genes de dos cromosomas
  int generacionAMutar = 1000/(datos.nInstalaciones*2);
  int nGeneracion = 0;
  int padre1, padre2;
  Cromosoma hijo1, hijo2;

  while (nIteraciones < iteracionesTotal) {
    vector<Cromosoma> hijos;
    nGeneracion++;
    // Ordenamos la población
    OrdenarPoblacion(poblacion);
    // Elegimos a los dos padres a cruzar mediante torneo binario
    padre1 = TorneoBinario();
    padre2 = TorneoBinario();
    // Los cruzamos obteniendo dos hijos
    if (cruce == "POSICION") {
      hijo1 = CrucePosicion(poblacion[padre1], poblacion[padre2]);
      hijo2 = CrucePosicion(poblacion[padre1], poblacion[padre2]);
    }
    else {
      hijo1 = CruceOX(poblacion[padre1], poblacion[padre2]);
      hijo2 = CruceOX(poblacion[padre1], poblacion[padre2]);
    }
    hijos.push_back(hijo1);
    hijos.push_back(hijo2);
    nIteraciones += 2;
    // Mutamos cada X generaciones calculadas
    if (nGeneracion == generacionAMutar) {
      nGeneracion = 0;
      MutacionEstacionarios(hijos);
    }
    // Reemplazamiento: incluimos los dos hijos obtenidos por los dos peores padres
    // si los hijos son mejores.
    // Para ello introducimos a los cuatro en una población, se ordenan y se introducen
    // en la población actual los dos mejores
    hijos.push_back(poblacion[poblacion.size()-1]);
    hijos.push_back(poblacion[poblacion.size()-2]);
    OrdenarPoblacion(hijos);
    poblacion[poblacion.size()-1] = hijos[0];
    poblacion[poblacion.size()-2] = hijos[1];
  }
}

// ALGORITMO MEMÉTICO 1: híbrido entre el Algoritmo Generacional con la Búsqueda Local.
// Se puede aplicar el operador de cruce basado en posición o el OX.
void Geneticos::MemeticoAGG(int iteracionesTotal, int generacionesBL,
  bool crucePosicion, string pLS) {
  // Inicializamos a 0 el número de llamadas a la función objetivo.
  nIteraciones = 0;
  // Contamos las generaciones para aplicar la búsqueda local
  int nGeneracion = 0;

  while (nIteraciones < iteracionesTotal) {
    nGeneracion++;
    vector<Cromosoma> padres, hijos;
    // Ordenamos la población actual
    OrdenarPoblacion(poblacion);
    // Selección de tantos padres como cromosomas haya en la población
    int padreSeleccionado;
    for (int i=0; i<poblacion.size(); i++) {
      padreSeleccionado = TorneoBinario();
      padres.push_back(poblacion[padreSeleccionado]);
    }
    // Cruzamos los padres con el operador de cruce basado en la posición
    Cromosoma hijo1, hijo2;
    int padresCruzados = 0;
    for (int i=0; i<crucesARealizar; i++) {
      if (crucePosicion) {
        hijo1 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      }
      else {
        hijo1 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
      }
      hijos.push_back(hijo1);
      hijos.push_back(hijo2);
      // Dos padres cruzados
      padresCruzados += 2;
      // Dos hijos evaluados
      nIteraciones += 2;
    }
    // Completamos la población con los padres que no se han cruzado
    for (int i=padresCruzados; i<padres.size(); i++) {
      hijos.push_back(padres[i]);
    }
    // Mutamos la población actual
    Mutacion(hijos);

    ///////// BÚSQUEDA LOCAL
    if (nGeneracion == generacionesBL) {
      nGeneracion = 0;
      // Búsqueda local sobre la población completa
      if (pLS == "1.0") {
        for (int i=0; i<hijos.size(); i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% aleatoriamente
      else if (pLS == "0.1") {
        vector<Cromosoma> hijosBL;
        for (int i=0; i<hijos.size()*0.1; i++) {
          int hijoSeleccionado = Cromosoma::GenerarNumeroRandom(0, hijos.size()-1);
          hijosBL.push_back(hijos[hijoSeleccionado]);
        }
        // BL con los hijos escogidos aleatoriamente
        for (int i=0; i<hijosBL.size(); i++) {
          BusquedaLocal busquedaL(datos, hijosBL[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% de los mejores
      else if (pLS == "0.1M") {
        OrdenarPoblacion(hijos);
        for (int i=0; i<hijos.size()*0.1; i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
    }

    // Ordenamos de nuevo la población
    OrdenarPoblacion(hijos);
    // Elitismo: el mejor padre debe sobrevivir y se sustituirá por el peor hijo
    bool mejorPadreEncontrado = false;
    for (int i=0; i<hijos.size() && !mejorPadreEncontrado; i++) {
      if (poblacion[0].solucion == hijos[i].solucion) {
        mejorPadreEncontrado = true;
      }
    }
    if (!mejorPadreEncontrado) {
      hijos[hijos.size()-1] = poblacion[0];
    }
    // Actualizamos la población
    poblacion = hijos;
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}

// ALGORITMO MEMÉTICO 2: híbrido entre el Algoritmo Estacionario con la Búsqueda Local.
// Se puede aplicar el operador de cruce basado en posición o el OX.
void Geneticos::MemeticoAGE(int iteracionesTotal, int generacionesBL,
  bool crucePosicion, string pLS) {
  // Inicializamos a 0 el número de llamadas a la función objetivo.
  nIteraciones = 0;
  // Contamos las generaciones para aplicar la búsqueda local
  int nGeneracion = 0;
  // Cada cuántas generaciones vamos a mutar a los hijos
  int generacionAMutar = 1000/(datos.nInstalaciones*poblacion.size());
  int nGeneracionMutar = 0;
  while (nIteraciones < iteracionesTotal) {
    nGeneracion++;
    nGeneracionMutar++;
    vector<Cromosoma> padres, hijos;
    // Ordenamos la población actual
    OrdenarPoblacion(poblacion);
    // Selección de tantos padres como cromosomas haya en la población
    int padreSeleccionado;
    for (int i=0; i<poblacion.size(); i++) {
      padreSeleccionado = TorneoBinario();
      padres.push_back(poblacion[padreSeleccionado]);
    }
    // Cruzamos los padres con el operador de cruce basado en la posición
    Cromosoma hijo1, hijo2;
    int padresCruzados = 0;
    for (int i=0; i<crucesARealizar; i++) {
      if (crucePosicion) {
        hijo1 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      }
      else {
        hijo1 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
        hijo2 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
      }
      hijos.push_back(hijo1);
      hijos.push_back(hijo2);
      // Dos padres cruzados
      padresCruzados += 2;
      // Dos hijos evaluados
      nIteraciones += 2;
    }
    // Completamos la población con los padres que no se han cruzado
    for (int i=padresCruzados; i<padres.size(); i++) {
      hijos.push_back(padres[i]);
    }
    // Mutamos la población actual
    if (nGeneracionMutar == generacionAMutar) {
      nGeneracionMutar = 0;
      MutacionEstacionarios(hijos);
    }

    ///////// BÚSQUEDA LOCAL
    if (nGeneracion == generacionesBL) {
      nGeneracion = 0;
      // Búsqueda local sobre la población completa
      if (pLS == "1.0") {
        for (int i=0; i<hijos.size(); i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% aleatoriamente
      else if (pLS == "0.1") {
        vector<Cromosoma> hijosBL;
        for (int i=0; i<hijos.size()*0.1; i++) {
          int hijoSeleccionado = Cromosoma::GenerarNumeroRandom(0, hijos.size()-1);
          hijosBL.push_back(hijos[hijoSeleccionado]);
        }
        // BL con los hijos escogidos aleatoriamente
        for (int i=0; i<hijosBL.size(); i++) {
          BusquedaLocal busquedaL(datos, hijosBL[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% de los mejores
      else if (pLS == "0.1M") {
        OrdenarPoblacion(hijos);
        for (int i=0; i<hijos.size()*0.1; i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
    }

    // Ordenamos de nuevo la población
    OrdenarPoblacion(hijos);
    // Elitismo: el mejor padre debe sobrevivir y se sustituirá por el peor hijo
    bool mejorPadreEncontrado = false;
    for (int i=0; i<hijos.size() && !mejorPadreEncontrado; i++) {
      if (poblacion[0].solucion == hijos[i].solucion) {
        mejorPadreEncontrado = true;
      }
    }
    if (!mejorPadreEncontrado) {
      hijos[hijos.size()-1] = poblacion[0];
    }
    // Actualizamos la población
    poblacion = hijos;
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}

void Geneticos::Memetico(int iteracionesTotal, int generacionesBL, string pLS) {
  // Inicializamos a 0 el número de llamadas a la función objetivo.
  nIteraciones = 0;
  // Contamos las generaciones para aplicar la búsqueda local
  int nGeneracion = 0;
  // Cada cuántas generaciones vamos a mutar a los hijos
  int generacionAMutar = 1000/(datos.nInstalaciones*poblacion.size());
  int nGeneracionMutar = 0;
  while (nIteraciones < iteracionesTotal) {
    nGeneracion++;
    nGeneracionMutar++;
    vector<Cromosoma> padres, hijos;
    // Ordenamos la población actual
    OrdenarPoblacion(poblacion);
    // Selección de tantos padres como cromosomas haya en la población
    int padreSeleccionado;
    for (int i=0; i<poblacion.size(); i++) {
      padreSeleccionado = TorneoBinario();
      padres.push_back(poblacion[padreSeleccionado]);
    }
    // Cruzamos los padres con el operador de cruce basado en la posición
    Cromosoma hijo1, hijo2;
    int padresCruzados = 0;
    for (int i=0; i<crucesARealizar; i++) {
      hijo1 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      hijo2 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      hijos.push_back(hijo1);
      hijos.push_back(hijo2);
      // Dos padres cruzados
      padresCruzados += 2;
      // Dos hijos evaluados
      nIteraciones += 2;
    }
    // Completamos la población con los padres que no se han cruzado
    for (int i=padresCruzados; i<padres.size(); i++) {
      hijos.push_back(padres[i]);
    }
    // Mutamos la población actual
    if (nGeneracionMutar == generacionAMutar) {
      nGeneracionMutar = 0;
      MutacionEstacionarios(hijos);
    }

    ///////// BÚSQUEDA LOCAL
    if (nGeneracion == generacionesBL) {
      nGeneracion = 0;
      // Búsqueda local sobre la población completa
      if (pLS == "1.0") {
        for (int i=0; i<hijos.size(); i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% aleatoriamente
      else if (pLS == "0.1") {
        vector<Cromosoma> hijosBL;
        for (int i=0; i<hijos.size()*0.1; i++) {
          int hijoSeleccionado = Cromosoma::GenerarNumeroRandom(0, hijos.size()-1);
          hijosBL.push_back(hijos[hijoSeleccionado]);
        }
        // BL con los hijos escogidos aleatoriamente
        for (int i=0; i<hijosBL.size(); i++) {
          BusquedaLocal busquedaL(datos, hijosBL[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
      // Búsqueda local sobre el 10% de los mejores
      else if (pLS == "0.1M") {
        OrdenarPoblacion(hijos);
        for (int i=0; i<hijos.size()*0.1; i++) {
          BusquedaLocal busquedaL(datos, hijos[i]);
          busquedaL.BL(400);
          hijos[i] = busquedaL.solucionBL;
          nIteraciones += busquedaL.nIteraciones;
        }
      }
    }

    // Ordenamos de nuevo la población
    OrdenarPoblacion(hijos);
    // Elitismo: el mejor padre debe sobrevivir y se sustituirá por el peor hijo
    bool mejorPadreEncontrado = false;
    for (int i=0; i<hijos.size() && !mejorPadreEncontrado; i++) {
      if (poblacion[0].solucion == hijos[i].solucion) {
        mejorPadreEncontrado = true;
      }
    }
    if (!mejorPadreEncontrado) {
      hijos[hijos.size()-1] = poblacion[0];
    }
    // Actualizamos la población
    poblacion = hijos;
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}