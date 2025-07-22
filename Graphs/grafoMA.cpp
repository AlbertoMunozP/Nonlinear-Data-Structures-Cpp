

#include "grafoMA.h"
#include <fstream>
#include <sstream>
#include <iomanip>

Grafo::Grafo(const std::string& nf)
{
   char c;
   std::string cad;
   vertice v, w;
   std::ifstream fg(nf);           
   unsigned n;                     

   fg >> n;
   ady = vector< vector<bool> >(n, vector<bool>(n, false));
   while (fg >> v) {
      fg >> c; // extrae ':'
      std::getline(fg, cad);
      std::istringstream ss(cad);
      while (ss >> w)
         ady[v][w] = true;
   }
   fg.close();
}

bool Grafo::esDirigido() const
{
   bool s = true;  
   const size_t n = numVert();
   vertice i = 0;
   while (s && i < n) {
      vertice j = i+1;
      while (s && j < n) {
         s = (ady[i][j] == ady[j][i]);
         ++j;
      }
      ++i;
   }
   return !s;  
}

std::ostream& operator <<(std::ostream& os, const Grafo& G)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   os << n << " vertices" << std::endl;
   os << "   ";
   for (vertice j = 0; j< n; j++)
      os << std::setw(3) << j;
   os << std::endl;
   for (vertice i = 0; i < n; i++) {
      os << std::setw(3) << i;
      for (vertice j = 0; j < n; j++)
         os << std::setw(3) << G[i][j];
      os << std::endl;
   }
   return os;
}
