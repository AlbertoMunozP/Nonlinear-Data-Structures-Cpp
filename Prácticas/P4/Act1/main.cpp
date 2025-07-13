#include "ABB_E-S.h"
#include "TADArbolDinamicoRecursivo.h"
using namespace std; 
typedef int tElto; 
const tElto fin = 0; 


int main () 
{ 
    Abb<tElto> A; 
    cout << "Rellenamos el arbol\n"; 
    LeerAbb(A); 
    cout<< "\nMostramos el arbol\n"; 
    MostrarAbb(A);
    int x;
    cout<<"Introduce el elemento a partir del cual podar: "; cin>>x;
    A.poda(x);
    MostrarAbb(A);
    return 0;
} 
