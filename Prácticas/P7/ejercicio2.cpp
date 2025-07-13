#include<iostream>
#include <random>
#include "alg_grafoPMC.h"

/* Ejercicio de examen, dice juanfran */

using namespace std;


struct casilla{
    size_t fila,columna;
};


struct tPared{
   casilla a,b;
};

// N = dimension
typename GrafoP<size_t>::vertice casilla_to_vertice(casilla a, size_t N){
    typename GrafoP<size_t>::vertice v = a.fila * N + a.columna;
    return v;
}

casilla vertice_to_casilla(typename GrafoP<size_t>::vertice v, size_t N){
    casilla c;
    c.fila = v / N;
    c.columna = v % N;
    return c;
}


bool adyacentes(casilla a, casilla b){
    return ((abs(a.fila-b.fila)+abs(a.columna-b.columna)) == 1);
}


struct tCamino{
    size_t coste;
    Lista<casilla> ruta;
};



tCamino laberintoNN(casilla origen, casilla destino,
vector<tPared> paredes, size_t N)
{
    const size_t n = N*N;
    typedef typename GrafoP<size_t>::vertice vertice;
    GrafoP<size_t> G(n);

    for(size_t i = 0; i < n; i++){
        for(size_t j = 0; j < n; j++){
            if(adyacentes(vertice_to_casilla(i,N),vertice_to_casilla(j,N)))
                G[i][j] = 1;
            else
                G[i][j] = GrafoP<size_t>::INFINITO;                
        }
    }

    /*
    Por ser no dirigido esto tambien vale:
    for(size_t i = 0; i < N; i++){
        for(size_t j = i; j < N; j++){
            if(adyacentes(vertice_to_casilla(i,N),vertice_to_casilla(j,N)))
                G[i][j] = G[j][i] = 1;
            else
                G[i][j] = G[j][i] = GrafoP<size_t>::INFINITO;                
        }
    }
    */
    for(size_t a = 0; a < paredes.size(); a++){
        vertice v1 = casilla_to_vertice(paredes[a].a, N);
        vertice v2 = casilla_to_vertice(paredes[a].b, N);
        G[v1][v2] = G[v2][v1] = GrafoP<size_t>::INFINITO;
    }
    vector<vertice> vertices(N);
    vector<size_t> costes = Dijkstra(G,casilla_to_vertice(origen,N),vertices);
    
    tCamino c;
    c.coste = costes[casilla_to_vertice(destino,N)];
    Lista<casilla> cRuta;
    // La funcion camino trabaja con vertices unicamente muty importante!!
    GrafoP<size_t>::tCamino ruta = camino<vertice>(casilla_to_vertice(origen,N),casilla_to_vertice(destino,N), vertices);
    for (Lista<size_t>::posicion v = ruta.primera() ; v != ruta.fin() ; v = ruta.siguiente(v))
        cRuta.insertar(vertice_to_casilla(ruta.elemento(v), N), cRuta.fin());
    c.ruta = cRuta;
    return c;
}

int main(){
    /* Ejercicio de examen, dice juanfran */
    GrafoP<int> G(10);

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

    return 0;
}