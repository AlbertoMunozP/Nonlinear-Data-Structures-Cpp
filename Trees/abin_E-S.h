#ifndef ABIN_E_S_H
#define ABIN_E_S_H

#include <cassert>
#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

template <typename T>
void rellenarAbin(Abin<T>& A, const T& fin)
{
   T e;

   assert(A.arbolVacio());
   cout << "Raíz (Fin = " << fin << "): "; cin >> e;
   if (e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(typename Abin<T>::nodo n, Abin<T>& A, const T& fin)
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Abin<T>::NODO_NULO &&
          A.hijoDrcho(n) == Abin<T>::NODO_NULO);
   cout << "Hijo izqdo. de " << A.elemento(n) <<
                " (Fin = " << fin << "): ";
   cin >> ehi;
   if (ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(A.hijoIzqdo(n), A, fin);
   }
   cout << "Hijo drcho. de " << A.elemento(n) <<
                " (Fin = " << fin << "): ";
   cin >> ehd;
   if (ehd != fin) {
      A.insertarHijoDrcho(n, ehd);
      rellenarDescendientes(A.hijoDrcho(n), A, fin);
   }
}

template <typename T>
void rellenarAbin(istream& is, Abin<T>& A)
{
   T e, fin;

   assert(A.arbolVacio());
   if (is >> fin && is >> e && e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(is, A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(istream& is, typename Abin<T>::nodo n, Abin<T>& A, const T& fin)
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Abin<T>::NODO_NULO &&
          A.hijoDrcho(n) == Abin<T>::NODO_NULO);
   if (is >> ehi && ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(is, A.hijoIzqdo(n), A, fin);
   }
   if (is >> ehd && ehd != fin) {
      A.insertarHijoDrcho(n, ehd);
      rellenarDescendientes(is, A.hijoDrcho(n), A, fin);
   }
}

template <typename T>
void imprimirAbin (const Abin<T>& A)
{
   if (!A.arbolVacio())
   {
      cout << "Raíz del árbol: "
                << A.elemento(A.raiz()) << endl;
      imprimirDescendientes(A.raiz(), A);
   }
   else
      cout << "Árbol vacío\n";
}

template <typename T>
void imprimirDescendientes (typename Abin<T>::nodo n, const Abin<T>& A)
{
   if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
   {
      cout << "Hijo izqdo de " << A.elemento(n) << ": "
                << A.elemento(A.hijoIzqdo(n)) << endl;
      imprimirDescendientes(A.hijoIzqdo(n), A);
   }
   if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
   {
      cout << "Hijo derecho de " << A.elemento(n) << ": "
                << A.elemento(A.hijoDrcho(n)) << endl;
      imprimirDescendientes(A.hijoDrcho(n), A);
   }
}

template <typename T>
void imprimirAbin (ostream& os, const Abin<T>& A, const T& fin)
{
   if (!A.arbolVacio())
   {
      os << fin << endl
         << A.elemento(A.raiz()) << ' ';
      imprimirDescendientes(os, A.raiz(), A, fin);
      os << endl;
   }
}

template <typename T>
void imprimirDescendientes (ostream& os, typename Abin<T>::nodo n, const Abin<T>& A, const T& fin)
{
   if (A.hijoIzqdo(n) != Abin<T>::NODO_NULO)
   {
      os << A.elemento(A.hijoIzqdo(n)) << ' ';
      imprimirDescendientes(os, A.hijoIzqdo(n), A, fin);
   }
   else
      os << fin << ' ';
   if (A.hijoDrcho(n) != Abin<T>::NODO_NULO)
   {
      os << A.elemento(A.hijoDrcho(n)) << ' ';
      imprimirDescendientes(os, A.hijoDrcho(n), A, fin);
   }
   else
      os << fin << ' ';
}

#endif   // ABIN_E_S_H
