#include "ABB_E-S.h"
#include "TADArbolDinamicoRecursivo.h"
#include<vector>
#include <algorithm>

using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

// Mi forma de equilibrar un ABB

template<typename T>
void llenar_v(vector<T>& v,const Abb<T>& A)
{
    if(!A.vacio())
    {
        llenar_v(v,A.izqdo());
        v.push_back(A.elemento());
        llenar_v(v,A.drcho());
    }
}
template<typename T>
void equilibrarRec(vector<T>& v,Abb<T>& B)
{
    if(v.size() == 1)   
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

    llenar_v(v,A);  

    equilibrarRec(v,B);
    A = B;
}

// Poda como función externa

template<typename T>
void podaAbb(const T& x, Abb<T>& A){
    if(!A.buscar(x).vacio()) {  // En caso de que el elemento no este en el arbol, no hacemos nada
        if(!A.buscar(x).izqdo().vacio()) {
            T izq = A.buscar(x).izqdo().elemento();
            podaAbb(izq,A);
        }
        if(!A.buscar(x).drcho().vacio()) {
            T der = A.buscar(x).drcho().elemento();
            podaAbb(der,A);
        }
        A.eliminar(x);
    }
}


int main(){
    Abb<int> A;
    LeerAbb(A);
    podaAbb(5,A);
    MostrarAbb(A);
    return 0;
}