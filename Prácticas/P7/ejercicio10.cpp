#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
tCoste min9(tCoste a, tCoste b, tCoste c, tCoste d,
tCoste e, tCoste f, tCoste g, tCoste h, tCoste i){
    tCoste x = min(min(a,b),min(c,d));
    tCoste y = min(min(e,f),min(g,h));
    return min(i, min(x,y));
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
const GrafoP<tCoste>& A,
typename GrafoP<tCoste>::vertice origen,
typename GrafoP<tCoste>::vertice destino,
tCoste taxi, tCoste taxi2
)
{
    const size_t n = T.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;
    GrafoP<tCoste> SG(n*3);
    for(size_t i = 0; i<n; i++){
        for(size_t j = 0; j<n; j++){
            SG[i][j] = T[i][j];
            SG[i+n][j+n] = B[i][j];
            SG[i+n+n][j+n+n] = A[i][j];
        }
    }
    for(size_t k = 0; k<n; k++){
        SG[k][k+n] = SG[k+n][k] = taxi;
        SG[k][k+n+n] = SG[k+n+n][k] = taxi2;
        SG[k+n][k+n+n] = SG[k+n+n][k+n] = taxi2;
    }
    ruta<tCoste> r;
    vector<vertice> trenV(n+n+n), busV(n+n+n), avionV(n+n+n);
    vector<tCoste> trenC = Dijkstra(SG,origen,trenV);
    vector<tCoste> busC = Dijkstra(SG,origen+n,busV);
    vector<tCoste> avionC = Dijkstra(SG,origen+n+n,avionV);
    

    r.coste = min9(trenC[destino], trenC[destino+n], trenC[destino+n+n],
                    busC[destino], busC[destino+n], busC[destino+n+n],
                    avionC[destino], avionC[destino+n], avionC[destino+n+n]);

    switch(r.coste){
        case trenC[destino]: r.path = camino(origen,destino,TrenV);
            break;
        case trenC[destino+n]: r.path = camino(origen,destino+n,TrenV);
            break;
        case trenC[destino+n+n]: r.path = camino(origen,destino+n+n,TrenV);
            break;
        case busC[destino]: r.path = camino(origen+n,destino,BusV);
            break;
        case busC[destino+n]: r.path = camino(origen+n,destino+n,BusV);
            break;
        case busC[destino+n+n]: r.path = camino(origen+n,destino+n+n,BusV);
            break;
        case avionC[destino]: r.path = camino(origen+n+n,destino,avionV);
            break;
        case avionC[destino+n]: r.path = camino(origen+n+n,destino+n,avionV);
            break;
        case avionC[destino+n+n]: r.path = camino(origen+n+n,destino+n+n,avionV);
            break;
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