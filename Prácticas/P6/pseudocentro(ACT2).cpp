#include<iostream>
#include <random>
#include "alg_grafoPMC.h"

using namespace std;

/*
Esto  esta mal hay buscar los dos nodos as alejados
y luego mirar el coste de ir de uno a otro pasadno por el resto
de nodos y el que minimice ese es el pseudocentro
hacemos n veces dijkstra o floyd y miro dila a fila
y almaceno el maximo y origen y destino y cada vez que se 
supere el maximo actualizo los tres atributos
*/


template<typename tCoste>
struct res{
    typename GrafoP<tCoste>::vertice p;
    int v;
};

template<typename tCoste>
tCoste pseudocentro(const GrafoP<tCoste> G){
    const size_t n = G.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

    vertice origen,destino;
    tCoste maximo = 0;
    tCoste maximo2 = 0;
    tCoste maxx = GrafoP<tCoste>::INFINITO;

    matriz<vertice> verts(n);
    matriz<tCoste> M = Floyd(G,verts);

    cout<<"------------------------------"<<endl;
    for(size_t i = 0; i<n;i++){
        for(size_t j = 0; j<n;j++){
            cout<<M[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"------------------------------"<<endl;

    for(size_t i = 0; i<n;i++){
        for(size_t j = 0; j<n;j++){
            if(G[i][j]!=GrafoP<tCoste>::INFINITO){
                if(G[i][j]>maximo){
                    maximo2 = maximo;
                    maximo = G[i][j];
            }
            else {
                if(GrafoP<tCoste>::INFINITO>G[i][j]>maximo2)
                    maximo2 = G[i][j];    
                }
            }
        }
        maxx = min(maxx,suma(maximo,maximo2));
    }
    return maxx;
}

int main(){
    GrafoP<int> G(4);
    cout<<G;
    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    // Definir la distribución (por ejemplo, distribución uniforme entre 1 y 100)
    uniform_int_distribution<> dis(1, 11);

    for(size_t i = 0; i<4;i++){
        for(size_t j = 0; j<4;j++){
            if(i==j)
                G[i][j] = 0;
            else
                G[i][j]=dis(gen);
        }
    }
    cout<<G;
    matriz<typename GrafoP<int>::vertice> P = matriz<size_t>(10);
    matriz<int> A = Floyd(G,P);
    cout<<endl<<"Aplicando Floyd..."<<endl;
    for(size_t i = 0; i<4;i++){
        for(size_t j = 0; j<4;j++)
            G[i][j] = A[i][j];
    }
    cout<<G;
    cout<<endl<<"Ahora calculamos su pseudocentro..."<<endl;
    cout<<"El diametro es "<< pseudocentro(G)<<endl;
    return 0;
}