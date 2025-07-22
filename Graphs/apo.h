

#ifndef APO_H
#define APO_H
#include <cassert>

template <typename T> class Apo {
public:
   explicit Apo(size_t maxNodos);       // constructor
   void insertar(const T& e);
   void suprimir();
   const T& cima() const;
   bool vacio() const;
   Apo(const Apo& A);                   
   Apo& operator =(const Apo& A);       
   ~Apo();                              
private:
   typedef size_t nodo; 
                        
   T* nodos;          
   size_t maxNodos;   
   size_t numNodos;   

   nodo padre(nodo i) const { return (i-1)/2; }
   nodo hIzq(nodo i)  const { return 2*i+1; }
   nodo hDer(nodo i)  const { return 2*i+2; }
   void flotar(nodo i);
   void hundir(nodo i);
};


template <typename T>
inline Apo<T>::Apo(size_t maxNodos) :
   nodos(new T[maxNodos]),
   maxNodos(maxNodos),
   numNodos(0)   
{}

template <typename T>
inline void Apo<T>::insertar(const T& e)
{
   assert(numNodos < maxNodos);   
   nodos[numNodos] = e;
   if (++numNodos > 1)
      flotar(numNodos-1);
}

template <typename T>
inline void Apo<T>::suprimir()
{
   assert(numNodos > 0);   
   if (--numNodos > 0) {     
      nodos[0] = nodos[numNodos];
      if (numNodos > 1)     
         hundir(0);         
   }
}

template <typename T>
inline const T& Apo<T>::cima() const
{
   assert(numNodos > 0);   
   return nodos[0];
}

template <typename T>
inline bool Apo<T>::vacio() const
{
   return (numNodos == 0);
}

template <typename T>
inline Apo<T>::~Apo()
{
   delete[] nodos;
}

template <typename T>
Apo<T>::Apo(const Apo<T>& A) :
   nodos(new T[A.maxNodos]),
   maxNodos(A.maxNodos),
   numNodos(A.numNodos)
{
   for (nodo n = 0; n < numNodos; n++)
      nodos[n] = A.nodos[n];
}

template <typename T>
Apo<T>& Apo<T>::operator =(const Apo<T>& A)
{
   if (this != &A) {   
      if (maxNodos != A.maxNodos) {
         delete[] nodos;
         maxNodos = A.maxNodos;
         nodos = new T[maxNodos];
      }
      numNodos = A.numNodos;
      for (nodo n = 0; n < numNodos; n++)
         nodos[n] = A.nodos[n];
   }
   return *this;
}


template <typename T>
void Apo<T>::flotar(nodo i)
{
   T e = nodos[i];
   while (i > 0 && e < nodos[padre(i)]) {
      nodos[i] = nodos[padre(i)];
      i = padre(i);
   }
   nodos[i] = e;  
}

template <typename T>
void Apo<T>::hundir(nodo i)
{
   bool fin = false;
   T e = nodos[i];
   while (hIzq(i) < numNodos && !fin) {   
      if (hDer(i) < numNodos && nodos[hDer(i)] < nodos[hIzq(i)])
         hMin = hDer(i);
      else
         hMin = hIzq(i);
      if (nodos[hMin] < e) {
         nodos[i] = nodos[hMin];
         i = hMin;
      }
      else   
         fin = true;
   }
   nodos[i] = e;   
}

#endif // APO_H
