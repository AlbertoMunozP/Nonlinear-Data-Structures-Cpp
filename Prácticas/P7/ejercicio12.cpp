#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

template<typename tCoste>
tCoste sumador(const vector<tCoste>& m){
    tCoste cont = 0;
    for(size_t i = 0; i<m.size(); i++){
        if(m[i]!=GrafoP<tCoste>::INFINITO)
            cont += m[i];
    }
    return cont;
}

template<typename tCoste>
tCoste min9(tCoste a, tCoste b, tCoste c, tCoste d,
tCoste e, tCoste f, tCoste g, tCoste h, tCoste i){
    tCoste x = min(min(a,b),min(c,d));
    tCoste y = min(min(e,f),min(g,h));
    return min(i, min(x,y));
}

template<typename tCoste>
struct tPuente
{
    typename GrafoP<tCoste>::vertice v1,v2;
};


template<typename tCoste>
tPuente<tCoste> grecoland
(const GrafoP<tCoste>& Fobos, const GrafoP<tCoste>& Deimos,
vector<typename GrafoP<tCoste>::vertice> cFobos,
vector<typename GrafoP<tCoste>::vertice> cDeimos
)
{
    const size_t n1 = Fobos.numVert();
    const size_t n2 = Deimos.numVert();
    const size_t n = n1+n2;
    typedef typename GrafoP<tCoste>::vertice vertice;

    vertice verticeF = 0;
    tCoste minimoF = GrafoP<tCoste>::INFINITO;

    for(size_t i = 0; i<cFobos.size(); i++){
        vector<vertice> vrt(n1);
        vector<tCoste> costesF = Dijkstra(Fobos,cFobos[i],vrt);
        tCoste valor = sumador(costesF);
        if(valor<minimoF){
            verticeF = cFobos[i];
            minimoF = valor;
        }
    }


    vertice verticeD = 0;
    tCoste minimoD = GrafoP<tCoste>::INFINITO;

    for(size_t j = 0; j<cDeimos.size(); j++){
        vector<vertice> vrtD(n1);
        vector<tCoste> costesD = Dijkstra(Deimos,cDeimos[j],vrtD);
        tCoste actual = sumador(costesD);
        if(actual<minimoD){
            verticeD = cDeimos[j];
            minimoD = actual;
        }
    }

    tPuente<tCoste> p;
    p.v1 = verticeF;
    p.v2 = verticeD;

    return p;

    /*

    ya corregido :

    Esta mal esta forma porque siempre saldria el mismo
    valor en el sumador porque se balancea,
    lo  que habria que hacer es un dijkstra por cada costera
    y veo cual es la que es mas barata tomar como origen 
    en su isla, asi hago en fobos y en deimos y creo el puente
    entre las dos costeras que abaratan viajar en sus respectivas 
    islas
    */

}


int main(){
    GrafoP<int> T(10);
    GrafoP<int> A(10);

    // GENERAR NUMEROS ALEATORIOS:

    // Obtener una semilla aleatoria utilizando std::random_device
    random_device rd;
    // Utilizar la semilla para inicializar el generador de números aleatorios
    mt19937 gen(rd());
    // Definir la distribución (por ejemplo, distribución uniforme entre 1 y 100)
    uniform_int_distribution<> dis(1, 26);

    for(size_t i = 0; i<10;i++){
        for(size_t j = 0; j<10;j++){
            if(i==j){
                T[i][j] = 0;
                A[i][j] = 0;
            }
            else{
                T[i][j] = dis(gen);
                A[i][j] = dis(gen)-1;
            }
                
        }
    }
    cout<<"Fobos---------------"<<endl;
    cout<<T;
    cout<<"Deimos--------------"<<endl;
    cout<<A;    

    tPuente<int>  p;
    p = grecoland(T,A,{{0},{1},{2},{3},{4}},{ {5},{6},{7},{8},{9} });
    cout<<"Puente: "<<p.v1<<" "<<p.v2<<endl;
    return 0;
};