#include <iostream> 
#include <fstream> 
#include "agen_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 


template <typename T>
int profundidad(typename Agen<T>::nodo n, const Agen<T>& A){
    if(A.padre(n) == Agen<T>::NODO_NULO)
        return 0;
    else
        return 1+profundidad(A.padre(n),A);
        
}

int main () 
{ 
    Agen<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    rellenarAgen(A, fin); 
    cout<< "\nMostramos el arbol\n"; 
    imprimirAgen(A);  
    typename Agen<tElto>::nodo n = A.hermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())));
    cout<<"La profundidad de este nodo es "<<profundidad(n,A)<<" y su valor es "<<A.elemento(n);
    return 0;
} 
