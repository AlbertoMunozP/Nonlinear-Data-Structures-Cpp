#include <iostream>
#include "abin.h"
#include "abin_E-S.h"

template <typename T>
bool esHoja(const typename Abin<T>::nodo& n,const Abin<T>& A) {
    if(n==Abin<T>::NODO_NULO)
        return false;
    else{
        return (A.hijoIzqdo(n) == Abin<T>::NODO_NULO) && (A.hijoDrcho(n) == Abin<T>::NODO_NULO);
    }
}

template <typename T>
void podar(typename Abin<T>::nodo n, T x, Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(n) == x) {
            poda_rec(n,A);
            if(n==A.raiz())
                A.eliminarRaiz();
            else{
                if(n == A.hijoIzqdo(A.padre(n)))
                    A.eliminarHijoIzqdo(A.padre(n));
                else
                    A.eliminarHijoDrcho(A.padre(n));
            }
        }
        else{
            podar(A.hijoIzqdo(n),x,A);
            podar(A.hijoDrcho(n),x,A);
        }
    }
}

template <typename T>
void poda_rec(const typename Abin<T>::nodo& n, Abin<T>& A){
    if(A.hijoIzqdo(n)  != Abin<T>::NODO_NULO){
        if(!esHoja(A.hijoIzqdo(n),A))
            poda_rec(A.hijoIzqdo(n),A);
        else
            A.eliminarHijoIzqdo(n);
    }
    if(A.hijoIzqdo(n)  != Abin<T>::NODO_NULO){
        if(!esHoja(A.hijoDrcho(n),A))
            poda_rec(A.hijoDrcho(n),A);
        else
            A.eliminarHijoDrcho(n);
    }
}

template <typename T>
void destruir(T x, Abin<T>& A){
    busquedaNodo(A.raiz(),x,A);
}

/* Se lleva nodo hsta las hojas, en caso de que tenga un
unico hijo intercambio con el, en cao de que tenga dos  intercambio
con el menor de ellos 
Tengo que implementar:
-Busqueda
-Hundir
-ELiminar
*/

/* Segundo intento*/

template<typename T>
void eliminar(typename Abin<T>::nodo n, Abin<T>& A){
    if(n == A.raiz())
        A.eliminarRaiz();
    else{
        typename Abin<T>::nodo padre = A.padre(n);
        if(n == A.hijoIzqdo(padre))
            A.eliminarHijoIzqdo(padre);
        else
            A.eliminarHijoDrcho(padre);
    }
}

template<typename T>
void hundir(typename Abin<T>::nodo n, Abin<T>& A){
    typename Abin<T>::nodo hizq = A.hijoIzqdo(n);
    typename Abin<T>::nodo hder = A.hijoDrcho(n);
    T aux = A.elemento(n);
    if(hizq==Abin<T>::NODO_NULO && hder==Abin<T>::NODO_NULO)
        eliminar(n,A);
    else{
        if(hizq == Abin<T>::NODO_NULO){
            A.elemento(n) = A.elemento(hder);
            A.elemento(hder) = aux;
            hundir(hder,A);
        }
        else{
            if(hder == Abin<T>::NODO_NULO) {
                A.elemento(n) = A.elemento(hizq);
                A.elemento(hizq) = aux;
                hundir(hizq,A);
            }
            else{
                if(A.elemento(hizq)<A.elemento(hder)){
                    A.elemento(n) = A.elemento(hizq);
                    A.elemento(hizq) = aux;
                    hundir(hizq,A);
                }
                else{
                    A.elemento(n) = A.elemento(hder);
                    A.elemento(hder) = aux;
                    hundir(hder,A);
                }
            }
        }
    }
}

template<typename T>
void busquedaNodo(typename Abin<T>::nodo n, T objetivo, Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(n) == objetivo)
            hundir(n,A);
        else{
            busquedaNodo(A.hijoIzqdo(n),objetivo,A);
            busquedaNodo(A.hijoDrcho(n),objetivo,A);
        }
    }
}

int main(){
    Abin<int> A; 
    rellenarAbin(A,0);
    cout<< "Arbol previo a la eliminación del nodo: "<<endl<<endl;
    imprimirAbin(A);
    int x;
    cout<<"Elemento a eliminar: "; cin>>x;
    destruir(x,A);
    cout<<endl<<endl<<"Arbol sin el nodo introducido";
    imprimirAbin(A);
    return 0;
}