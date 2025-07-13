#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;


template<typename tCoste>
struct jerte{
    GrafoP<tCoste> canales;
    tCoste c;
    jerte(GrafoP<tCoste> p, tCoste x): canales(p), c(x){}
};

template<typename tCoste>
jerte<tCoste> emasejer 
(const GrafoP<tCoste>& G, const GrafoP<tCoste>& C,
tCoste subvencion, tCoste costeKM
)
{
    typedef typename Grafo::vertice vertice;
    const size_t n = G.numVert();

    GrafoP<tCoste> K(n);
    for(size_t i = 0; i<n;i++){
        for(size_t j = 0; j<n;j++){
            if (G[i][j] != GrafoP<tCoste>::INFINITO && C[i][j] != GrafoP<tCoste>::INFINITO)
            K[i][j] = suma((G[i][j] * costeKM),-(C[i][j] * subvencion));
        }
    }

    K = Kruskall(K);

    cout<<K;

    tCoste minimo = 0;
    for(size_t i = 0; i<n;i++){
        for(size_t j = i; j<n;j++){
            if(K[i][j]!=GrafoP<tCoste>::INFINITO)
                minimo += K[i][j];
                
        }
    }
    jerte<tCoste> j;
    j.c = minimo;
    j.canales = K;
    return j;
}


int main(){
    GrafoP<double> T(10);
    GrafoP<double> A(10);

    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    // Definir la distribución (por ejemplo, distribución uniforme entre 1 y 100)
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = i; j<10;j++){
            if(i==j){
                T[i][j] = 0;
                A[i][j] = 0;
            }
            else{
                T[i][j] = T[j][i] = dis(gen);
                A[i][j] = A[j][i] = dis(gen);
            }
                
        }
    }
    cout<<"TREN---------------"<<endl;
    cout<<T;
    jerte<double> j = emasejer(T,A,0.4,10.0);
    cout<<j.canales;
    return 0;
};