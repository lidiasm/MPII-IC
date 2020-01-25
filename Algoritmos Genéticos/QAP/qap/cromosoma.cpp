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

void Solucion::calcularCoste(Datos &datos)
{
    int costo_acumulado=0;
    for(int i=0; i<datos.n; i++){
        for(unsigned int j=0; j<permutacion.size(); j++){
            if(j!=i){
                costo_acumulado += datos.f[i][j]*datos.d[permutacion[i]][permutacion[j]];
            }
        }
    }

    coste=costo_acumulado;

}

void Solucion::solucionRandom(Datos &datos)
{
    permutacion.resize(datos.n,datos.n);

    int cont = 0, random_num;
    vector<int>::iterator it=permutacion.begin();

    while(cont<datos.n){
        random_num = Randint(0,datos.n-1);
        it=find(permutacion.begin(), permutacion.end(), random_num);

        while(it!=permutacion.end()){
            random_num = Randint(0,datos.n-1);
            it=find(permutacion.begin(), permutacion.end(), random_num);

        }

        permutacion[cont] = random_num;
        cont++;

    }

    calcularCoste(datos);
}

int Solucion::incrementoCoste(Datos &datos, int &r, int &s){

    int costo_acumulado=0;

    for(int j=0; j<datos.n; j++){
        if(j!=r && j!=s){
            costo_acumulado +=
            datos.f[r][j]*(datos.d[permutacion[s]][permutacion[j]]-datos.d[permutacion[r]][permutacion[j]]) +
            datos.f[s][j]*(datos.d[permutacion[r]][permutacion[j]]-datos.d[permutacion[s]][permutacion[j]]) +
            datos.f[j][r]*(datos.d[permutacion[j]][permutacion[s]]-datos.d[permutacion[j]][permutacion[r]]) +
            datos.f[j][s]*(datos.d[permutacion[j]][permutacion[r]]-datos.d[permutacion[j]][permutacion[s]]);
        }
    }

    return costo_acumulado;
}

int Solucion::ValorAleatorio(int topeInferior, int topeSuperior){
    int random_num = Randint(topeInferior,topeSuperior);
    return random_num;
}

void Solucion::OperadorIntercambio(int r, int s){
    swap(permutacion[r],permutacion[s]);
}


