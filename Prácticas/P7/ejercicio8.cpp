#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
tCoste calculaMin(vector<tCoste> v, vector<tCoste> vv,
typename GrafoP<tCoste>::vertice o,
typename GrafoP<tCoste>::vertice d){
    tCoste m= GrafoP<tCoste>::INFINITO;
    for(size_t i = 0; i < v.size(); i++)
        if(i != o && i!= d)
            m = min(m,v[i]+vv[i]);
    return m;
}

template<typename tCoste>
tCoste min4(tCoste a, tCoste b, tCoste c, tCoste d){
    return min(min(a,b),min(c,d));
}


// Probar a devolver con std::tuple en vez de structs

template<typename tCoste>
matriz<tCoste> soloUnTransbordo
(const GrafoP<tCoste>& T, const GrafoP<tCoste>& B,
typename GrafoP<tCoste>::vertice origen,
typename GrafoP<tCoste>::vertice destino
)
{
    const size_t n = T.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

   
    vector<vertice> idaTV(n), idaBV(n), vueltaBV(n), vueltaTV(n); 
    vector<tCoste> idaT(n), idaB(n), vueltaT(n), vueltaB(n); 
    
    idaT = Dijkstra(T,origen,idaTV);
    idaB = Dijkstra(B,origen,idaBV);
    vueltaT = DijkstraInv(T,destino,vueltaTV);
    vueltaB = DijkstraInv(B,destino,vueltaBV);

    tCoste minimoB = calculaMin(idaB,vueltaT,origen,destino);
    tCoste minimoT = calculaMin(idaT,vueltaB,origen,destino);

    return min4(idaT[destino],idaB[destino],minimoB,minimoT);
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