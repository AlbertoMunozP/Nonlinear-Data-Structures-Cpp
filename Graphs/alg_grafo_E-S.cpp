

#include "alg_grafo_E-S.h"
#include <iomanip>           // std::setw

template <>
ostream& operator << <bool>(ostream& os, const matriz<bool>& m)
{
   const size_t n = m.dimension();
   os << "   ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(3) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(3) << i;
      for (size_t j = 0; j < n; ++j)
         os << std::setw(3) << m[i][j];
      os << std::endl;
   }
   return os;
}

template <>
ostream& operator << <size_t>(ostream& os, const Lista<size_t>& L)
{
   typedef Lista<Grafo::vertice>::posicion posicion;
   for (posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
      os << L.elemento(i) << ' ';
   return os;
}
