#include<iostream>
#include <random>
#include <tuple>
#include "alg_grafoPMC.h"

using namespace std;

template <typename tCoste>
struct tViaje {
    typename GrafoP<tCoste>::vertice origen, destino;
    tCoste coste;
    tViaje(typename GrafoP<tCoste>::vertice o, typename GrafoP<tCoste>::vertice d, tCoste c): origen(o), destino(d), coste(c) {}
};

/*
Happy path porque nos dice que el grafo es aciclico
Intentar siendo ciclico
*/

template <typename tCoste>
matriz<tCoste> FloydM(const GrafoP<tCoste>& G,
                     matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos

   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];                    // copia costes del grafo
      A[i][i] = 0;                    // diagonal a 0
      P[i] = vector<vertice>(n, i);   // caminos directos
   }
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++) {
            if(A[i][k]!= GrafoP<tCoste>::INFINITO && A[k][j]!= GrafoP<tCoste>::INFINITO){
                tCoste ikj = suma(A[i][k], A[k][j]);
                if (ikj > A[i][j] && A[i][k]!= GrafoP<tCoste>::INFINITO && ikj!= GrafoP<tCoste>::INFINITO) {
                    A[i][j] = ikj;
                    P[i][j] = k;
            }
            }
            
         }
   return A;
}


template <typename tCoste>
tViaje<tCoste> otravezungrafo(const GrafoP<tCoste>& G){
    const size_t n = G.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;

    matriz<vertice> v(n);
    matriz<tCoste> costes = FloydM(G,v);
    tCoste masCaro = 0;
    vertice origen = 0, destino = 0;

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            if(costes[i][j]!=GrafoP<tCoste>::INFINITO && costes[i][j]>masCaro){
                masCaro = costes[i][j];
                origen = i;
                destino = j;
            }
        }
    }
    return tViaje<tCoste>(origen,destino,masCaro);
}

/*Segun Juanfran
template <typename tCoste>
auto viajeroCaro(const GrafoP<tCoste>& G){
    matriz<tCoste> mat;

    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    
    for (vertice i = 0; i < n; i++) {
      mat[i] = G[i];                    // copia costes del grafo
      mat[i][i] = 0;                    // diagonal a 0
   }
    vertice origen,destino;
    tCoste ikj = 0;
    for (vertice k = 0; k < n; k++)
        for (vertice i = 0; i < n; i++)
            for (vertice j = 0; j < n; j++) {
                    tCoste ikj = suma(mat[i][k], mat[k][j]);
                    if (ikj > mat[i][j] && mat[i][k]!= GrafoP<tCoste>::INFINITO && ikj!= GrafoP<tCoste>::INFINITO) {
                        mat[i][j] = ikj;
                        origen = i;
                        destino = j;
                    }

             }

    return make_tuple(origen,destino,maximo);
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
        for(size_t j = i+1; j<10;j++){
                G[i][j] = 0;
        }
    }


    for(size_t i = 0; i<10;i++){
        for(size_t j = i+1; j<10;j++){
            if(i==j)
                G[i][j] = 0;
            else
                G[i][j] = dis(gen);
        }
    }


    cout<<G;

    cout << endl << endl << "Caminos maximos: " << endl << endl; 

    matriz<typename GrafoP<int>::vertice> v(G.numVert());
    matriz<int> m = FloydM(G,v);
    cout << endl << endl; 
    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl; 

    cout << otravezungrafo(G).origen << " " << otravezungrafo(G).destino << " " << otravezungrafo(G).coste << endl;

    /*
    Juanfran
    

   GrafoP<unsigned int> grafo("grafo.txt");
   // para c++ 17
   auto [a, b, c] = viajeroCaro(grafo);

    */

    return 0;
}