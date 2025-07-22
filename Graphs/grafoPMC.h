

#ifndef GRAFO_PON_H
#define GRAFO_PON_H
#include <vector>
#include <limits>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "listaenla.h" 
#include "grafoMA.h"   

using std::vector;

template <typename T> class GrafoP {
public:
   typedef T tCoste;
   typedef size_t vertice;
   struct arista {
      vertice orig, dest;
      tCoste coste;
      explicit arista(vertice v = vertice(), vertice w = vertice(),
                      tCoste c = tCoste()): orig(v), dest(w), coste(c) {}
      bool operator <(const arista& a) const {return coste < a.coste;}
   };
   typedef Lista<vertice> tCamino;

   static const tCoste INFINITO;

   explicit GrafoP(size_t n): costes(n, vector<tCoste>(n, INFINITO)) {}
   explicit GrafoP(const std::string& nf);
   GrafoP(const Grafo& G);
   size_t numVert() const {return costes.size();}
   const vector<tCoste>& operator [](vertice v) const {return costes[v];}
   vector<tCoste>& operator [](vertice v) {return costes[v];}
   bool esDirigido() const;
private:
   vector< vector<tCoste> > costes;
};

template <typename T>
const T GrafoP<T>::INFINITO = std::numeric_limits<T>::max();

template <typename T>
GrafoP<T>::GrafoP(const std::string& nf)
{
   std::ifstream fg(nf);           
   unsigned n;                    
   fg >> n;
   costes = vector<vector<T> >(n, vector<T>(n));
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         fg >> costes[i][j];
   fg.close();                     
}

template <typename T>
GrafoP<T>::GrafoP(const Grafo& G):
   costes(G.numVert(), vector<T>(G.numVert()))
{
   const size_t n = G.numVert();
   for (vertice i = 0; i < n; i++)
      for (vertice j = 0; j < n; j++)
         costes[i][j] = G[i][j] ? 1 : GrafoP<T>::INFINITO;
}

template <typename T>
bool GrafoP<T>::esDirigido() const
{
   bool s = true;   
   const size_t n = numVert();
   vertice i = 0;
   while (s && i < n) {
      vertice j = i+1;
      while (s && j < n) {
         s = (costes[i][j] == costes[j][i]);
         ++j;
      }
      ++i;
   }
   return !s;  
}

template <typename T>
std::ostream& operator <<(std::ostream& os, const GrafoP<T>& G)
{
   typedef typename GrafoP<T>::vertice vertice;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   os << "    ";
   for (vertice j = 0; j < n; j++)
      os << std::setw(4) << j;
   os << std::endl;
   for (vertice i = 0; i < n; i++) {
      os << std::setw(4) << i;
      for (vertice j = 0; j < n; j++) {
         os << std::setw(4);
         if (G[i][j] == GrafoP<T>::INFINITO)
            os << "-";
         else
            os << G[i][j];
      }
      os << std::endl;
   }
   return os;
}

#endif   // GRAFO_PON_H
