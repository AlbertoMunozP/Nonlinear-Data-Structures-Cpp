#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

int main () 
{ 
    Abin<tElto> A;  
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);
    // Dentro de las llamadas especificamos el nodo a calcular
    cout<<"La profundidad de este nodo es "<<A.profundidad(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))<<" y su altura es "<<A.altura(A.raiz());   
    return 0;
} 
