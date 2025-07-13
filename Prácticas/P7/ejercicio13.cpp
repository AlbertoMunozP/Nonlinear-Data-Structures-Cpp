#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

/* Este es exactamente lo mismo que 
el anterior pero con tres islas
*/

/* Nota: si dice que tiene que haber
un puente entre cada par de islas
serian n*(n-1)/2 y si es el numero minimo
de puentes seran n-1
*/


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
struct tPuente
{
    typename GrafoP<tCoste>::vertice v1,v2;
};

template<typename tCoste>
struct tConexion
{
    tPuente<tCoste> p,q;
};


template <typename tCoste>
tConexion<tCoste> huries (const GrafoP<tCoste>& isla1, 
const GrafoP<tCoste>& isla2, 
const GrafoP<tCoste>& isla3, 
vector<typename GrafoP<tCoste>::vertice> costeras1, 
vector<typename GrafoP<tCoste>::vertice> costeras2, 
vector<typename GrafoP<tCoste>::vertice> costeras3)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n1 = isla1.numVert();
    const size_t n2 = isla2.numVert();
    const size_t n3 = isla3.numVert();

    vertice vertice1 = 0;
    tCoste minimo1 = GrafoP<tCoste>::INFINITO;

    for(size_t i = 0; i<costeras1.size(); i++){
        vector<vertice> vrt(n1);
        vector<tCoste> costes1 = Dijkstra(isla1,costeras1[i],vrt);
        tCoste valor = sumador(costes1);
        if(valor<minimo1){
            vertice1 = costeras1[i];
            minimo1 = valor;
        }
    }

    vertice vertice2 = 0;
    tCoste minimo2 = GrafoP<tCoste>::INFINITO;

    for(size_t j = 0; j<costeras2.size(); j++){
        vector<vertice> vrt2(n2);
        vector<tCoste> costes2 = Dijkstra(isla2,costeras2[j],vrt2);
        tCoste actual = sumador(costes2);
        if(actual<minimo2){
            vertice2 = costeras2[j];
            minimo2 = actual;
        }
    }

    vertice vertice3 = 0;
    tCoste minimo3 = GrafoP<tCoste>::INFINITO;

    for(size_t k = 0; k<costeras3.size(); k++){
        vector<vertice> vrt3(n3);
        vector<tCoste> costes3 = Dijkstra(isla3,costeras3[k],vrt3);
        tCoste actual = sumador(costes3);
        if(actual<minimo3){
            vertice3 = costeras3[k];
            minimo3 = actual;
        }
    }

    tPuente<tCoste> p12, p23;
    p12.v1 = vertice1;
    p12.v2 = vertice2;

    p23.v1 = vertice2;
    p23.v2 = vertice3;

    tConexion<tCoste> conex;
    conex.p = p12;
    conex.q = p23;

    return conex;
}





int main(){
    GrafoP<int> T(10);
    GrafoP<int> A(10);
    GrafoP<int> X(10);

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
                X[i][j] = 0;
            }
            else{
                T[i][j] = dis(gen);
                A[i][j] = dis(gen)-1;
                X[i][j] = dis(gen)%23; 
            }
                
        }
    }
    cout<<"isla1---------------"<<endl;
    cout<<T;
    cout<<"isla2--------------"<<endl;
    cout<<A;    
    cout<<"isla3--------------"<<endl;
    cout<<X;

    tConexion<int> c = huries(T,A,X,{{0},{1},{2},{3},{4}},{ {5},{6},{7},{8},{9} },{ {5},{6},{7}}) ;
    cout<<endl;
    cout << c.p.v1 << "---" << c.p.v2;
    cout<<endl;
    cout << c.q.v1 << "---" << c.q.v2;

    return 0;
};