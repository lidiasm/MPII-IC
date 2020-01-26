#include "geneticos.h"
// Constructor
Geneticos::Geneticos(DatosFichero &dat, float pC, float pM, int tam) {
  datos = dat;
  probCruce = pC;
  probMutacion = pM;
  // Inicializamos la población
  poblacion.resize(tam);
  for (int i=0; i<poblacion.size(); i++) {
    poblacion[i].InicializarSolucion(dat);
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
  }
}

// Esquema generacional del algoritmo generacional utilizando cruce basado en posición
Cromosoma Geneticos::AGGPosicion(int iteracionesTotal) {
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
      hijo1 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
      hijos.push_back(hijo1);
      hijo2 = CrucePosicion(padres[padresCruzados], padres[padresCruzados+1]);
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
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}

// Esquema generacional del algoritmo generacional utilizando cruce OX
Cromosoma Geneticos::AGGOX(int iteracionesTotal) {
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
      hijo1 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
      hijos.push_back(hijo1);
      hijo2 = CruceOX(padres[padresCruzados], padres[padresCruzados+1]);
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
  }
  // Se ordena la población final
  OrdenarPoblacion(poblacion);
}