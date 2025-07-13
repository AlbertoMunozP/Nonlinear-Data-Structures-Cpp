#ifndef Abbes_h
#define Abbes_h

#include<iostream>
#include "TADArbolDinamicoRecursivo.h"

using namespace std;

template <typename T> void LeerAbb(Abb<T>& A);
template <typename T> void MostrarAbb(const Abb<T>& A);

template <typename T> void LeerAbb(Abb<T>& A)
{
	int elto;
	cout<<"Lectura del arbol ABB (fin: '0')"<<endl;
	
	do {
		cout<<"Introduce el elemento a insertar: ";
		cin>>elto;
		if(elto != 0) A.insertar(elto);
	} while(elto != 0);
	
}

template <typename T>
void MostrarAbb(const Abb<T>& A)
{
	cout<<A.elemento()<<endl;
	if(!A.izqdo().vacio())
	{
		cout<<"Hijo izquierdo de "<<A.elemento()<<" : ";
		MostrarAbb(A.izqdo());
	}
	if(!A.drcho().vacio())
	{
		cout<<"Hijo derecho de "<<A.elemento()<<" : ";
		MostrarAbb(A.drcho());
	}
}

#endif
