
#ifndef ALG_GRAFO_H
#define ALG_GRAFO_H
#include "grafoMA.h"  
#include "matriz.h"    
#include "listaenla.h" 


matriz<bool> Warshall(const Grafo& G);


Lista<Grafo::vertice> Profundidad(const Grafo& G, Grafo::vertice v);

Lista<Grafo::vertice> Profundidad2(const Grafo& G, Grafo::vertice v);

Lista<Grafo::vertice> Anchura(const Grafo& G, Grafo::vertice v);

#endif   // ALG_GRAFO_H
