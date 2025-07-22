
#ifndef GRAFO_LIS_ADY_H
#define GRAFO_LIS_ADY_H
#include <vector>
#include <iostream>
#include <string>
#include "listaenla.h"

class Grafo {
public:
   typedef size_t vertice;

   explicit Grafo(size_t n): ady(n) {}
   explicit Grafo(const std::string& nf);
   size_t numVert() const {return ady.size();}
   const Lista<vertice>& adyacentes(vertice v) const {return ady[v];}
   Lista<vertice>& adyacentes(vertice v) {return ady[v];}
private:
   std::vector< Lista<vertice> > ady; 
};

std::ostream& operator <<(std::ostream& os, const Grafo& G);

#endif   // GRAFO_LIS_ADY_H
