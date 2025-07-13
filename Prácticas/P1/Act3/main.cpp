#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 


template <typename T>
int profNodoAbin(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO) // Tambien valdria: if n ==A.raiz() return 0 como caso base
        return -1;
    else
        return 1+profNodoAbin(A.padre(n),A);
}


int main () 
{ 
    Abin<tElto> A; 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);  
    //Pasamos a profundidad rec el nodo que queremos conocere su profundidad
    cout<<endl<<"La profundidad de este nodo es "<<profNodoAbin(A.raiz(),A)<<endl;   
    return 0;
} 
