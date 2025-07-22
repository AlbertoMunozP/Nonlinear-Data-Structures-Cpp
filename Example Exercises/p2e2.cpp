#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

template <typename T>
void reflejado(const Abin<T>& A, Abin<T>& B){
    if (A.raiz() != Abin<T>::NODO_NULO){
        B.insertarRaiz(A.elemento(A.raiz()));
        reflejado_rec(A.raiz(),B.raiz(),A,B); 
    }
        
}
template <typename T>
void reflejado_rec(typename Abin<T>::nodo n1, typename Abin<T>::nodo n2, const Abin<T>& A, Abin<T>& B){
    if(n1 != Abin<T>::NODO_NULO){   
        if(A.hijoDrcho(n1)!= Abin<T>::NODO_NULO){
            B.insertarHijoIzqdo(n2,A.elemento(A.hijoDrcho(n1)));
            reflejado_rec(A.hijoDrcho(n1),B.hijoIzqdo(n2),A,B);
        }
        if(A.hijoIzqdo(n1)!= Abin<T>::NODO_NULO){
            B.insertarHijoDrcho(n2,A.elemento(A.hijoIzqdo(n1)));
            reflejado_rec(A.hijoIzqdo(n1),B.hijoDrcho(n2),A,B);
        }
    }   
}

int main () 
{ 
    Abin<tElto> A,B; 
    cout << "Rellenamos el arbol binario A\n"; 
    rellenarAbin(A, fin);
    
    cout<<"Mostramos el arbol A\n";
    imprimirAbin(A);
    
    reflejado(A,B);

    cout<<"Mostramos el arbol reflejado B\n";
    imprimirAbin(B);
    return 0;
} 
