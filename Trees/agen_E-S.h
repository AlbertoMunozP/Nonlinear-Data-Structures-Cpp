#ifndef AGEN_E_S_H
#define AGEN_E_S_H

#include <cassert>
#include <iostream>
#include "Agen.h"
#include <fstream>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;

template <typename T>
void rellenarAgen(Agen<T>& A, const T& fin)
{
   T e;

   assert(A.raiz() == Agen<T>::NODO_NULO);
   cout << "Ra�z (Fin = " << fin << "): "; cin >> e;
   if (e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(typename Agen<T>::nodo n, Agen<T>& A, const T& fin)
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Agen<T>::NODO_NULO);
   cout << "Hijo izqdo. de " << A.elemento(n)
        << " (Fin = " << fin << "): ";
   cin >> ehi;
   if (ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(A.hijoIzqdo(n), A, fin);
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      cout << "Hermano drcho. de " << A.elemento(hijo)
           << " (Fin = " << fin << "): ";
      cin >> ehd;
      while (ehd != fin) {
         A.insertarHermDrcho(hijo, ehd);
         rellenarDescendientes(A.hermDrcho(hijo), A, fin);
         hijo = A.hermDrcho(hijo);
         cout << "Hermano drcho. de " << A.elemento(hijo)
              << " (Fin = " << fin << "): ";
         cin >> ehd;
      }
   }
}

template <typename T>
void rellenarAgen(istream& is, Agen<T>& A)
{
   T e, fin;

   assert(A.arbolVacio());
   if (is >> fin && is >> e && e != fin) {
      A.insertarRaiz(e);
      rellenarDescendientes(is, A.raiz(), A, fin);
   }
}

template <typename T>
void rellenarDescendientes(istream& is, typename Agen<T>::nodo n, Agen<T>& A, const T& fin)
{
   T ehi, ehd;

   assert(A.hijoIzqdo(n) == Agen<T>::NODO_NULO);
   if (is >> ehi && ehi != fin) {
      A.insertarHijoIzqdo(n, ehi);
      rellenarDescendientes(is, A.hijoIzqdo(n), A, fin);
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      while (is >> ehd && ehd != fin) {
         A.insertarHermDrcho(hijo, ehd);
         rellenarDescendientes(is,A.hermDrcho(hijo), A, fin);
         hijo = A.hermDrcho(hijo);
      }
   }
}

template <typename T>
void imprimirAgen(const Agen<T>& A)
{
   if (A.raiz() != Agen<T>::NODO_NULO)
   {
      cout << "Raiz del arbol: "
           << A.elemento(A.raiz()) << endl;
      imprimirDescendientes(A.raiz(), A);
   }
   else
      cout << "Arbol vacio\n";
}

template <typename T>
void imprimirDescendientes(typename Agen<T>::nodo n, const Agen<T>& A)
{
   if (A.hijoIzqdo(n) != Agen<T>::NODO_NULO)
   {
      typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
      cout << "Hijo izqdo de " << A.elemento(n) << ": "
           << A.elemento(hijo) << endl;
      while (hijo != Agen<T>::NODO_NULO) {
         imprimirDescendientes(hijo, A);
         if (A.hermDrcho(hijo) != Agen<T>::NODO_NULO)
            cout << "Hermano derecho de " << A.elemento(hijo) << ": "
                 << A.elemento(A.hermDrcho(hijo)) << endl;
         hijo = A.hermDrcho(hijo);
      }
   }
}

template <typename T>
void imprimirAgen(ostream& os, const Agen<T>& A, const T& fin)
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
void imprimirDescendientes(ostream& os, typename Agen<T>::nodo n, const Agen<T>& A, const T& fin){

   typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
   while (hijo != Agen<T>::NODO_NULO) {
      os << A.elemento(hijo) << ' ';
      imprimirDescendientes(os, hijo, A, fin);
      hijo = A.hermDrcho(hijo);
   }
   os << fin << ' ';
}

#endif   
