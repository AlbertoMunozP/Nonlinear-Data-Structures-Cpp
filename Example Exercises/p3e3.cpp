#include <iostream> 
#include <fstream> 
#include "agen_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

template <typename T>
int altura_rec(typename Agen<T>::nodo n, const Agen<T>& A){
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else{
        int alturaMax = -1;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
            alturaMax = max(alturaMax, altura_rec(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return 1+alturaMax;
    }
}

template <typename T>
int ramaMasCorta(typename Agen<T>::nodo n, const Agen<T>& A){
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else{
        int minimo = 1e6;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
            minimo = min(minimo, ramaMasCorta(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return 1+minimo;
    }
}

template <typename T>
int desequilibrio(const Agen<T>& A){
    return altura_rec(A.raiz(),A)-ramaMasCorta(A.raiz(),A);       
}



int main () 
{ 
    Agen<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    rellenarAgen(A, fin); 
    cout<< "\nMostramos el arbol\n"; 
    imprimirAgen(A);  
    cout<<"El desequilibrio de este arbol es "<<desequilibrio(A);
    return 0;
} 
    