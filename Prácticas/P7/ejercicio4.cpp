#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include<vector>

using namespace std;





template<typename tCoste>
tCoste Cementos(vertice capital,
const GrafoP<tCoste>& G, 
vector<typename GrafoP<tCoste>::vertice> parte)
{
    const size_t n = G.numVert();
    vector<typename GrafoP<tCoste>::vertice> verts(n);
    vector<tCoste> costesD = Dijkstra(G,capital,verts);
    vector<typename GrafoP<tCoste>::vertice> vertsI(n);
    vector<tCoste> costesI = DijkstraInv(G,capital,vertsI);

    tCoste km = 0;
    for(size_t i = 0; i < parte.size(); i++)
        km += costesD[parte[i]] + costesI[parte[i]];
        
    return km;
}


int main(){
    GrafoP<int> G(10);

    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    // Definir la distribución (por ejemplo, distribución uniforme entre 1 y 100)
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
            if(i==j)
                G[i][j] = 0;
            else
                G[i][j]=dis(gen);
        }
    }

    return 0;
};