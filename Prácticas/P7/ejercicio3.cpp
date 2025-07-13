#include<iostream>
#include <random>
#include "alg_grafoPMC.h"

using namespace std;

typedef typename GrafoP<tCoste>::vertice vertice;

template<typename tCoste>
struct tCamino{
    tCoste coste;
    Lista<vertice> ruta;
    
};


/*
Replantear ejercicio con Dijkstra, ya que el coste desde el almacen es cero
por lo que podemos ir repartiendo a  los mascercanos desde entonces y volver
devolver un vector de tamaño num vertices donde indicamos la cantidad de producto
que dejamos ahi
*/
template<typename tCoste>
tCamino<tCoste> repartidor(vertice almacen, tCoste cantidad, 
const GrafoP<tCoste>& G, vector<tCoste> capacidades,
vector<double> subvencion)
{
    const size_t n = G.numVert();
    GrafoP<tCoste> D = G;

    for(size_t i = 0; i < N; i++)
        for(size_t j = 0; j < N; j++)
            D[i][j] *= (1 - subvencion[j])/100;
    matriz<vertice> verts(n);
    matriz<tCoste> costes = Floyd(G,verts);

    // Creamos un vector para marcar los visitados
    vector<bool> visitados(n,false);
    visitados[almacen] = true;

    tCamino trazado;
    vertice actual = almacen, siguiente;
    tCoste contador = cantidad;
    bool TodosVisitados = false;
    while (contador > 0 && !TodosVisitados){
        //primero buscamos mas cernano no visitado
        tCoste next = GrafoP<tCoste>::INFINITO;
        for(vertice i = 0; i < N; i++)
            if(next > D[actual][i] && !visitados[i]){
                next = D[actual][i];
                siguiente = i;
            }
        if(capacidades[i] > contador){
            contador = 0;
            trazado.coste += contador;
        }
        else{
            contador -= capacidades[i];
            trazado.coste += capacidades[i];
        }
        trazado.ruta.insertar(i,trazado.ruta.fin());
        visitados[i] = true;
        actual = i;
        TodosVisitados = all_of(visitados.begin(),visitados.end(), [](bool v){
            return v;
        });
    }
    
    return trazado;
}
/* Version github
template <typename tCoste>
void distribucionStock (const GrafoP<tCoste>& G, vector<unsigned> capacidad, vector<double> subvencion, typename GrafoP<tCoste>::vertice centro, unsigned cantidad)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    const size_t n = G.numVert();

    GrafoP<tCoste> SA = G;  // SA == Subvenciones aplicadas

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if (SA[i][j] != INFINITO)
                SA[i][j] *= (1 - subvencion[j]/100);
    
    vector<tCoste> dSA(n);  // dSA == disjktra de SA
    vector<vertice> P(n);    
    dSA = Dijkstra(SA, centro, P);

    vector<unsigned> udsXciudad(n);
    double costeMinTotal = 0;

    while (cantidad > 0)
    {
        unsigned costeMin = INFINITO;
        vertice ciudadMin;
        for(vertice i = 0 ; i < n ; i++)
        {
            if (i != centro && dSA[i] < costeMin)
            {
                costeMin = dSA[i];
                ciudadMin = i;
            }
        }

        unsigned cant;
        if (capacidad[ciudadMin] < cantidad)
        {
            cant = capacidad[ciudadMin];
            dSA[ciudadMin] = INFINITO;
        }
        else
            cant = cantidad;

        cantidad -= cant;
        costeMinTotal += costeMin * cant;
        udsXciudad[ciudadMin] = cant;
    }

    cout << "Distribucion: " << endl;
    cout << " - Uds x Ciudad: ";
    for (size_t i = 0 ; i < n ; i++)
        cout << udsXciudad[i] << " ";
    cout << endl << " - Coste minimo total: " << costeMinTotal << endl << endl;

}

*/

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
}