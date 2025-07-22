#include<iostream>
#include "Agen.h"
#include "agen_E-S.h"
typedef int T;

using namespace std;

template<typename T>
int numHijos(typename Agen<T>::nodo n,const Agen<T>& A){
    int num=0;
    if(A.hijoIzqdo(n)!=Agen<T>::NODO_NULO){
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
            num++;
            hijo = A.hermDrcho(hijo);
        }
    }
    return num;
}

template<typename T>
bool esTerciarioRec(typename Agen<T>::nodo n,const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return true;
    else{
        if(numHijos(n,A)!=0 && numHijos(n,A)!=3)
            return false;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        bool t = true;
        while(hijo!=Agen<T>::NODO_NULO){
            t = (t && esTerciarioRec(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return t;
    }
}


template<typename T>
bool esTerciarioRecv2(typename Agen<T>::nodo n,const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return true;
    else{
        int nHijos = numHijos(n,A);
        bool flag = (nHijos==0 || nHijos==3);
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO && flag){
            flag &= esTerciarioRecv2(hijo,A);
            hijo = A.hermDrcho(hijo);
        }
        return flag;
    }
}


template<typename T>
bool esTerciario(const Agen<T>& A){
    return esTerciarioRecv2(A.raiz(),A);
}

int main(){
    Agen<T> A;
    rellenarAgen(A,0);
    if(esTerciario(A))
        cout<<endl<<"El arbol es terciario";
    else
        cout<<endl<<"El arbol no es terciario";

}
