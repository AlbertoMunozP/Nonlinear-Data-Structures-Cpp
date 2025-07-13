#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 


//Ejercicio 1
template<typename T>
int numNodos(const Abin<T>& A){
    return numNodos_rec(A.raiz(),A);
}
/*
    Siempre el nodo lo pasamos como primer parámetro
    porque es el que va a ir cambiando. Tambien importante´
    poner en mayúscula el nombre del arbol que pasamos
    (la estructura contenedora) y en minúscula el resto
    como pueden ser enteros, nodos, etc. 
*/

template <typename T>
int numNodos_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1+numNodos_rec(A.hijoIzqdo(n),A)+numNodos_rec(A.hijoDrcho(n),A);
}


int main () 
{ 
    Abin<tElto> A; 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);  
    cout<<endl<<"El numero de nodos de este arbol es "<<numNodos(A)<<endl;
} 
