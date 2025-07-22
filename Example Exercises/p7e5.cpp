#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
Lista<typename GrafoP<tCoste>::vertice> alergico
(typename GrafoP<tCoste>::vertice origen,
const GrafoP<tCoste>& C, const GrafoP<tCoste>& T,
const GrafoP<tCoste>& A, char alergia, tCoste saldo)
{
    const size_t n = A.numVert();
    GrafoP<tCoste> V(n);
    typedef typename GrafoP<tCoste>::vertice vertice;

    switch (alergia)
    {
    case 'C':
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < n; j++)
                V[i][j] = min(T[i][j],A[i][j]);
        break;
    case 'T':
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < n; j++)
                V[i][j] = min(C[i][j],A[i][j]);
        break;
    case 'A':
        for(size_t i = 0; i < n; i++)
            for(size_t j = 0; j < n; j++)
                V[i][j] = min(T[i][j],C[i][j]);
        break;
    default:
        break;
    }

    vector<vertice> verts(n);
    vector<tCoste> costes = Dijkstra(V,origen,verts);
    Lista<vertice> L();
    for(size_t i = 0; i < n; i++)
        if(costes[i] < saldo && i != origen)
            L.insertar(i,L.fin());
    
    return L;
}


int main(){
    GrafoP<int> C(10);
    GrafoP<int> T(10);
    GrafoP<int> A(10);


    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
            if(i==j){
                C[i][j] = 0;
                T[i][j] = 0;
                A[i][j] = 0;
            }
            else{
                C[i][j] = dis(gen)+1;
                T[i][j] = dis(gen);
                A[i][j] = dis(gen)-1;
            }
                
        }
    }
    cout<<"COCHE--------------"<<endl;
    cout<<C;
    cout<<"TREN---------------"<<endl;
    cout<<T;
    cout<<"AVION--------------"<<endl;
    cout<<A;
    cout<<"El origen del viajero es 4";
    Lista<typename GrafoP<int>::vertice> v = alergico<int>(4,C,T,A,'A',20);
    Lista<typename GrafoP<int>::vertice>::posicion p = v.primera();  
    for (p = p; p != v.fin(); p = v.siguiente(p)){
        cout<<" "<<v.elemento(p);
    }
    return 0;
};