#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

/*
  Como concepto es la altura lo que yo estoy tomando como la maxima profundidad de un nodo
  en un arbol, asi que debería pasarle la altura del arbol a pseudocompleto_rec, aunque
  esta bien comolo tengo, es mas algo de conceptos segun juanfran ya que la altura del arbol
  es lo mismo que la maxima profundidad que va a tener un nodo en el arbol
*/

template <typename T>
int profArbol(typename Abin<T>::nodo n, const Abin<T>& A){
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else{
        int prof = A.profundidad(n);
        return max(prof,max(profArbol(A.hijoIzqdo(n),A),profArbol(A.hijoDrcho(n),A)));
    }
}

template <typename T>
bool pseudocompleto(const Abin<T>& A){
    int profundidadArbol = profArbol(A.raiz(),A);
    return pseudocompleto_rec(A.raiz(),profundidadArbol,A);
}
template <typename T>
bool pseudocompleto_rec(typename Abin<T>::nodo n, int p, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO )
        return true;
    else{
        if(A.profundidad(n) == p-1){    // AlturaAbin - A.profundidad(nodo) == 1; que la altura la pasamos como parametro
        // Mas sencillos hacer un numHijos(n) y un unico if-else o return numhijos(n)!=1 directamente mejor
            if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
              return true;
            else{
                if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
                    return true;
                else
                    return false; // Solo tiene 1 hijo
        }
        }
        else
            return pseudocompleto_rec(A.hijoIzqdo(n),p,A) && pseudocompleto_rec(A.hijoDrcho(n),p,A);
    }
         
}

int main () 
{ 
    Abin<tElto> A; 
    cout << "Rellenamos el arbol binario\n"; 
    rellenarAbin(A, fin); 
    cout<<"Mostramos el arbol\n";
    imprimirAbin(A);
    if(pseudocompleto(A))  
        cout<<"Arbol pseudocompleto"<<endl;   
    else
        cout<<"Arbol no pseudocompleto"<<endl; 
    return 0;
} 
