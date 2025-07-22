#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;


template<typename tCoste>
tCoste reteuni3 
(const GrafoP<tCoste>& G)
{
    typedef typename Grafo::vertice vertice;
    const size_t n = G.numVert();

    GrafoP<tCoste> K = G;
    
    K = Kruskall(K);

    cout<<K;

    tCoste minimo = 0;
    for(size_t i = 0; i<n;i++){
        for(size_t j = i; j<n;j++){
            if(K[i][j]!=GrafoP<tCoste>::INFINITO)
                minimo += K[i][j];
                
        }
    }
    return minimo;
}


int main(){
    GrafoP<int> T(10);
    GrafoP<int> A(10);


    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = i; j<10;j++){
            if(i==j){
                T[i][j] = 0;
            }
            else{
                T[i][j] = T[j][i] = dis(gen);
            }
                
        }
    }
    cout<<"TREN---------------"<<endl;
    cout<<T;
    int x = reteuni3(T);
    cout<<"LA longitud minima es "<<x<<endl;
    return 0;
};