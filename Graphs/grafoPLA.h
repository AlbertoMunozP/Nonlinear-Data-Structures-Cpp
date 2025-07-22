

#ifndef GRAFO_PON_LIS_ADY_H
#define GRAFO_PON_LIS_ADY_H
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <ostream>
#include "listaenla.h"

using std::vector;

template <typename T> class GrafoP {
public:
   typedef T tCoste;
   typedef size_t vertice;
   typedef Lista<vertice> tCamino;

   struct vertice_coste {
      vertice v;
      tCoste c;
      bool operator ==(const vertice_coste& vc) const {return v == vc.v;}
   };

   static const tCoste INFINITO;

   GrafoP(size_t n): ady(n) {}
   GrafoP(const std::string& nf);
   size_t numVert() const {return ady.size();}
   const Lista<vertice_coste>& adyacentes(vertice v) const {return ady[v];}
   Lista<vertice_coste>& adyacentes(vertice v) {return ady[v];}
private:
   vector< Lista<vertice_coste> > ady;
};

template <typename T>
const T GrafoP<T>::INFINITO = std::numeric_limits<T>::max();

template <typename T>
GrafoP<T>::GrafoP(const std::string& nf)
{
   char c;
   std::string cad;
   vertice v, w;
   tCoste p;
   vertice_coste vc;
   std::ifstream fg(nf);           
   unsigned n;                     

   fg >> n;
   ady = vector< Lista<vertice_coste> >(n);
   while (fg >> v) {
      fg >> c; 
      std::getline(fg, cad);
      std::istringstream ss(cad);
      while (ss >> vc.v && ss >> vc.c)
         ady[v].insertar(vc, ady[v].fin());
   }
   fg.close();                     
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const GrafoP<T>& G)
{
   typedef typename GrafoP<T>::vertice vertice;
   typedef typename Lista<typename GrafoP<T>::vertice_coste>::posicion posicion;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   for (vertice i = 0; i < n; i++)
      if (G.adyacentes(i).primera() != G.adyacentes(i).fin()) {
         os << i << ':';
         for (posicion p = G.adyacentes(i).primera();
              p != G.adyacentes(i).fin();
              p = G.adyacentes(i).siguiente(p))
            os << ' ' << G.adyacentes(i).elemento(p).v
               << ' ' << G.adyacentes(i).elemento(p).c;
         os << std::endl;
      }
   return os;
}

#endif   // GRAFO_PON_LIS_ADY_H
