#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

/* Mirar apo max */

template<typename tCoste>
tCoste min4(tCoste a, tCoste b, tCoste c, tCoste d){
    return min(min(a,b),min(c,d));
}

template<typename tCoste>
struct ruta
{
    tCoste coste;
    Lista<GrafoP<tCoste>::vertice> path;
};


template<typename tCoste>
ruta<tCoste> supergrafo
(const GrafoP<tCoste>& T, const GrafoP<tCoste>& B,
typename GrafoP<tCoste>::vertice origen,
typename GrafoP<tCoste>::vertice destino,
tCoste taxi
)
{
    const size_t n = T.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;
    GrafoP<tCoste> SG(n*2);
    for(size_t i = 0; i<n; i++){
        for(size_t j = 0; j<n; j++){
            SG[i][j] = T[i][j];
            SG[i+n][j+n] = B[i][j];  
        }
    }
    for(size_t k = 0; k<n; k++){
        SG[k][k+n] = SG[k+n][k] = taxi;
    }
    ruta<tCoste> r;
    vector<vertice> trenV(n+n), busV(n+n);
    vector<tCoste> trenC = Dijkstra(SG,origen,trenV);
    vector<tCoste> busC = Dijkstra(SG,origen+n,busV);

    r.coste = min4(trenC[destino],busC[destino],trenC[destino+n],busC[destino+n]);
    if(r.coste == trenC[destino])
        r.path = camino(origen,destino,trenV);
    else{
        if(r.coste == trenC[destino+n])
            r.path = camino(origen,destino+n,trenV);
        else{
            if(r.coste == busC[destino])
                r.path = camino(origen+n,destino,busV);
            else
                r.path = camino(origen+n,destino+n,busV);
        }
    }
    return r;

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