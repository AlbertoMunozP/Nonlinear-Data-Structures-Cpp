#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

struct tCiudad
{
    size_t x,y;
};

struct tDistribucion{
    matriz<double> M;
    Particion p;
    tDistribucion(matriz<double> matriz, Particion particion) : M(matriz), p(particion) {}
};

long double distancia(tCiudad c1, tCiudad c2){
    return sqrt(pow(c1.x-c2.x,2)+pow(c1.y-c2.y,2));
}


tDistribucion Tombuctu 
(matriz<bool> G, vector<tCiudad> ciudades)
{
    typedef typename Grafo::vertice vertice;
    const size_t n = 10;

    Particion p(n);
    GrafoP<double> K(n);

    for (vertice i = 0 ; i < n ; i++)
        for (vertice j = 0 ; j < n ; j++)
            if(G[i][j]){
                K[i][j] = distancia(ciudades[i],ciudades[j]);
                if(p.encontrar(i)!=p.encontrar(j))
                    p.unir(p.encontrar(i),p.encontrar(j));
            }
    
    matriz<GrafoP<double>::vertice> v(n);
    matriz<double> m = Floyd(K,v);
    tDistribucion dis(m,p);
    return dis;
}


int main(){
    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    

    matriz<int> preB(10);
    uniform_int_distribution<> dis(0, 1);

    for(size_t i = 0; i < 10; i++){
        for(size_t j = 0; j < 10; j++){
            if(i == j){
                preB[i][j] = 0;
            }
            else{
                preB[i][j] = dis(gen);
            }
        }
    }

    matriz<bool> B(10);
    for(size_t i = 0; i < 10; i++){
        for(size_t j = 0; j < 10; j++){
            B[i][j] = (preB[i][j]==0);
        }
    }


    cout << "Grafo tombuctu" << endl;
    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
                if(B[i][j])
                    cout << "1 ";
                else
                    cout << "0 ";
        }
        cout << endl;
    }




    vector<tCiudad> ciudades = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10}};

    tDistribucion dist = Tombuctu(B,ciudades);
    
    cout << "Costes minimos tombuctu" << endl;
    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
                cout << dist.M[i][j];
        }
        cout << endl;
    }
    
    for(size_t i = 0; i<10;i++){
        cout << i << "esta en" << dist.p.encontrar(i) << endl;
    }

    return 0;
};