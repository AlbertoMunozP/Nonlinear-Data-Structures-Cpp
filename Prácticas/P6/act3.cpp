#include<iostream>
#include <random>
#include "alg_grafoPMC.h"

using namespace std;

/* Segun Juanfran
Hacer un recorrido en profundidad, en anchura:
no tendria sentido porque como vimos en IA en 
profundidad es la forma mas posible de encontrar grafos
tambien vale la version de abajo de de la huerta
HACER TAMBIEN LA VERSION DE RECORRIDO EN PROFUNDIDAD
*/

template <typename tCoste>
matriz<tCoste> FloydMod(const GrafoP<tCoste>& G,
                     matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   // matriz de costes mínimos

   // Iniciar A y P con caminos directos entre cada par de vértices.
   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];                    // copia costes del grafo
      A[i][i] = GrafoP<tCoste>::INFINITO; 
      P[i] = vector<vertice>(n, i);   // caminos directos
   }
   // Calcular costes mínimos y caminos correspondientes
   // entre cualquier par de vértices i, j
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++) {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if (ikj > A[i][j] && ikj!=GrafoP<tCoste>::INFINITO && A[i][j]!=GrafoP<tCoste>::INFINITO) {
               A[i][j] = ikj;
               P[i][j] = k;
            }
         }
   return A;
   // Si en la diagonal devuelve algun valor diferente de infinito
   // es porque el grado asociaado es cíclico, es decir ha encontrado 
   // un camino de un nodo a sí mismo
}

template <typename tCoste>
bool aciclico(matriz<tCoste> M){
    bool nociclo = true;
    for(size_t i = 0; i < M.dimension() && nociclo; i++){
        if(M[i][i]!=GrafoP<tCoste>::INFINITO)
            nociclo = false;
    }
    return nociclo;
}

int main(){
    GrafoP<int> G(10);
    cout<<G;
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
    cout<<G;
    matriz<typename GrafoP<int>::vertice> P = matriz<size_t>(10);
    matriz<int> A = FloydMod(G,P);
    cout<<endl<<"Aplicando Floyd modificado..."<<endl;
    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++)
            G[i][j] = A[i][j];
    }
    cout<<G;
    cout<<endl<<"Comprobamos si podemos pedir la subvencion..."<<endl;
    if(aciclico(A))
        cout<<"Sí se puede pedir, el grafo asociado es aciclico!";
    else
        cout<<"No se puede pedir, el grafo asociado es ciclico!";            
    return 0;
}