#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;


template<typename tCoste>
GrafoP<tCoste> emasajer 
(const GrafoP<tCoste>& G)
{
    typedef typename Grafo::vertice vertice;
    const size_t n = G.numVert();

    GrafoP<tCoste> K(n);

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            K[i][j] = (-1)*G[i][j];
    
    K = Kruskall(K);
    // Si le pasamos un grafo a Kruskall con todos sus
    // pesos negativos devolvera el arbol de expansión
    // máximo, por lo que la solución será una matriz
    // de pesos que indica los canales que deben existir,
    // su origen, su destino y sus kms.
    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            K[i][j] = (-1)*G[i][j];
    return K;
}

/*
    Usamos el Kruskall del ejercicio anterior
*/

int main(){
    GrafoP<int> T(10);
    GrafoP<int> A(10);

    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    // Definir la distribución (por ejemplo, distribución uniforme entre 1 y 100)
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = i; j<10;j++){
            if(i==j){
                T[i][j] = 0;
                A[i][j] = 0;
            }
            else{
                T[i][j] = T[j][i] = -dis(gen);
                A[i][j] = dis(gen)-1;
            }
                
        }
    }
    cout<<"TREN---------------"<<endl;
    cout<<T;
    cout<<"APLICANDO KRUSKALL"<<endl;
    T = Kruskall(T);
    cout<<T;
    return 0;
};