#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
using namespace std; 

// Markdown

// Hacer una version con class y dos contructores en cada caso poner el bool
// a true o false
struct OP{
    bool numero;    //True si es hoja
    int n;
    char x;
    OP(bool esn = true, int num = 0, char xx = '+'): numero(esn), n(num), x(xx){}
};

const OP fin(true,0); // Nodo nulo. 


int expresion_rec(typename Abin<OP>::nodo n, const Abin<OP>& A){
    if(n != Abin<OP>::NODO_NULO){
        if(A.elemento(n).numero)
            return A.elemento(n).n;
        else{
            switch(A.elemento(n).x){
                case '+': return (expresion_rec(A.hijoIzqdo(n),A) + expresion_rec(A.hijoDrcho(n),A));
                    break;
                case '-': return expresion_rec(A.hijoIzqdo(n),A)-expresion_rec(A.hijoDrcho(n),A);
                    break;
                case '*': return expresion_rec(A.hijoIzqdo(n),A) * expresion_rec(A.hijoDrcho(n),A);
                    break;
                case '/': return expresion_rec(A.hijoIzqdo(n),A)/expresion_rec(A.hijoDrcho(n),A);
                    break;
            }
        }
    }   
}

int expresion(const Abin<OP>& A){
    if (A.raiz() == Abin<OP>::NODO_NULO)
        return 0;
    return expresion_rec(A.raiz(),A);
}

int main () 
{ 
    Abin<OP> A; 
    cout << "Rellenamos el arbol binario A\n"; 
    A.insertarRaiz(OP(false,1,'+'));
    A.insertarHijoDrcho(A.raiz(),OP(true,1));
    A.insertarHijoIzqdo(A.raiz(),OP(false,1,'/'));
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()),OP(true,4,'+'));
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()),OP(true,4,'+'));
    cout << "El restultado es "<< expresion(A);
    return 0;
} 
