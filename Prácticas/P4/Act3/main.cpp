#include "ABB_E-S.h"
#include "TADArbolDinamicoRecursivo.h"
#include<vector>
#include <algorithm>

using namespace std; 
typedef int tElto; 
const tElto fin = 0; 



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



void UnionRec1(const Abb<int>& A,Abb<int>& Resultado)//Rellena el arbol resultado con A
{
    if(!A.vacio())
    {
        Resultado.insertar(A.elemento());
        UnionRec1(A.izqdo(),Resultado);
        UnionRec1(A.drcho(),Resultado);
    }
}

void UnionRec2(const Abb<int>& B,Abb<int>& Resultado)
{
    if(!B.vacio())
    {
        if((Resultado.buscar(B.elemento())).vacio())
           Resultado.insertar(B.elemento());
        UnionRec2(B.izqdo(),Resultado);
        UnionRec2(B.drcho(),Resultado);               
    }

}

Abb<int> Union(const Abb<int>& A, const Abb<int>& B)
{
    Abb<int> Resultado;
    UnionRec1(A,Resultado);
    UnionRec2(B,Resultado);

    return Resultado;
}

/* Segun Juanfran
Seria conveniente hacer un TAD Conjunto con un Abb
en su private ya que nos facilitaría trabajar para
haver uniones por ejemplo:
Conjunto<T> A,B,C;
C = A + B;
si sobrecargamos ese operador + dentro de la clase
podriamos realizar esa operacion para unir o lo que
queramos. Por ello Juanfran plantea los ultimos tres
ejercicios como un mismo TAD
*/
template <typename T>
class Conjunto{
    public:
        Conjunto(){}
        Conjunto(Abb<T> A) : arbol_(A){fillInorden(A,eltos_);}
        void add(T elto);
        inline bool pertenece(T elto) const;
        void mostrar();
        const Abb<T>& arbol();
        const vector<T>& elementos() const;
        Conjunto<T> operator| (const Conjunto<T>& c);
        Conjunto<T> operator& (const Conjunto<T>& c);
        Conjunto<T> operator- (const Conjunto<T>& c);
        Conjunto<T> operator= (const Conjunto<T>& c);        
    private:
        Abb<T> arbol_;
        vector<T> eltos_;
};

template<typename T>
Conjunto<T> Conjunto<T>::operator| (const Conjunto<T>& B){ //union
    Conjunto<T> out;
    for(auto elto: eltos_)
        out.arbol_.insertar(elto);
    for(auto elto: B.eltos_)
        out.arbol_.insertar(elto);
    fillInorden(out.arbol_, out.eltos_);
    equilibrar(out.arbol_);
    return out;
}

template<typename T>
Conjunto<T> Conjunto<T>::operator& (const Conjunto<T>& B){ //inserccion
    Conjunto<T> out;
    for(auto elto: eltos_){
        if(B.pertenece(elto))
            out.arbol_.insertar(elto);
    }
       
    fillInorden(out.arbol_, out.eltos_);
    equilibrar(out.arbol_);
    return out;
}

template<typename T>
Conjunto<T> Conjunto<T>::operator- (const Conjunto<T>& B){ //diferencia simetrica
    Conjunto<T> out;
    for(auto elto: eltos_){
        if(!B.pertenece(elto))
            out.arbol_.insertar(elto);
    }

    for(auto elto: B.eltos_){
        if(!pertenece(elto))
            out.arbol_.insertar(elto);
    }
       
    fillInorden(out.arbol_, out.eltos_);
    equilibrar(out.arbol_);
    return out;
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
    U = Union(A,B);
    equilibrarAbb(U);
    cout<< "\n\nMostramos el arbol union\n"; 
    MostrarAbb(U);
    return 0;
} 
