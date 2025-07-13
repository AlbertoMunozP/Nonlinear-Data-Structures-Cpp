#include "ABB_E-S.h"
#include "TADArbolDinamicoRecursivo.h"
#include<vector>
#include <algorithm>

using namespace std; 
typedef int tElto; 
const tElto fin = 0; 

void podar(int x, Abb<tElto>& A){
    if(!A.buscar(x).vacio())
        A.buscar(x).~Abb();

}

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
    sort(v.begin(),v.end());    // El vector se ordena

    equilibrarRec(v,B);
    A = B;
}



void InterseccionRec1(const Abb<int> A, const Abb<int> B, Abb<int>& Resultado)//Rellena el arbol resultado con A
{
    if(!A.vacio() && !B.vacio())
    {
        if(!B.buscar(A.elemento()).vacio())
            Resultado.insertar(A.elemento());
        InterseccionRec1(A.izqdo(),B,Resultado);
        InterseccionRec1(A.drcho(),B,Resultado);
    }
}


Abb<int> Interseccion(Abb<int> A, Abb<int> B)
{
    Abb<int> Resultado;
    InterseccionRec1(A,B,Resultado);
    return Resultado;
}

void UnionRec1(const Abb<int> A,Abb<int>& Resultado)//Rellena el arbol resultado con A
{
    if(!A.vacio())
    {
        Resultado.insertar(A.elemento());
        UnionRec1(A.izqdo(),Resultado);
        UnionRec1(A.drcho(),Resultado);
    }
}

void UnionRec2(const Abb<int> B,Abb<int>& Resultado)
{
    if(!B.vacio())
    {
        if((Resultado.buscar(B.elemento())).vacio())
           Resultado.insertar(B.elemento());
        UnionRec2(B.izqdo(),Resultado);
        UnionRec2(B.drcho(),Resultado);               
    }

}

Abb<int> Union(Abb<int> A, Abb<int> B)
{
    Abb<int> Resultado;
    UnionRec1(A,Resultado);
    UnionRec2(B,Resultado);

    return Resultado;
}

void rombo_rec(Abb<int>& A, const Abb<int>& B){
    if(!B.vacio()){
        if(!A.buscar(B.elemento()).vacio())
            A.eliminar(B.elemento());
        rombo_rec(A,B.izqdo()); 
        rombo_rec(A,B.drcho());
    }
}
Abb<int> Rombo(Abb<int> A, Abb<int> B)
{
    Abb<int> Resultado,aux;
    Resultado = Union(A,B);
    aux = Interseccion(A,B);
    rombo_rec(Resultado,aux);
    return Resultado;
}

int main () 
{ 
    Abb<tElto> A,B,U; 
    cout << "\nRellenamos el arbol A\n"; 
    LeerAbb(A); 
    cout<< "\nMostramos el arbol A\n"; 
    MostrarAbb(A);
    cout << "\n\nRellenamos el arbol B\n"; 
    LeerAbb(B); 
    cout<< "\n\nMostramos el arbol B\n"; 
    MostrarAbb(B);
    U = Rombo(A,B);
    equilibrarAbb(U);
    cout<< "\n\nMostramos el arbol union\n"; 
    MostrarAbb(U);
    return 0;
} 
