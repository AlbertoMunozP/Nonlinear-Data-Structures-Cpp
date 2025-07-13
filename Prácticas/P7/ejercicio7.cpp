#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
struct ruta{
    tCoste coste;
    Lista<typename GrafoP<tCoste>::vertice> camino;
};


template<typename tCoste>
matriz<tCoste> dos_cambios
(const GrafoP<tCoste>& T, const GrafoP<tCoste>& B,
typename GrafoP<tCoste>::vertice cambio1,
typename GrafoP<tCoste>::vertice cambio2,
typename GrafoP<tCoste>::vertice origen,
typename GrafoP<tCoste>::vertice destino
)
// En un grafo no dirigido es lo mismo hacer dos veces
// Dijkstra que hacer una vez Dijkstra y otra el inverso
// Si no dicen nada es grafo no dirigido
{
    const size_t n = T.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

    // Represento ida como origen - cambioX
    // Represento vuelta como cambioX - destino
    
    vector<vertice> idaV(n), vueltaV(n); 
    vector<tCoste> ida(n), vuelta(n); 

    ida = Dijkstra(T,origen,idaV);
    vuelta = DijkstraInv(B,destino,vueltaV);

    ruta<tCoste> r;
    r.coste = min(ida[cambio1]+vuelta[cambio1],ida[cambio2]+vuelta[cambio2]);
    typename GrafoP<tCoste>::tCamino c;
    if(r.coste == ida[cambio1]+vuelta[cambio1])
        c = camino(origen,cambio1,idaV) + camino(cambio1,destino,vueltaV);
    else
        c = camino(origen,cambio2,idaV) + camino(cambio2,destino,vueltaV);
    
    // Supongo sobrecargado el operador + para listas,
    // cuyo comportamiento es concatenar dos listas.
    
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