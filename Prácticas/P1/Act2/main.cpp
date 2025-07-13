#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 


//Ejercicio 2
template<typename T>
int altura(const Abin<T>& A){
    int a = altura_rec(A.raiz(),A);
    if (a == -1)
        return 0; // Arbol vacio tiene altura 0
    else
        return a;
}

template <typename T>
int altura_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return -1;
    else
        return 1+max(altura_rec(A.hijoIzqdo(n),A),altura_rec(A.hijoDrcho(n),A));
}


int main () 
{ 
    Abin<tElto> A; 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);  
    cout<<endl<<"La altura de este arbol es "<<altura(A)<<endl;
} 
