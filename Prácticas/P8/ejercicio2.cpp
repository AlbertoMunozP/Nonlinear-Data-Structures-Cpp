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

struct tLineaAerea{
    tCiudad c1,c2;
    //Sobrevargar <
};

long double distancia(tCiudad c1, tCiudad c2){
    return sqrt(pow(c1.x-c2.x,2)+pow(c1.y-c2.y,2));
}


struct lineaAerea {
    tCiudad c1, c2;
    double distancia;
    lineaAerea(tCiudad x, tCiudad y, double d) : c1(x), c2(y), distancia(d) {}
};

double distEuclidea(tCiudad c1, tCiudad c2)
{ return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2)); }

size_t ciudad_to_isla(tCiudad c, vector<tCiudad> ciudades, vector<int> repres, Particion p)
{
    // Busco la ciudad
    bool encontrado = false;
    size_t iter = 0;
    while (iter < ciudades.size() && !encontrado)
    {
        if(ciudades[iter].x == c.x && ciudades[iter].y == c.y)
            encontrado = true;
        else
            iter++;
    }

    // Busco representante
    int rep = p.encontrar(iter);
    encontrado = false;
    iter = 0;
    while(iter < repres.size() && !encontrado)
    {
        if(repres[iter] == rep)
            return iter;
        else
            iter++;
    }
}

vector<lineaAerea> Tombuctu2 (const Grafo& arch, vector<tCiudad> ciudades)
{
    const size_t nCiudades = arch.numVert();
    size_t nIslas = nCiudades;
    Particion p(nCiudades);

    typedef typename Grafo::vertice vertice;

    // Contar el número de islas
    for (vertice i = 0 ; i < nCiudades ; i++)
        for (vertice j = 0 ; j < nCiudades ; j++)
            if (arch[i][j] && p.encontrar(i) != p.encontrar(j)) {
                p.unir(p.encontrar(i),p.encontrar(j));
                nIslas--;
            }

    // Representantes de cada isla
    vector<int> repres(nIslas);
    int numRepres = 0;
    for(size_t i = 0 ; i < ciudades.size() && numRepres < nIslas ; i++)
    {
        int repreActual = p.encontrar(i);
        size_t iter = 0;
        bool encontrado = false;
        while (iter < numRepres && !encontrado)
        {
            if (repres[iter] == repreActual)
                encontrado = true;
            else
                iter++;
        }

        if (!encontrado)
        {
            repres[numRepres] = repreActual;
            numRepres++;
        }
    }

    // Insertar todas las lineas aéreas en un APO
    Apo<lineaAerea> APO(nCiudades * (nCiudades - 1) / 2);
    
    for(int i = 0; i < nCiudades-1; i++)
        for(int j = i+1; j < nCiudades; j++)
            APO.insertar(lineaAerea(ciudades[i], ciudades[j], distEuclidea(ciudades[i], ciudades[j])));

    // Vuelos mínimos
    matriz<bool> minimos(nIslas);
    for (size_t i = 0 ; i < nIslas ; i++)
        for (size_t j = i ; j < nIslas ; j++)
            minimos[i][j] = minimos[j][i] = false;

    vector<lineaAerea> vuelos(nIslas * (nIslas - 1) / 2);
    int cont = 0;
    while(cont < nIslas * (nIslas - 1) / 2)
    {
        lineaAerea la = APO.cima();
        APO.suprimir();
        size_t isla1 = ciudad_to_isla(la.c1, ciudades, repres, p);
        size_t isla2 = ciudad_to_isla(la.c2, ciudades, repres, p);
        // Comprobar tambien isla1!=isla2
        if (isla1!=isla2 && minimos[isla1][isla2] == false) {
            minimos[isla1][isla2] = minimos[isla2][isla1] = true;
            vuelos.push_back(la);
        }
    }

    return vuelos;
}


/* Clase de práctica
    - Lo primero ver cuantas líneas aéreas se necesitan
    (n*n-1/2) porque dice el enunciado que tiene que haber
    una linea directa entre cada par de islas
    - RepToNislas para poner los representantes en un vector
    de 0 a nIslas-1 y tener una matriz de nIslas x nIslas 
    La otra version numero minimo de lineas

    Muy importante!
    n-1 numero minimo
    n*(n-1)/2 numero entre cada par

    Si aplico el algoritmo de Kruskall o Prim a un grafo
    con dos componentes conexas, no aparecerá una arista
    que conecte a esos dos componentes conexas
*/


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