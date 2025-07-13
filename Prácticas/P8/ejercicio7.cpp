#include<iostream>
#include <random>
#include <limits>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

struct tCiudad{
    size_t x,y;
};

struct tPuente{
    size_t a,b;
    double distancia;
};



struct CCostera{
    tCiudad v;
};


double distancias(tCiudad a, tCiudad b){
    return sqrt(pow(abs(a.x-b.x),2)+pow(abs(a.y-b.y),2));
}

tPuente mejorPuente(vector<tCiudad> fc, vector<tCiudad> dc){
    double x = numeric_limits<double>::max();
    tPuente p;
    for(size_t i = 0; i < fc.size(); i++){
        for(size_t j = 0; j< dc.size(); j++){
            double d = distancias(fc[i],dc[j]);
            if (d < x){
                p.a = i;
                p.b = j;
                p.distancia = d;
                x = d;
            }
        }
    }
    return p;
}


template<typename tCoste>
tCoste grecoland 
(vector<tCiudad>Fobos, vector<tCiudad> Deimos,
vector<tCiudad> FobosC, vector<tCiudad> DeimosC,
tCiudad origen, tCiudad destino
)
{
    typedef typename Grafo::vertice vertice;
    const size_t n1 = Fobos.size();
    const size_t n2 = Deimos.size();

    GrafoP<tCoste> F(n1),D(n2);

    // Arreglamos Fobos
    for(size_t i = 0; i<n1;i++){
        for(size_t j = i; j<n1;j++){
           F[i][j] = F[j][i] = distancias(Fobos[i],Fobos[j]);
        }
    }

    F = Kruskall(F);

    // Arreglamos Deimos
    for(size_t i = 0; i<n2; i++){
        for(size_t j = i; j<n2; j++){
           D[i][j] = D[j][i] = distancias(Deimos[i],Deimos[j]);
        }
    }

    D = Kruskall(D);

    // El mejor coste esta mal dicho, el mas corto
    tPuente mp = mejorPuente(FobosC,DeimosC);

    GrafoP<tCoste> G(n1+n2);

    for(size_t i = 0; i<n1; i++){
        for(size_t j = 0; j<n1; j++){
           G[i][j] = F[i][j];
        }
    }

    for(size_t i = n1; i<n1+n2; i++){
        for(size_t j = n1; j<n1+n2; j++){
           G[i][j] = D[i-n1][j-n1];
        }
    }

    // Ponemos el puente
    G[mp.a][mp.b + n1] = mp.distancia;
    G[mp.b + n1][mp.a] = mp.distancia;

    cout<<G;

    vector<vertice> verts(n1+n2);
    vector<tCoste> costes = Dijkstra(G,origen,verts);
    return costes[destino];
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
 
    return 0;
};