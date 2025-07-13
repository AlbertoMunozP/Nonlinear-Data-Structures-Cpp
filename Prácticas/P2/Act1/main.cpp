#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

template <typename T>
bool similares(const Abin<T>& A, const Abin<T>& B){
    return similares_rec(A.raiz(),B.raiz(),A,B);
}
template <typename T>
bool similares_rec(typename Abin<T>::nodo n1, typename Abin<T>::nodo n2, const Abin<T>& A, const Abin<T>& B){
    if(n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;
    else{
        if(n1 == Abin<T>::NODO_NULO || n2 == Abin<T>::NODO_NULO) // No se dara el caso de que sean nulos los dos ya que lo comprobamos en el caso base!!!
            return false;
        else 
            return true && similares_rec(A.hijoIzqdo(n1), B.hijoIzqdo(n2),A, B) && similares_rec(A.hijoDrcho(n1),B.hijoDrcho(n2),A,B);
    }       
}

int main () 
{ 
    Abin<tElto> A,B; 
    cout << "Rellenamos el arbol binario A\n"; 
    rellenarAbin(A, fin);
    cout << "Rellenamos el arbol binario B\n"; 
    rellenarAbin(B, fin);  
    cout<<"Mostramos el arbol A\n";
    imprimirAbin(A);
    cout<<"Mostramos el arbol B\n";
    imprimirAbin(B);
    if(similares(A,B))  
        cout<<"Arboles similares"<<endl;   
    else
        cout<<"Arboles no similares"<<endl; 
    return 0;
} 
