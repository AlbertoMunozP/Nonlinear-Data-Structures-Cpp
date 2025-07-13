#include <iostream> 
#include <fstream> 
#include "agen_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

template <typename T>
int numHermanos(typename Agen<T>::nodo n, const Agen<T>& A){
    int contador = 0;
    while(n!=Agen<T>::NODO_NULO){
        contador++;
        n = A.hermDrcho(n);
    }
    return contador;
}

template <typename T>
int grado(const Agen<T>& A){
    return grado_rec(A.raiz(),A);
}

template <typename T>
int grado_rec(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else{
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        int cont = numHermanos(hijo, A);
        while(hijo!=Agen<T>::NODO_NULO){
            cont = max(cont,grado_rec(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

/* Según Juanfran en clase:
template <typename T>
int grado(const Agen<T>& A){
    int g = 0;
    grado_rec(A.raiz(),A,g);
    return g;
}

template <typename T>
void grado_rec(typename Agen<T>::nodo n, const Agen<T>& A, int &gradoMax){
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else{
        int grado = max(gradoMax,nHijos(n,A));
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
            grado_rec(hijo,A,grado);
            hijo = A.hermDrcho(hijo);
        }
    }
}

Dice que como entero también es correcto como cada uno
lo considere más sencillo
*/

int main () 
{ 
    Agen<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    rellenarAgen(A, fin); 
    
    cout<< "\nMostramos el arbol\n"; 
    imprimirAgen(A);  
    cout<<"El grado de este arbol es "<<grado(A);
    return 0;
} 
