

#ifndef LISTA_ENLA_H
#define LISTA_ENLA_H
#include <cassert>

template <typename T> class Lista {
   struct nodo;   
public:
   typedef nodo* posicion;     
   Lista();                    
   Lista(const Lista<T>& Lis); 
   Lista<T>& operator =(const Lista<T>& Lis); 
   void insertar(const T& x, posicion p);
   void eliminar(posicion p);
   const T& elemento(posicion p) const;
   T& elemento(posicion p);            
   posicion buscar(const T& x) const;
   posicion siguiente(posicion p) const;
   posicion anterior(posicion p) const;
   posicion primera() const;
   posicion fin() const;      
   ~Lista();                  
   Lista<T>& operator +=(const Lista<T>& l); 
private:
   struct nodo {
      T elto;
      nodo* sig;
      nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
   };

   nodo* L;   

   void copiar(const Lista<T>& Lis);
};


template <typename T>
void Lista<T>::copiar(const Lista<T> &Lis)
{
   L = new nodo(T());  // Crear el nodo cabecera
   nodo* q = L;
   for (nodo* r = Lis.L->sig; r; r = r->sig) {
      q->sig = new nodo(r->elto);
      q = q->sig;
   }
}

template <typename T>
inline Lista<T>::Lista() : L(new nodo(T())) // Crear cabecera
{}

template <typename T>
inline Lista<T>::Lista(const Lista<T>& Lis)
{
   copiar(Lis);
}

template <typename T>
Lista<T>& Lista<T>::operator =(const Lista<T>& Lis)
{
   if (this != &Lis) {  // Evitar autoasignaci�n
      this->~Lista();   // Vaciar la lista actual
      copiar(Lis);
   }
   return *this;
}

template <typename T> inline
void Lista<T>::insertar(const T& x, Lista<T>::posicion p)
{
   p->sig = new nodo(x, p->sig);
   // El nuevo nodo con x queda en la posici�n p
}

template <typename T>
inline void Lista<T>::eliminar(Lista<T>::posicion p)
{
   assert(p->sig); // p no es fin
   nodo* q = p->sig;
   p->sig = q->sig;
   delete q;
   // El nodo siguiente queda en la posici�n p
}

template <typename T> inline
const T& Lista<T>::elemento(Lista<T>::posicion p) const
{
   assert(p->sig);   // p no es fin
   return p->sig->elto;
}

template <typename T>
inline T& Lista<T>::elemento(Lista<T>::posicion p)
{
   assert(p->sig);   // p no es fin
   return p->sig->elto;
}

template <typename T>
typename Lista<T>::posicion
   Lista<T>::buscar(const T& x) const
{
   nodo* q = L;
   bool encontrado = false;
   while (q->sig && !encontrado)
      if (q->sig->elto == x)
         encontrado = true;
      else q = q->sig;
   return q;
}

template <typename T> inline
typename Lista<T>::posicion
   Lista<T>::siguiente(Lista<T>::posicion p) const
{
   assert(p->sig);   // p no es fin
   return p->sig;
}

template <typename T>
typename Lista<T>::posicion
   Lista<T>::anterior(Lista<T>::posicion p) const
{
   nodo* q;

   assert(p != L);   // p no es la primera posici�n
   for (q = L; q->sig != p; q = q->sig);
   return q;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
   return L;
}

template <typename T>
typename Lista<T>::posicion Lista<T>::fin() const
{
   nodo* p;
   for (p = L; p->sig; p = p->sig);
   return p;
}

// Destructor: destruye el nodo cabecera y vac�a la lista
template <typename T> Lista<T>::~Lista()
{
   nodo* q;
   while (L) {
      q = L->sig;
      delete L;
      L = q;
   }
}


template<typename T>
Lista<T>& Lista<T>::operator +=(const Lista<T>& L)
{
   for (Lista<T>::posicion i = L.primera(); i != L.fin(); i = L.siguiente(i))
      insertar(L.elemento(i), fin());
   return *this;
}

template<typename T>
Lista<T> operator +(const Lista<T>& L1, const Lista<T>& L2)
{
   return Lista<T>(L1) += L2;
}

#endif // LISTA_ENLA_H
