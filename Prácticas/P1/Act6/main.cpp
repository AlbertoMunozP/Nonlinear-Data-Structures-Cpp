#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

template <typename T>
int desequilibrio(const Abin<T>& A){
    return desequilibrio_rec(A.raiz(),A);
}
template <typename T>
int desequilibrio_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        int des = (unsigned int) A.altura(A.hijoIzqdo(n))-A.altura(A.hijoDrcho(n));
        return max(des,max(desequilibrio_rec(A.hijoIzqdo(n),A),desequilibrio_rec(A.hijoDrcho(n),A)));
    }
         
}

int main () 
{ 
    Abin<tElto> A; 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);  
    cout<<endl<<"El desequilibrio de este arbol es "<<desequilibrio(A)<<endl;   
    return 0;
} 
