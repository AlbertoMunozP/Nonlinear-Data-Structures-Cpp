#include<iostream>
#include <random>
#include "alg_grafoPMC.h"
#include "listaenla.h"
#include<vector>

using namespace std;

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
    GrafoP<tCoste>::vertice v1,v2;
    /* Suponemos que nos dan los vertices
    que corresponden en el supergrafo, para
    ahorrarnos problema de saber isla de cada vertice
    */
};

template<typename tCoste>
matriz<tCoste> supergrafo
(const GrafoP<tCoste>& isla1, const GrafoP<tCoste>& isla2,
const GrafoP<tCoste>& isla3,
vector<tPuente<tCoste>> puentes
)
{
    const size_t n1 = isla1.numVert();
    const size_t n2 = isla2.numVert();
    const size_t n3 = isla3.numVert();
    typedef typename GrafoP<tCoste>::vertice vertice;
    GrafoP<tCoste> SG(n1+n2+n3);

    // Añadimos costes isla 1
    for(size_t i = 0; i<n1; i++){
        for(size_t j = 0; j<n1; j++){
            SG[i][j] = isla1 [i][j]
        }
    }
    // Añadimos costes isla 2
    for(size_t i = n1; i<n1+n2; i++){
        for(size_t j = n1; j<n1+n2; j++){
            SG[i][j] = isla1 [i-n1][j-n1]
        }
    }
    // Añadimos costes isla 3
    for(size_t i = n1+n2; i<n; i++){
        for(size_t j = n1+n2; j<n; j++){
            SG[i][j] = isla1[i-n1-n2][j-n1-n2]
        }
    }
    // Añadimos los puentes
    for(size_t i = 0; i < puentes.size(); i++){
        SG[puentes[i].v1][puentes[i].v2] = 0;
        SG[puentes[i].v2][puentes[i].v1] = 0;
    }
    
    matriz<vertice> verts(n);
    matriz<tCoste> costes = Floyd(SG,verts);

    return costes;

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
    cout<<"TREN---------------"<<endl;
    cout<<T;
    cout<<"BUS--------------"<<endl;
    cout<<A;    
    return 0;
};