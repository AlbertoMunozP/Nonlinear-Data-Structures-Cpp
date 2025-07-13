#include <iostream> 
#include <fstream> 
#include "TADarbolbinarioVectorial.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

int main () 
{ 
    Abin<tElto> A(10);  //Le pasamos numero maximo de nodos 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);
    // Dentro de las llamadas especiicamos el nodo a calcular
    cout<<"La profundidad de este nodo es "<<A.profundidad_rec(A.raiz())<< " y su altura es "<<A.altura(A.raiz());   
    return 0;
} 
