#include<iostream>
#include <random>
#include<vector>
#include "alg_grafoPMC.h"

using namespace std;

template<typename tCoste>
struct tCarretera{
    typename GrafoP<tCoste>::vertice v1,v2;
};

template <typename tCoste>
GrafoP<tCoste> Zuelandia(GrafoP<tCoste>& G, vector<typename GrafoP<tCoste>::vertice> ciudades,
vector<tCarretera<tCoste>> cc, typename GrafoP<tCoste>::vertice capital)
{
    const size_t n = G.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;
    for(size_t i = 0; i < ciudades.size(); i++)
        for (size_t j = 0; j < n; j++)
            G[ciudades[i]][j] = G[j][ciudades[i]] = GrafoP<tCoste>::INFINITO;
    
    for(size_t k = 0; k < cc.size(); k++)
        G[cc[k].v1][cc[k].v2] = GrafoP<tCoste>::INFINITO;
    
    vector<tCoste> costes(n),costesInv(n);
    vector<vertice> ver(n),verInv(n);
    
    costes = Dijkstra(G,capital,ver);
    costesInv = DijkstraInv(G,capital,verInv);

    // Probar con Floyf
    //matriz<tCoste> m = Floyd(G,matriz<vertice>(n));
    /*
    Pero seria un cero debido a que FLoyd es n^3 mientras
    hacer dos veces Dijkstra es 2*(n^2)
    */

    GrafoP<tCoste> res(n);
    for(size_t a = 0; a < n; a++)
        for (size_t b = 0; b < n; b++){
            if(a!=b)
                res[a][b] = suma(costesInv[a],costes[b]);
            else
                res[a][b] = 0;
                // Debido a que el camino de un nodo a sí mismo es cero 
                // y no se tendría que pasar por la capital
        }

            

    return res;

}

int main(){
    GrafoP<size_t> G(10);
    const size_t n = G.numVert();
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
    cout<<"El grafo de Zuelandia previo se ve así: "<<endl;
    cout<<G;
    typename GrafoP<size_t>::vertice capital = 5;
    vector<typename GrafoP<size_t>::vertice> v;
    v.push_back(capital+1);
    vector<tCarretera<size_t>> v2(1);
    tCarretera<size_t> c;
    c.v1 = 3;
    c.v2 = 1;
    v2.push_back(c);
    cout<<"La capital es "<<capital<<endl;
    G = Zuelandia<size_t>(G,v,v2,capital);
    cout<<G;
    return 0;
}