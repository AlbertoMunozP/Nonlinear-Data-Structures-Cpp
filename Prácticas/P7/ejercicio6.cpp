#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
tCoste min4(tCoste a, tCoste b, tCoste c, tCoste d){
    return min(min(a,b),min(c,d));
}

template<typename tCoste>
matriz<tCoste> agencia
(const GrafoP<tCoste>& T, const GrafoP<tCoste>& B,
typename GrafoP<tCoste>::vertice transbordo)
{
    const size_t n = T.numVert();
    GrafoP<tCoste> V(n);
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<vertice> busV(n),trenV(n);
    matriz<tCoste> busC(n), trenC(n); 

    // Solo bus
    busC = Floyd(B,busV);
    // Solo tren
    trenC = Floyd(T,trenV);

    for(size_t i = 0; i<n; i++){
        for(size_t j = 0; j<n ;j++){
            V[i][j] = min4(busC[i][j],trenC[i][j],busC[i][transbordo]+trenC[transbordo][j],trenC[i][transbordo]+busC[transbordo][j]);
        }
    }
    
    return V;
}


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
        for(size_t j = 0; j<10;j++){
            if(i==j){
                T[i][j] = 0;
                A[i][j] = 0;
            }
            else{
                T[i][j] = dis(gen);
                A[i][j] = dis(gen)-1;
            }
                
        }
    }
    cout<<"TREN---------------"<<endl;
    cout<<T;
    cout<<"BUS--------------"<<endl;
    cout<<A;
    
    
    return 0;
};