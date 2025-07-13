#include "ABB_E-S.h"
#include "TADArbolDinamicoRecursivo.h"
#include<vector>
#include <algorithm>

using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

// Juanfran la llama inorden()
void llenar_v(vector<int>& v,const Abb<int>& A)
{
    if(!A.vacio())
    {
        llenar_v(v,A.izqdo());
        v.push_back(A.elemento());
        llenar_v(v,A.drcho());
    }
}

void equilibrarRec(vector<int>& v,Abb<int>& B)
{
    if(v.size() == 1)   //Si s�lo queda un elemento en el vector lo insertamos directamente en el �rbol.
        B.insertar(v.front());
    else{
        if(v.size() != 0){

            vector<int> vIzq, vDer;
            int mediana = v.size()/2;
            B.insertar(v[mediana]);

            for(int i=0; i < mediana; i++)
                vIzq.push_back(v[i]);

            for(int i=mediana+1; i < v.size(); i++)
                vDer.push_back(v[i]);

            equilibrarRec(vIzq,B);
            equilibrarRec(vDer,B);
        }
    }
}

void equilibrarAbb(Abb<int>& A) {
	vector<int> v;
    Abb<int> B;

    llenar_v(v,A);  // El vector se rellena del arbol

    equilibrarRec(v,B);
    A = B;
}


// Forma de hacer segun Juanfran
template<typename T>
void inorden(vector<T>& v,const Abb<T>& A)
{
    if(!A.vacio())
    {
        inorden(v,A.izqdo());
        v.push_back(A.elemento());
        inorden(v,A.drcho());
    }
}

template<typename T>
void equilibrarJF_rec(Abb<T>& A, const vector<T>& eltos, int ini, int fin)
{
    int mitad = (fin + ini)/2;
    if(fin>=ini){
        A.insertar(eltos[mitad]);
        equilibrarJF_rec(A,eltos,ini,mitad-1);
        equilibrarJF_rec(A,eltos,mitad+1,fin);
    }
}

template<typename T>
void equilibrarJF(Abb<T>& A)
{
    vector<T> eltos;
    inorden(v,A);
    Abb<T> aux;
    equilibrarJF_rec(aux,eltos,0,eltos.size()-1);
    A = aux;
}

int main () 
{ 
    Abb<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    LeerAbb(A); 
    cout<< "\nMostramos el arbol\n"; 
    MostrarAbb(A);
    equilibrarAbb(A);
    MostrarAbb(A);
    return 0;
} 
