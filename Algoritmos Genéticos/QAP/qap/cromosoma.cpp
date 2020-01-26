#include "cromosoma.h"
#include "datosfichero.h"

#include "pseudoaleatorio.h"

Solucion::Solucion()
{
    permutacion = vector<int>(0);
    coste = 0;
}

Solucion::Solucion(int &semilla)
{
    Seed = semilla;
    cout << "Cambiando semilla a -> " << Seed << endl;
}

void Solucion::calcularCoste(DatosFichero &datos)
{
    int costo_acumulado=0;
    for(int i=0; i<datos.nInstalaciones; i++){
        for(unsigned int j=0; j<permutacion.size(); j++){
            if(j!=i){
                costo_acumulado += datos.flujos[i][j]*datos.distancias[permutacion[i]][permutacion[j]];
            }
        }
    }

    coste=costo_acumulado;

}

void Solucion::solucionRandom(DatosFichero &datos)
{
    permutacion.resize(datos.nInstalaciones,datos.nInstalaciones);

    int cont = 0, random_num;
    vector<int>::iterator it=permutacion.begin();

    while(cont<datos.nInstalaciones){
        random_num = Randint(0,datos.nInstalaciones-1);
        it=find(permutacion.begin(), permutacion.end(), random_num);

        while(it!=permutacion.end()){
            random_num = Randint(0,datos.nInstalaciones-1);
            it=find(permutacion.begin(), permutacion.end(), random_num);

        }

        permutacion[cont] = random_num;
        cont++;

    }

    calcularCoste(datos);
}

int Solucion::ValorAleatorio(int topeInferior, int topeSuperior){
    int random_num = Randint(topeInferior,topeSuperior);
    return random_num;
}

void Solucion::OperadorIntercambio(int r, int s){
    swap(permutacion[r],permutacion[s]);
}