#include <iostream> 
#include <fstream> 
#include "agen_E-S.h" 
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

template<typename T>
void buscarRec(typename Agen<T>::nodo n, Agen<T> A, T elto, typename Agen<T>::nodo& nodobuscado){
	if(n!=Agen<T>::NODO_NULO){
		if(A.elemento(n) == elto)
			nodobuscado = n;
		else{
			typename Agen<T>::nodo aux = A.hijoIzqdo(n);
			while(aux!=Agen<T>::NODO_NULO){
				buscarRec(aux,A,elto,nodobuscado);
				aux = A.hermDrcho(aux);
			}
		}
	}
}


template<typename T>
void podarRec(typename Agen<T>::nodo n, Agen<T>& A){
	while( A.hijoIzqdo(n)!=Agen<T>::NODO_NULO){
			podarRec( A.hijoIzqdo(n),A);
			A.eliminarHijoIzqdo(n);
	}

}

template<typename T>
void podarAgen(Agen<T>& A, T elto){
	typename Agen<T>::nodo eliminar = Agen<T>::NODO_NULO;
	buscarRec(A.raiz(),A,elto,eliminar);
	if(eliminar!=Agen<T>::NODO_NULO){
		podarRec(eliminar,A);
		typename Agen<T>::nodo aux = A.hijoIzqdo(A.padre(eliminar));
		if(A.elemento(aux) == elto)
			A.eliminarHijoIzqdo(A.padre(aux));
		else{
			while(A.elemento(A.hermDrcho(aux))!=elto)
				aux = A.hermDrcho(aux);
			A.eliminarHermDrcho(aux);
		}
	}
	else {
		cout << endl << "No se ha encontrado el nodo" << endl;
	}
}


int main () 
{ 
    Agen<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    rellenarAgen(A, fin); 
    cout<< "\nMostramos el arbol\n"; 
    imprimirAgen(A);  
    tElto x;
    cout<<"Introduce elemento a partir del que podar: "; cin >> x;
    podarAgen(A,x);
    cout<<endl<<"ARBOL TRAS LA PODA"<<endl<<endl;
    imprimirAgen(A);
    return 0;
} 
