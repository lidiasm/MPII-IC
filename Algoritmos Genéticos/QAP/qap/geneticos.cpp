#include "geneticos.h"
#include <time.h>


AlgoritmoGenetico::AlgoritmoGenetico(DatosFichero &dat, float probCruce, float probMutacion, int n, float pls)
{
    //Obtengo una población de caracter aleatorio de tamaño 50
    poblacion.resize(n);
    probabilidadPLS = pls;

    for(unsigned int i=0; i<poblacion.size(); i++){
        poblacion[i].solucionRandom(dat);

    }

    tamPoblacion = n;
    datos = dat;
    probabilidadCruce = probCruce;
    probabilidadMutacion = probMutacion;

    nEsperadoCruces = probabilidadCruce*(poblacion.size()/2) + 1;


    nEsperadoGenesMutados = probabilidadMutacion*(poblacion.size()*datos.nInstalaciones);



}


//Función que realiza el torneo a dos.
//devuelve el índice de la mejor de dos soluciones escogidas al azar de entre la población
int AlgoritmoGenetico::seleccionTorneoBinario()
{
    //3 variables, las dos soluciones aleatorias y la mejor solución obtenida

    int sol1 = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //padre1
    int sol2  = poblacion[0].ValorAleatorio(0,poblacion.size()-1); //padre2

    //Como los dos padres tienen que ser diferentes, forzamos que sol2 != sol1
    while(sol1 == sol2){
       sol2 = poblacion[0].ValorAleatorio(0,poblacion.size()-1);
    }

    //Devolvemos la mejor de ellas
    if(sol1<sol2)
        return sol1;
    return sol2;


}


//Algoritmo genético estacionario con el operador de cruce posicional
Solucion AlgoritmoGenetico::AlgoritmoEstacionario_Posicional()
{
    Solucion hijoObtenido;
    llamadasFuncionObjetivo = 0;
    int generaciones_realizadas = 0 ;
    int genes = 2*datos.nInstalaciones; //2 por numero de genes
    int cada_cuanto = 1000/genes; //cada cuantas generaciones tienes que mutar los dos hijos


    clock_t start,end;
    start = clock();

    while(llamadasFuncionObjetivo < 50000){

        //Para la mutación necesito contar el número de iteraciones realizadas
        generaciones_realizadas++;

        int padre1, padre2;

        ordenarPoblacion(poblacion);
        vector<Solucion> poblacionHijos;

        //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
        padre1 = seleccionTorneoBinario();
        padre2 = seleccionTorneoBinario();


        //2. Realizo el cruce y obtengo dos hijos
        hijoObtenido = OperadorCrucePosicion(poblacion[padre1],poblacion[padre2]);
        poblacionHijos.push_back(hijoObtenido);
        llamadasFuncionObjetivo++;

        hijoObtenido = OperadorCrucePosicion(poblacion[padre1],poblacion[padre2]);
        poblacionHijos.push_back(hijoObtenido);
        llamadasFuncionObjetivo++;

        int hijoMutar, genMutar1, genMutar2;
        //3. Mutación
        if(generaciones_realizadas == cada_cuanto){
            generaciones_realizadas = 0;
            hijoMutar = hijoObtenido.ValorAleatorio(0,poblacionHijos.size()-1);
            genMutar1 = hijoObtenido.ValorAleatorio(0, hijoObtenido.permutacion.size()-1);
            genMutar2 = hijoObtenido.ValorAleatorio(0, hijoObtenido.permutacion.size()-1);

            //me aseguro que los genes a cambiar son distintos
            //NO deben coincidir
            while(genMutar1 == genMutar2){
                genMutar2 = hijoObtenido.ValorAleatorio(0,hijoObtenido.permutacion.size()-1);
            }

            //PARA MUTAR USO EL OPERADOR DE INTERCAMBIO /VECINOS
            poblacionHijos[hijoMutar].OperadorIntercambio(genMutar1,genMutar2);
            poblacionHijos[hijoMutar].calcularCoste(datos);
            llamadasFuncionObjetivo++;


        }

        //4. Sustituir por los padres
        //para facilitar los cálculos, añado los dos peores de la población a poblacionHijos, para ponerlos
        //a competir con los hijos recién generados
        poblacionHijos.push_back(poblacion[poblacion.size()-1]);
        poblacionHijos.push_back(poblacion[poblacion.size()-2]);

        ordenarPoblacion(poblacionHijos);
        poblacion[poblacion.size()-1] = poblacionHijos[0];    //el mejor de la poblacionHijos guardado en ultima pos
        poblacion[poblacion.size()-2] = poblacionHijos[1];


    }//end while

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;

    if ( poblacion[0].coste < poblacion[poblacion.size()-1].coste)
        return poblacion[0];

    return poblacion[poblacion.size()-1];
}
//--------------------------------------------------------------------------------------------------------

//Algoritmo genético generacional utilizando el operador de cruce OX
Solucion AlgoritmoGenetico::AlgoritmoGeneracional_OX()
{
    llamadasFuncionObjetivo = 50;

    clock_t start,end;
    start = clock();

    while( llamadasFuncionObjetivo < 50000){


        vector<Solucion> poblacionPadres, poblacionHijos;

        ordenarPoblacion(poblacion);

        //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
        int sol_seleccionada;
        for(int i=0; i<50; i++){
            sol_seleccionada = seleccionTorneoBinario();
            poblacionPadres.push_back(poblacion[sol_seleccionada]);
        }

        //2. Cruzo la población recién seleccionada
        int sol_cruzada=0; //la inicializo a 0 porque voy a realizar cruces de dos en dos

        Solucion hijoObtenido1, hijoObtenido2;

        for(int i=0; i<nEsperadoCruces ; i++){

            hijoObtenido1 = OperadorCruceOX(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
            poblacionHijos.push_back(hijoObtenido1);
            llamadasFuncionObjetivo++;

            hijoObtenido2 = OperadorCruceOX(poblacionPadres[sol_cruzada+1],poblacionPadres[sol_cruzada]);
            poblacionHijos.push_back(hijoObtenido2);
            llamadasFuncionObjetivo++;

            sol_cruzada+=2;

        }

        //3. Añadimos los padres que no se han cruzado a la población de los hijos
        for(unsigned int i=sol_cruzada; i< poblacionPadres.size();i++){
           poblacionHijos.push_back(poblacionPadres[i]);
        }

        //4. Muto la población de los hijos
        //Vamos a mutar nEsperadoGenesMutados
        Mutacion(poblacionHijos);

        //Ordenamos la población obtenida por menor coste
        ordenarPoblacion(poblacionHijos);

        //5. Para mantener el elitismo, si no se encuentra el mejor padre de la población
        //anterior, tenemos que añadirlo nosotros intercambiandolo por el peor de la población de
        //los hijos

        bool mejor_encontrado = false;
        for(unsigned int i = 0; i < poblacionHijos.size() && !mejor_encontrado ; i++){
            if( poblacion[0].permutacion == poblacionHijos[i].permutacion){
                mejor_encontrado=true;

            }
        }

        //Si la mejor solución de la población de partida no está incluida en la población de los hijos
        //la sustituimos por la peor encontrada en los hijos.
        if(!mejor_encontrado){
            poblacionHijos[poblacionHijos.size()-1] = poblacion[0];
        }

         poblacion = poblacionHijos;
    }//end while

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;

    if ( poblacion[0].coste < poblacion[poblacion.size()-1].coste)
        return poblacion[0];

    return poblacion[poblacion.size()-1];

}

//-------------------------------------------------------------------------------------------------------
//Algoritmo genético generacional utilizando el operador de cruce OX
Solucion AlgoritmoGenetico::AlgoritmoGeneracional_Posicional()
{

    llamadasFuncionObjetivo = 50;

    clock_t start,end;
    start = clock();
    int num = 0;
    while( llamadasFuncionObjetivo < 50000){

        vector<Solucion> poblacionPadres, poblacionHijos;

        ordenarPoblacion(poblacion);


        //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
        int sol_seleccionada;
        for(int i=0; i<50; i++){
            sol_seleccionada = seleccionTorneoBinario();
            poblacionPadres.push_back(poblacion[sol_seleccionada]);
        }


        //2. Cruzo la población recién seleccionada
        int sol_cruzada=0; //la inicializo a 0 porque voy a realizar cruces de dos en dos

        Solucion hijoObtenido1, hijoObtenido2;
        for(int i=0; i<nEsperadoCruces ; i++){

            hijoObtenido1 = OperadorCrucePosicion(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
            poblacionHijos.push_back(hijoObtenido1);
            llamadasFuncionObjetivo++;

            hijoObtenido2 = OperadorCrucePosicion(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
            poblacionHijos.push_back(hijoObtenido2);
            llamadasFuncionObjetivo++;

            sol_cruzada+=2;

        }

        //3. Añadimos los padres que no se han cruzado a la población de los hijos
        for(unsigned int i=sol_cruzada; i< poblacionPadres.size();i++){
           poblacionHijos.push_back(poblacionPadres[i]);
        }


        //4. Muto la población de los hijos
        //Vamos a mutar nEsperadoGenesMutados
        Mutacion(poblacionHijos);

        //Ordenamos la población obtenida por menor coste
        ordenarPoblacion(poblacionHijos);

        //5. Para mantener el elitismo, si no se encuentra el mejor padre de la población
        //anterior, tenemos que añadirlo nosotros intercambiandolo por el peor de la población de
        //los hijos

        bool mejor_encontrado = false;
        for(unsigned int i = 0; i < poblacionHijos.size() && !mejor_encontrado ; i++){
            if( poblacion[0].permutacion == poblacionHijos[i].permutacion){
                mejor_encontrado=true;
            }
        }

        //Si la mejor solución de la población de partida no está incluida en la población de los hijos
        //la sustituimos por la peor encontrada en los hijos.
        if(!mejor_encontrado){
            poblacionHijos[poblacionHijos.size()-1] = poblacion[0];
        }

         poblacion = poblacionHijos;
    }

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;


    if ( poblacion[0].coste < poblacion[poblacion.size()-1].coste)
        return poblacion[0];

    return poblacion[poblacion.size()-1];
}

//-----------------------------------------------------------------------------------------------------
//Algoritmo genético estacionario utilizando el operador de cruce OX
Solucion AlgoritmoGenetico::AlgoritmoEstacionario_OX()
{
    Solucion hijoObtenido;
    llamadasFuncionObjetivo = 0;
    int generaciones_realizadas = 0;
    int genes = 2*datos.nInstalaciones; //2 por numero de genes
    int cada_cuanto = 1000/genes; //cada cuantas generaciones tienes que mutar los dos hijos

    clock_t start,end;
    start = clock();

    while(llamadasFuncionObjetivo<50000){
        generaciones_realizadas++;
        int padre1, padre2;

        ordenarPoblacion(poblacion);
        vector<Solucion> poblacionHijos;


        //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
        padre1 = seleccionTorneoBinario();
        padre2 = seleccionTorneoBinario();

        //2. Realizo el cruce y obtengo dos hijos
        hijoObtenido = OperadorCruceOX(poblacion[padre1],poblacion[padre2]);
        poblacionHijos.push_back(hijoObtenido);
        llamadasFuncionObjetivo++;

        hijoObtenido = OperadorCruceOX(poblacion[padre2],poblacion[padre1]);
        poblacionHijos.push_back(hijoObtenido);
        llamadasFuncionObjetivo++;

        int hijoMutar, genMutar1, genMutar2;
        //3. Mutación
        if(generaciones_realizadas == cada_cuanto){

            generaciones_realizadas = 0;

            hijoMutar = hijoObtenido.ValorAleatorio(0,1);
            genMutar1 = hijoObtenido.ValorAleatorio(0, datos.nInstalaciones-1);
            genMutar2 = hijoObtenido.ValorAleatorio(0, datos.nInstalaciones-1);

            //me aseguro que los genes a cambiar son distintos
            //NO deben coincidir
            while(genMutar1 == genMutar2){
                genMutar2 = hijoObtenido.ValorAleatorio(0, datos.nInstalaciones-1);
            }

            poblacionHijos[hijoMutar].OperadorIntercambio(genMutar1,genMutar2);
            poblacionHijos[hijoMutar].calcularCoste(datos);
            llamadasFuncionObjetivo++;

        }

        //4. Sustituir por los padres
        //para facilitar los cálculos, añado los dos peores de la población a poblacionHijos, para ponerlos
        //a competir con los hijos recién generados
        poblacionHijos.push_back(poblacion[poblacion.size()-1]);
        poblacionHijos.push_back(poblacion[poblacion.size()-2]);

        ordenarPoblacion(poblacionHijos);
        poblacion[poblacion.size()-1] = poblacionHijos[0];    //el mejor de la poblacionHijos guardado en ultima pos
        poblacion[poblacion.size()-2] = poblacionHijos[1];

        //Para la mutación necesito contar el número de iteraciones realizadas


    }//end while

    end = clock();
    tiempo = (end-start)/(double)CLOCKS_PER_SEC;


    if ( poblacion[0].coste < poblacion[poblacion.size()-1].coste)
        return poblacion[0];

    return poblacion[poblacion.size()-1];
}

//------------------------------------------------------------------------------------------
//Operador de cruce de posición
Solucion AlgoritmoGenetico::OperadorCrucePosicion(Solucion padre1, Solucion padre2)
{

    //Creamos un hijo a partir de dos padres
    Solucion hijo;
    hijo.permutacion.resize(padre1.permutacion.size(),padre1.permutacion.size());


    int random_num;
    vector<int>::iterator it = hijo.permutacion.begin();

    for(unsigned int i=0; i<hijo.permutacion.size() ; i++){

        //Las posiciones de los padres que coincidan las colocamos en la misma pos del hijo.
        //Estas posiciones conservadas son las prometedoras
        if(padre1.permutacion[i]==padre2.permutacion[i]){
            hijo.permutacion[i]=padre1.permutacion[i];
        }

    }

    //generamos de manera aleatoria números hasta completar la solución
    for(int i=0; i<hijo.permutacion.size() ; i++){
        if(hijo.permutacion[i]==padre1.permutacion.size()){
            random_num = hijo.ValorAleatorio(0,hijo.permutacion.size()-1);
            it=find(hijo.permutacion.begin(), hijo.permutacion.end(), random_num);

            while(it!=hijo.permutacion.end()){
                random_num = hijo.ValorAleatorio(0,hijo.permutacion.size()-1);
                it=find(hijo.permutacion.begin(), hijo.permutacion.end(), random_num);
            }
            hijo.permutacion[i]=random_num;

        }

    }

    hijo.calcularCoste(datos);

    return hijo;

}

//---------------------------------------------------------------------------------------------------------
//Operador de cruce de OX
Solucion AlgoritmoGenetico::OperadorCruceOX(Solucion padre1, Solucion padre2)
{

    //Creamos un hijo a partir de dos padres
    Solucion hijo;
    //Lo inicializamos a un valor que sabemos que nunca va a tener (por ej: su tamaño)
    hijo.permutacion.resize(padre1.permutacion.size(),padre1.permutacion.size());

    //CADENA CENTRAL DE 4 VALORES
    int primero_copiar = (padre1.permutacion.size())/2 - (padre1.permutacion.size())/12;
    int fin_copiar = primero_copiar + (2*padre1.permutacion.size())/12;

    //Copiamos en el hijo la cadena central elegida del padre1
    for(int i=primero_copiar; i<fin_copiar ; i++){
        hijo.permutacion[i] = padre1.permutacion[i];
    }

    //ahora completamos las posiciones que quedan a la derecha con las del padre2
    int pos_copiadas_padre2=0;

    for(unsigned int i=0; i+fin_copiar<hijo.permutacion.size(); i++){
        while( find(hijo.permutacion.begin(),hijo.permutacion.end(),padre2.permutacion[pos_copiadas_padre2])
                !=hijo.permutacion.end()){
            pos_copiadas_padre2++;
        }
        hijo.permutacion[i+fin_copiar] = padre2.permutacion[pos_copiadas_padre2];
    }


    //completamos las posiciones a la izquierda con las que quedan del padre2
    for(int i=0; i<primero_copiar; i++){
        while( find(hijo.permutacion.begin(),hijo.permutacion.end(),padre2.permutacion[pos_copiadas_padre2])
                !=hijo.permutacion.end()){
            pos_copiadas_padre2++;
        }
        hijo.permutacion[i] = padre2.permutacion[pos_copiadas_padre2];

    }
    //Una vez llegado este paso, pos_copiadas_padre tiene que ser igual que
    //padre2.permutacion.size() - fin_copiar+primero_copiar


    hijo.calcularCoste(datos);
    return hijo;
}



//-------------------------------------------------------------------------------------------------------
void AlgoritmoGenetico::Mutacion(vector<Solucion> &poblacionMutar){

    //Utilizamos el operador de intercambio para representación del orden
    //Para ello necesitamos dos valores aleatorios (distintos) para intercambiar
    int hijoMutar, genMutar1,genMutar2;


    //El numero de genes a mutar va a ser tam_poblacion*tam_solucion*probM

    for(int i=0; i<nEsperadoGenesMutados; i++){
        llamadasFuncionObjetivo++;
        //3.1 Elegimos aleatoriamente los valores a mutar:
        genMutar1 = poblacion[0].ValorAleatorio(0, datos.nInstalaciones-1);
        genMutar2 = poblacion[0].ValorAleatorio(0, datos.nInstalaciones-1);

        //me aseguro que los genes a cambiar son distintos
        //NO deben coincidir
        while(genMutar1 == genMutar2){
            genMutar2 = poblacion[0].ValorAleatorio(0, datos.nInstalaciones-1);
        }

        //Elijo aleatoriamente el hijo que va a mutar
        hijoMutar = poblacion[0].ValorAleatorio(0, poblacion.size()-1);

        //Intercambio los valores para realizar propiamente la mutación
        poblacionMutar[hijoMutar].OperadorIntercambio(genMutar1,genMutar2);
        poblacionMutar[hijoMutar].calcularCoste(datos);

    }

}

//------------------------------------------------------------------------------------------------------
void AlgoritmoGenetico::ordenarPoblacion(vector<Solucion> &pobl){

    int j;
    Solucion valor;

    for (unsigned int i = 1; i < pobl.size(); i++){
         valor = pobl[i];
         j = i - 1;
         while (j >= 0 && pobl[j].coste > valor.coste){
              pobl[j + 1] = pobl[j];
              j--;
         }

         pobl[j + 1] = valor;
    }


}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Solucion AlgoritmoGenetico::AlgoritmoMemetico(){
//     //para realizar la BL
//     int contar_generaciones = 0;
//     int it = 0;
//     //condición de parada
//     llamadasFuncionObjetivo = poblacion.size();
//
//     //para la mutación:
//     int generaciones_realizadas = 0 ;
//     int genes = poblacion.size()*datos.n; //tampoblacion por numero de genes
//     int cada_cuanto = 1000/genes; //cada cuantas generaciones tienes que mutar los dos hijos
//
//     clock_t start,end;
//     start = clock();
//
//     while( llamadasFuncionObjetivo < 50000){
//
//         it++;
//         contar_generaciones++;
//         generaciones_realizadas++;
//         vector<Solucion> poblacionPadres, poblacionHijos;
//
//         ordenarPoblacion(poblacion);
//
//
//         //1. Obtengo población de los padres mediante un proceso de selección de la población de partida
//         int sol_seleccionada;
//         for(int i=0; i<poblacion.size(); i++){
//             sol_seleccionada = seleccionTorneoBinario();
//             poblacionPadres.push_back(poblacion[sol_seleccionada]);
//
//         }
//
//         //2. Cruzo la población recién seleccionada
//         int sol_cruzada=0; //la inicializo a 0 porque voy a realizar cruces de dos en dos
//
//         Solucion hijoObtenido1, hijoObtenido2;
//         for(int i=0; i<nEsperadoCruces ; i++){
//
//             hijoObtenido1 = OperadorCrucePosicion(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
//             poblacionHijos.push_back(hijoObtenido1);
//             llamadasFuncionObjetivo++;
//
//             hijoObtenido2 = OperadorCrucePosicion(poblacionPadres[sol_cruzada],poblacionPadres[sol_cruzada+1]);
//             poblacionHijos.push_back(hijoObtenido2);
//             llamadasFuncionObjetivo++;
//
//             sol_cruzada+=2;
//
//         }
//
//         //3. Añadimos los padres que no se han cruzado a la población de los hijos
//         for(unsigned int i=sol_cruzada; i< poblacionPadres.size();i++){
//            poblacionHijos.push_back(poblacionPadres[i]);
//         }
//
//         //4. Muto la población de los hijos
//         //Vamos a mutar nEsperadoGenesMutados
//         if(cada_cuanto == generaciones_realizadas){
//             nEsperadoGenesMutados = 1;
//             Mutacion(poblacionHijos);
//             generaciones_realizadas = 0;
//         }
//         if(contar_generaciones == 10){
//
//             contar_generaciones = 0;
//
//             if (probabilidadPLS == 1.0){
//
//                 for(unsigned int i = 0; i<poblacionHijos.size(); i++){
//                     BusquedaLocal bl(datos,poblacionHijos[i]);
//                     poblacionHijos[i] = bl.solucion_bl;
//
//                     llamadasFuncionObjetivo+=bl.soluciones_exploradas;
//                 }
//             }else if(probabilidadPLS == 2.0){
//
//                 vector<Solucion>poblacionBL;
//                 for(unsigned int i = 0; i<poblacionHijos.size()*0.1; i++){
//                     int hijoEscogido = poblacionHijos[0].ValorAleatorio(0,poblacionHijos.size()-1);
//                     poblacionBL.push_back(poblacionHijos[hijoEscogido]);
//                 }
//                 for(unsigned int i = 0; i<poblacionBL.size(); i++){
//                     BusquedaLocal bl(datos,poblacionHijos[i]);
//                     poblacionHijos[i] = bl.solucion_bl;
//                     llamadasFuncionObjetivo+=bl.soluciones_exploradas;
//                 }
//             }else if(probabilidadPLS == 3.0){
//
//                 //Ordenamos la población obtenida por menor coste
//                 ordenarPoblacion(poblacionHijos);
//                 for(unsigned int i = 0; i<poblacionHijos.size()*0.1; i++){
//                     BusquedaLocal bl(datos,poblacionHijos[i]);
//                     poblacionHijos[i] = bl.solucion_bl;
//                     llamadasFuncionObjetivo+=bl.soluciones_exploradas;
//                 }
//             }
//         }
//
//         //Ordenamos la población obtenida por menor coste
//         ordenarPoblacion(poblacionHijos);
//         //5. Para mantener el elitismo, si no se encuentra el mejor padre de la población
//         //anterior, tenemos que añadirlo nosotros intercambiandolo por el peor de la población de
//         //los hijos
//
//         bool mejor_encontrado = false;
//         for(unsigned int i = 0; i < poblacionHijos.size() && !mejor_encontrado ; i++){
//             if( poblacion[0].permutacion == poblacionHijos[i].permutacion){
//                 mejor_encontrado=true;
//             }
//         }
//
//         //Si la mejor solución de la población de partida no está incluida en la población de los hijos
//         //la sustituimos por la peor encontrada en los hijos.
//         if(!mejor_encontrado){
//             poblacionHijos[poblacionHijos.size()-1] = poblacion[0];
//         }
//
//          poblacion = poblacionHijos;
//     }
//
//     end = clock();
//     tiempo = (end-start)/(double)CLOCKS_PER_SEC;
//
//     if ( poblacion[0].coste < poblacion[poblacion.size()-1].coste)
//         return poblacion[0];
//
//     return poblacion[poblacion.size()-1];
// }
