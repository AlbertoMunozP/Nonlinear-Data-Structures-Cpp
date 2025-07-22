

#ifndef ALG_GRAFO_E_S_H
#define ALG_GRAFO_E_S_H
#include "grafoPMC.h"  
#include <vector>
#include "matriz.h"    
#include "listaenla.h" 
#include <ostream>

using std::ostream;

template <typename T>
ostream& operator <<(ostream& os, const vector<T>& v)
{
   for (size_t i = 0; i < v.size(); i++) {
      os << std::setw(4);
      if (v[i] != GrafoP<T>::INFINITO)
         os << v[i];
      else
         os << "-";
   }
   return os;
}

template <typename T>
ostream& operator << (ostream& os, const matriz<T>& m)
{
   const size_t n = m.dimension();
   os << "    ";
   for (size_t j = 0; j < n; ++j)
      os << std::setw(4) << j;
   os << std::endl;
   for (size_t i = 0; i < n; ++i) {
      os << std::setw(4) << i;
      for (size_t j = 0; j < n; ++j) {
         os << std::setw(4);
         if (m[i][j] == GrafoP<T>::INFINITO)
            os << "-";
         else
            os << m[i][j];
      }
      os << std::endl;
   }
   return os;
}

template <>
ostream& operator << <bool>(ostream& os, const matriz<bool>& m);

template <typename T>
ostream& operator <<(ostream&, const Lista<T>&);
template <>
ostream& operator << <size_t>(ostream& os, const Lista<size_t>& c);

#endif   // ALG_GRAFO_E_S_H
