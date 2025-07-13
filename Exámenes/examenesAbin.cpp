#include <iostream> 
#include <fstream> 
#include <vector>
#include <limits> // Para el examen de esAbb
#include <stack>
#include <algorithm>
#include "abin.h" 
#include "abin_E-S.h" 
#include "Pila.hpp"

using namespace std; 
typedef int tElto; 
const tElto fin = 0; // Nodo nulo. 

/* Contar descendientes PROPIOS de un nodo dado */
template <typename T>
int numDescendientes(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1+numDescendientes(A.hijoIzqdo(n),A)+numDescendientes(A.hijoDrcho(n),A);
}
/* En caso que se nos pidiese los descendientes propios de un nodo, 
es decir, no habría que contar el propio nodo, se tendría 
que hacer una funcion previa que llamase a numDescendientes:
*/
template <typename T>
int numDescendientesP(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return numDescendientes(n,A)-1;
}



/* Nodos verdes: Tener exactamente 3 nietos*/
template <typename T>
int numHijos(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        if(A.hijoIzqdo(n)!=Abin<T>::NODO_NULO && A.hijoDrcho(n)!=Abin<T>::NODO_NULO)
            return 2;
        else
            if(A.hijoIzqdo(n)==Abin<T>::NODO_NULO && A.hijoDrcho(n)==Abin<T>::NODO_NULO)
                return 0;
            else
                return 1;
    }
        
}

template <typename T>
int numNietos(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return numHijos(A.hijoIzqdo(n),A)+numHijos(A.hijoDrcho(n),A);
}

template <typename T>
int tresnietos_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        if(numNietos(n,A) == 3)
            return 1+tresnietos_rec(A.hijoIzqdo(n),A)+tresnietos_rec(A.hijoDrcho(n),A);
        else
            return 0+tresnietos_rec(A.hijoIzqdo(n),A)+tresnietos_rec(A.hijoDrcho(n),A);
    }
}

template <typename T>
int tresnietos(const Abin<T>& A){
    return tresnietos_rec(A.raiz(),A);
}

/* Nodos verdes: Tener el doble de nietos que de biniestos (>0)*/
template <typename T>
int numBisnietos(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else
        return numNietos(A.hijoIzqdo(n),A)+numNietos(A.hijoDrcho(n),A);
}

template <typename T>
int dobleNB(const Abin<T>& A){
    return dobleNB_rec(A.raiz(),A);
}

template<typename T>
int dobleNB_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        int nietos = numNietos(n,A);
        int bisnietos = numBisnietos(n,A);
        if(nietos == 2*bisnietos && nietos > 0)
            return 1+dobleNB_rec(A.hijoIzqdo(n),A)+dobleNB_rec(A.hijoDrcho(n),A);
        else
            return 0+dobleNB_rec(A.hijoIzqdo(n),A)+dobleNB_rec(A.hijoDrcho(n),A);
    }
}

/* Nodos verdes: Ser nostálgicos.  Definimos un nodo nostálgico como aquel que tiene 
más pasado que futuro, es decir son los nodos que tienen más antecesores propios 
que descendientes propios. */

template <typename T>
int numAntecesoresP(typename Abin<T>::nodo n, const Abin<T>& A){
    if(A.padre(n) == Abin<T>::NODO_NULO)
        return 0;
    else
        return 1+numAntecesoresP(A.padre(n),A);
}

template <typename T>
int nostalgicos_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if (n == Abin<T>::NODO_NULO)
        return 0;
    else {
        if (numAntecesoresP(n,A) > numDescendientesP(n,A))
            return 1+nostalgicos_rec(A.hijoIzqdo(n),A)+nostalgicos_rec(A.hijoDrcho(n),A);
        else
            return 0+nostalgicos_rec(A.hijoIzqdo(n),A)+nostalgicos_rec(A.hijoDrcho(n),A);
    }
}

template <typename T>
int nostalgicos(const Abin<T>& A){
    return nostalgicos_rec(A.raiz(),A);
}

/* Nodos verdes: Nodos reflejos. Dos nodos son reflejos cuando, 
siendo hermanos entre sí, son las raíces de dos árboles 
(subárboles si queréis) que son reflejados entre sí. 
*/

template <typename T>
bool reflejos(typename Abin<T>::nodo n1, typename Abin<T>::nodo n2, const Abin<T>& A){
    if(n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;
    else{
        if(n1 != Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
            return false;
        else{
            if(n1 == Abin<T>::NODO_NULO && n2 != Abin<T>::NODO_NULO)
                return false;
            else
                return true && reflejos(A.hijoIzqdo(n1),A.hijoDrcho(n2),A) && reflejos(A.hijoDrcho(n1),A.hijoIzqdo(n2),A);
        }
    }
}

template <typename T>
int reflejados(const Abin<T>& A){
    return reflejados_rec(A.raiz(),A);
}

template <typename T>
int reflejados_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        typename Abin<T>::nodo hizq = A.hijoIzqdo(n);
        typename Abin<T>::nodo hder = A.hijoDrcho(n);
        if (hizq != Abin<T>::NODO_NULO && hder != Abin<T>::NODO_NULO && reflejos(hizq,hder,A))
            return 2+reflejados_rec(hizq,A)+reflejados_rec(hder,A);
        else
            return 0+reflejados_rec(hizq,A)+reflejados_rec(hder,A);
    }
}

/* Dado un Abin comprobar si dicho arbol es ABB*/
template <typename T>
bool esABB(const Abin<T>& A){
    return esABB_rec(A.raiz(),A,numeric_limits<T>::min(), numeric_limits<T>::max());
}

/* No se comprueba que no haya elementos repetidos debido a que al comprobar la condicion 
   siempre se hace con > o < por lo que en caso de encontrar un elemento repetido dara False */

template <typename T>
bool esABB_rec(typename Abin<T>::nodo n, const Abin<T>& A, T minimo, T maximo){
    if(n == Abin<T>::NODO_NULO)
        return true;
    else{
        typename Abin<T>::nodo hizq = A.hijoIzqdo(n);
        typename Abin<T>::nodo hder = A.hijoDrcho(n);
        if(hizq != Abin<T>::NODO_NULO && hder != Abin<T>::NODO_NULO){
            if(A.elemento(n)>A.elemento(hizq) && A.elemento(hizq)>minimo && A.elemento(hizq)<maximo 
                && A.elemento(n)<A.elemento(hder) && A.elemento(hder)>minimo && A.elemento(hder)<maximo)
                return true && esABB_rec(hizq,A,minimo,A.elemento(n)) && esABB_rec(hder,A,A.elemento(n),maximo);
            else
                return false;
        }
        else{
            if(hizq != Abin<T>::NODO_NULO){
                if(A.elemento(n)>A.elemento(hizq) && A.elemento(hizq)>minimo && A.elemento(hizq)<maximo)
                    return true && esABB_rec(hizq,A,minimo,A.elemento(n));
                else
                    return false;
            }
            else{
                if(hder != Abin<T>::NODO_NULO){
                    if(A.elemento(n)<A.elemento(hder) && A.elemento(hder)>minimo && A.elemento(hder)<maximo)
                        return true && esABB_rec(hder,A,A.elemento(n),maximo);
                    else    
                        return false;
                }
                else
                    return true;
                 
            }
        }
    }
}

/*Dado un árbol A y un valor x, compruebe si dicho valor se encuentra o no en el árbol. Si 
es así, devuelva el camino desde el nodo raíz hasta dicho nodo. Puede suponer que no 
hay ningún elemento repetido en el árbol que recibe como parámetro. */
template <typename T>
vector<typename Abin<T>::nodo> caminoRaiz(const T& x, const Abin<T>& A){
    typedef typename Abin<T>::nodo nodo;
    vector<nodo> camino;
    nodo n = buscarNodo(x,A);

    while(n != Abin<T>::NODO_NULO){
        camino.push_back(n);
        n = A.padre(n);
    }
    return camino;
    /* Devuelve un vector vacio si el elemento no se 
    encuentra en el arbol y el mismo nodo si este se
    encuentra en la raiz */
}

template <typename T>
typename Abin<T>::nodo buscarNodo(const T& x, const Abin<T>& A){
    return busquedaNodo_rec(A.raiz(), x, A);
}

template <typename T>
typename Abin<T>::nodo busquedaNodo_rec(typename Abin<T>::nodo n,const T& x, const Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(n)==x)
            return n;
        else{
            typename Abin<T>::nodo izq = busquedaNodo_rec(A.hijoIzqdo(n), x, A);
            if (izq != Abin<T>::NODO_NULO)
                return izq; // Devolver el nodo encontrado en el subárbol izquierdo si se encuentra
            // Si no se encuentra en el subárbol izquierdo, buscar en el subárbol derecho
            return busquedaNodo_rec(A.hijoDrcho(n), x, A);
        }
    }
    else    
        return Abin<T>::NODO_NULO;

}


/* Pasar un Abin a un vector */
template <typename T>
void rellenar(vector<T>& vec, typename Abin<T>::nodo nodo, const Abin<T>& A) {
    if (nodo != Abin<T>::NODO_NULO){
        vec.insert(vec.end(), A.elemento(nodo));
        rellenar(vec, A.hijoIzqdo(nodo), A) ;
        rellenar(vec, A.hijoDrcho(nodo), A);
    }
}

/* Febrero 2021 
Implementa una función genérica que transforme un árbol 
binario, eliminando los descendientes propios de todos 
aquellos nodos cuyo contenido sea, al mismo tiempo, 
mayor o igual que el de sus ascendientes propios y 
menor o igual que el de sus descendientes propios.

__Nota__: Es absolutamente necesario definir todos los 
tipos de datos que se usen para resolver el problema, 
así cómo los prototipos de las funciones usadas.

Hay dos formas de entender este enunciado como que el nodo
debe ser mayor o igual que las *SUMAS* de los valores de 
sus ascendientes propios y menor o igual de los valores
que el de sus descencientes propios o en caso de que haya
al menos un ascendiente propio mayor o igual y de igual
forma con los descendientes propios.

1º Version:
*/
template <typename T>
T sumaAntecesores(typename Abin<T>::nodo n, const Abin<T>& A){
    T x = T();
    n = A.padre(n);
    while(n!=Abin<T>::NODO_NULO){
        x += A.elemento(n);
        n = A.padre(n);
    }
    return x;
}

template <typename T>
T sumaSucesores(typename Abin<T>::nodo n, const Abin<T>& A){
    return sumaSucesoresP(A.hijoIzqdo(n),A) + sumaSucesoresP(A.hijoDrcho(n),A);
}

template <typename T>
T sumaSucesoresP(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return T();
    else
        return A.elemento(n) + sumaSucesoresP(A.hijoIzqdo(n),A) + sumaSucesoresP(A.hijoDrcho(n),A);
}


template <typename T>
bool condicion(typename Abin<T>::nodo n, const Abin<T>& A){
    if(A.elemento(n)>=sumaAntecesores(n,A) && A.elemento(n)<=sumaSucesores(n,A))
        return true;
    else
        return false;
}

template <typename T>
void podaArbol(Abin<T>& A){
    podaArbol_rec(A.raiz(),A);
}

template <typename T>
void realizarPoda(typename Abin<T>::nodo n, Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        realizarPoda(A.hijoIzqdo(n),A);
        realizarPoda(A.hijoDrcho(n),A);
        if(A.hijoIzqdo(n)!=Abin<T>::NODO_NULO)
            A.eliminarHijoIzqdo(n);
        if(A.hijoDrcho(n)!=Abin<T>::NODO_NULO)
            A.eliminarHijoDrcho(n);
    }
}


template <typename T>
void podaArbol_rec(typename Abin<T>::nodo n, Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        if(condicion(n,A) && n!=A.raiz())
            realizarPoda(n,A);
        else{
            podaArbol_rec(A.hijoIzqdo(n),A);
            podaArbol_rec(A.hijoDrcho(n),A);
        }
    }
}

/* 2ª Versión */
template <typename T>
bool mayorQueAscendientes(typename Abin<T>::nodo n, const Abin<T>& A){
    T x = A.elemento(n);
    n = A.padre(n);     // Miramos solo  ascendientes propios
    bool hay = false;
    while(!hay && n!=Abin<T>::NODO_NULO){
        if(A.elemento(n)<=x)
            hay = true;
        else
            n = A.padre(n);
    }
    return hay;
    /* En realidad haria una primera funcion que llamase esta y caso de ser n
    la raiz no se si devolvería true o false, no viene bien especificado en el enunciado
    segun esta funcion devolvería false*/
}

template <typename T>
bool menorQueDescendientes(T x,typename Abin<T>::nodo n, const Abin<T>& A){
    return menorQueDescendientes_rec(x,A.hijoIzqdo(n),A) && menorQueDescendientes_rec(x,A.hijoDrcho(n),A);
}

template <typename T>
bool menorQueDescendientes_rec(T x,typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return true;
    else{
        if(A.elemento(n)<x)
            return false;
        else
            return true && menorQueDescendientes_rec(x,A.hijoIzqdo(n),A) && menorQueDescendientes_rec(x,A.hijoDrcho(n),A);
    }
}

template <typename T>
bool condicion_dos(typename Abin<T>::nodo n, const Abin<T>& A){
    if(mayorQueAscendientes(n,A) && menorQueDescendientes(A.elemento(n),n,A))
        return true;
    else
        return false;
}

/* PROBAR CONDICION 2 DE ARRIBA!!! */

/* Ejercicio propuesto por juanfran en practicas
Considere un arbol A, en el que puede suponer que no 
hay elementos repetidos. Dado un elemento x, 
devuelve el camino que existe entre la raiz y 
el nodo cuyo elemento es x, si existe.
*/
template <typename T>
typename Abin<T>::nodo buscarElemento(T x, const Abin<T>& A){
    if(A.raiz() == Abin<T>::NODO_NULO)
        return Abin<T>::NODO_NULO;
    else
        return buscarElemento_rec(A.raiz(),x,A);
}

template <typename T>
typename Abin<T>::nodo buscarElemento(typename Abin<T>::nodo n, T x, const Abin<T>& A){
    if(n!= Abin<T>::NODO_NULO){
        if(A.elemento(n) == x)
            return n;
        else{
            buscarElemento(A.hijoIzqdo(n),x,A);
            buscarElemento(A.hijoDrcho(n),x,A);
        }
    }
}

// Se puede usar tambien la pila de la stl #include<stack>


template <typename T>
Pila<typename Abin<T>::nodo> caminoAraiz(T x, const Abin<T>& A){
    typename Abin<T>::nodo n = buscarElemento(x,A);
    Pila<typename Abin<T>::nodo> camino();
    while(n!=Abin<T>::NODO_NULO){
        camino.push(n);
        n = A.padre(n);
    }
    return camino;
}


// Respuesta de Juanfran 
template <typename T>
void busqueda_rec(const typename Abin<T>::nodo& n, T x, const Abin<T>& A, vector<T>& camino){
    if(n!=Abin<T>::NODO_NULO){
        if(A.elemento(n) == x) {
            typename Abin<T>::nodo aux = n;
            stack<T> pila;
            while(A.padre(aux)!=Abin<T>::NODO_NULO){
                pila.push(A.elemento(aux));
                aux = A.padre(aux);
            }
            pila.push(A.elemento(A.raiz()));
            while(!pila.empty()){
                camino.push_back(pila.top());
                pila.pop();
            }
        }
        else{
            busqueda_rec(A.hijoIzqdo(n),x,A,camino);
            busqueda_rec(A.hijoDrcho(n),x,A,camino);
        }
    }
}

template <typename T>
vector<T> busqueda(T x, const Abin<T>& A){
    vector<T> camino;
    busqueda_rec(A.raiz(),x,A,camino);
    return camino;
}

/* Ejercicio propuesto por Juanfran en prácticas
Implemente una función que, dado un árbol A y 
un elemento T, realice la poda del subarbol cuya raiz 
tiene por elemento T. Puede suponer que no hay elementos 
repetidos en el arbol*/


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
        if(!esHoja(A.hijoIzqdo(n)))
            poda_rec(A.hijoIzqdo(n),A);
        else
            A.eliminarHijoDrcho(n);
    }
    // igual para la derecha
}

template <typename T>
void destruir(T x, Abin<T>& A){
    podar(A.raiz(),x,A);
}


// Ejercicio para hacer

/* Ejercicio propuesto por Juanfran en practicas
Implemente una función que, dado un arbol, 
devuelve el numero de nodos prosperos que existen en el. 
Se considera que un nodo es prospero si es estrictamente 
más rico que sus ascendientes, pero menos que sus descendientes

*/

template <typename T>
int ascendientes(typename Abin<T>::nodo n, const Abin<T>& A){
    if(A.padre(n)==Abin<T>::NODO_NULO)
        return 0;
    else
        return A.elemento(A.padre(n)) + ascendientes(A.padre(n),A);
}

template <typename T>
int descendientes(typename Abin<T>::nodo n, const Abin<T>& A){
    return descendientes_rec(A.hijoIzqdo(n),A)+descendientes_rec(A.hijoDrcho(n),A);
}

template <typename T>
int descendientes_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return 0;
    else
        return A.elemento(n) + descendientes_rec(A.hijoIzqdo(n),A) + descendientes_rec(A.hijoDrcho(n),A);
}

template <typename T>
bool esProspero(typename Abin<T>::nodo n, const Abin<T>& A){
    return (ascendientes(n,A)<A.elemento(n) && descendientes(n,A)>A.elemento(n));
}


template <typename T>
int nodosprosperos(const Abin<T>& A){
    return nodosprosperos_rec(A.raiz(),A);
}

template <typename T>
int nodosprosperos_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        if(esProspero(n,A))
            return 1+nodosprosperos_rec(A.hijoIzqdo(n),A)+nodosprosperos_rec(A.hijoDrcho(n),A);
        else
            return 0+nodosprosperos_rec(A.hijoIzqdo(n),A)+nodosprosperos_rec(A.hijoDrcho(n),A);
    } 
}


/*
Se tiene un árbol binario en el que cada nodo representa una persona y tiene asociado 
un montón de dinero. El objetivo es implementar una función en C++ que reciba un nodo 
del árbol y reparta su herencia entre sus descendientes vivos, es decir, aquellos 
que están más abajo en el árbol y que no han sido marcados como muertos.

La función deberá eliminar el nodo pasado como argumento y repartir su dinero entre 
sus descendientes vivos. Si el nodo no tiene descendientes vivos, su dinero se pierde.

Para realizar la repartición de la herencia, se debe sumar el dinero del nodo y 
distribuirlo entre los descendientes vivos de manera equitativa. Si la división 
no es exacta, se debe asignar el dinero sobrante al primer descendiente en orden 
de recorrido en preorden.
*/
struct tPersona
{
    int dinero;
    bool vivo;
    tPersona(int d=0) : dinero(d), vivo(true) {}
};

int numDescendientesPV_rec(typename Abin<tPersona>::nodo n, const Abin<tPersona>& A){
    if(n==Abin<tPersona>::NODO_NULO)
        return 0;  
    else
        return 1 + numDescendientesPV_rec(A.hijoIzqdo(n),A) + numDescendientesPV_rec(A.hijoDrcho(n),A);

}

int numDescendientesPV(typename Abin<tPersona>::nodo n, const Abin<tPersona>& A){
    if(n==Abin<tPersona>::NODO_NULO)
        return 0;
    else
        return numDescendientesPV_rec(A.hijoIzqdo(n),A) + numDescendientesPV_rec(A.hijoDrcho(n),A);

}



void realizarReparto(typename Abin<tPersona>::nodo n, bool primero, Abin<tPersona>& A, int parte, int p){
    if(n!=Abin<tPersona>::NODO_NULO){
        if(primero) {
            A.elemento(n).dinero += (parte+p);
            primero = false;
        }
        realizarReparto(A.hijoIzqdo(n),primero,A,parte,p);
        realizarReparto(A.hijoDrcho(n),primero,A,parte,p);
    }
}

void repartirDinero(typename Abin<tPersona>::nodo n, Abin<tPersona>& A){
    if(n!=Abin<tPersona>::NODO_NULO){
        int d = A.elemento(n).dinero;
        int nDesc = numDescendientesPV(n,A);
        if(d % nDesc != 0)
            int pico = d % nDesc;
        realizarReparto(A.hijoIzqdo(n),true,A,d/nDesc,d);
        realizarReparto(A.hijoDrcho(n),false,A,d/nDesc,d);
    }
}

void matarNodo(typename Abin<tPersona>::nodo n, Abin<tPersona>& A){
    if(n!=Abin<tPersona>::NODO_NULO){
        A.elemento(n).vivo = false;
        repartirDinero(n,A);
        A.elemento(n).dinero = 0;
    }
}




/*
Sea un conjunto finito de _A = {s1, s2, ..., sn}_, con _n_ constante 
y predeterminado.
Una _proposición_ es:
- un _símbolo_ proposicional del conjunto A, o bien
- una expresión construida aplicando conectivas lógicas
 a otras proposiciones. Se considerarán las conectivas
  (Y), (O), y (NO).

Una forma de representar una proposición es mediante 
un árbol binario en el que los nodos internos contienen 
las conectivas lógicas y las hojas los símbolos 
proposicionales. Por ejemplo, la proposición 
((s1 o s2) y s4) y (¬s1) se representa mediante el 
siguiente árbol binario:

![image](https://github.com/martaajonees/EDNL/assets/100365874/1a454298-b781-4231-b819-b7eaa5e75b20)


Una _valoración_ es una asignación de un valor de verdad 
(_verdadero_ o _falso_) a cada símbolo del conjunto A. 
La forma de representar una valoración de A será 
mediante una secuencia _v_ de valores de verdad que 
asigna el valor i-ésimo de _v_ al símbolo si. 

Por ejemplo, suponiendo n = 3, la secuencia <verdadero,
 falso, verdadero> representa la valoración que asigna 
 verdadero a s1, falso a s2 y verdadero a s3. Una vez 
 que se tiene una valoración, es posible obtener el 
 valor de verdad de cualquier proposición con sólo 
 interpretar las conectivas lógicas con su significado 
 convencional. Veamos una serie de ejemplos suponiendo 
 n = 3:

![image](https://github.com/martaajonees/EDNL/assets/100365874/3f349c43-a1e2-4cff-a015-f1c13249d7e9)
*/

/* Añado(en enero se pidio al menos):
Apartado A. Estructura de datos necesaria para almacenar
valoraciones 
Apartado B. Metodo para retornar el valor de un simbolo
concreto
Apartado C. Metodo para retornar el valor de verdad de
una proposicon representada en un Abin.
*/

// Apartado A

/* Vector dinamico de bool el valor de cada simbolo se 
almacena en el valor del simbolo-1*/
vector<bool> valoraciones;

// Apartado B
bool valorSimbolo(const vector<bool>& valoraciones, int i){
    if(valoraciones.size()<=i && i>0){
        return valoraciones[i-1];
    }
    else
        return false;
}

// Apartado C
struct tProposicion{
    tProposicion(int x): operando(x), esOperador(false){}
    tProposicion(char y): operador(y), esOperador(true){}
    bool esOperador;
    char operador;
    int operando;
};

bool resolverProposion_rec(typename Abin<tProposicion>::nodo n, const Abin<tProposicion> A, const vector<bool>& val){
    if(n==Abin<tProposicion>::NODO_NULO)
        return true;
    else{
        if(!A.elemento(n).esOperador)
            return valorSimbolo(val,A.elemento(n).operando);
        else{
            switch (A.elemento(n).operador)
            {
            case 'N':
                return !resolverProposion_rec(A.hijoIzqdo(n),A,val);
                break;
            case 'Y':
                return resolverProposion_rec(A.hijoIzqdo(n),A,val) && resolverProposion_rec(A.hijoDrcho(n),A,val);
                break;   
            case 'O':
                return resolverProposion_rec(A.hijoIzqdo(n),A,val) || resolverProposion_rec(A.hijoDrcho(n),A,val);
                break;
            default:
                return false;
                break;
            }
        }
    }
}

bool resolverProposicion(const Abin<tProposicion> p, const vector<bool>& val){
    return resolverProposion_rec(p.raiz(),p,val);
}

/*
Se dice que un árbol binario es “zurdo” en uno de estos tres casos:
● si es el árbol vacío; o
● si es una hoja; o
● si sus hijos izquierdo y derecho son los dos “zurdos” y el hijo izquierdo tiene más elementos
que el hijo derecho.
Crear las operaciones necesarias para determinar si un árbol binario es “zurdo”.
*/

template <typename T>
int nEltos(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return 0;
    else{
        return 1+nEltos(A.hijoIzqdo(n),A)+nEltos(A.hijoDrcho(n),A);
    }
}

template<typename T>
bool esZurdo(const Abin<T>& A){
    return esZurdo_rec(A.raiz(),A);
}

template<typename T>
bool esZurdo_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n == Abin<T>::NODO_NULO)
        return true;
    else{
        if(nEltos(A.hijoIzqdo(n),A) > nEltos(A.hijoDrcho(n),A) || (nEltos(A.hijoIzqdo(n),A) == 0 && nEltos(A.hijoDrcho(n),A) == 0))
            return true && esZurdo_rec(A.hijoIzqdo(n),A) && esZurdo_rec(A.hijoDrcho(n),A);
        else
            return false;
    }
}

/*
Propuesta de Juanfran en clase, buscar el ancestro mas comun en un Abin de dos elementos (no nodos, T x,y). 
Tambien se pregunta para un ABB.
Para un Abin: coger los caminos de ambos  y en el primero que divergen pues el justo anterior es el ancestro comun.
*/
template<typename T>
void rama(typename Abin<T>::nodo n, vector<typename Abin<T>::nodo>& v, const Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        v.insert(v.begin(),n);
        rama(A.padre(n),v,A);
    }
}

template<typename T>
void busquedaNodo(typename Abin<T>::nodo n, const T& x, vector<typename Abin<T>::nodo>& v, const Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        if(x == A.elemento(n))
            rama(n,v,A);
        else{
            busquedaNodo(A.hijoIzqdo(n),x,v,A);
            busquedaNodo(A.hijoDrcho(n),x,v,A);
        }
    }
}

template<typename T>
T AncestroComun(const T& x, const T& y, const Abin<T>& A){
    vector<typename Abin<T>::nodo> caminoX,caminoY; 
    busquedaNodo(A.raiz(),x,caminoX,A);
    busquedaNodo(A.raiz(),y,caminoY,A);
    bool iguales = true;
    T aux;
    while(iguales && !caminoY.empty() && !caminoX.empty()){
        T frenteX = A.elemento(caminoX.front());
        T frenteY =  A.elemento(caminoY.front());
        caminoX.erase(caminoX.begin());
        caminoY.erase(caminoY.begin());
        if(frenteX != frenteY)
            iguales = false;
        else
            aux = frenteX;
    }
    return aux;
}


/*
Dado un arbol comprobar si hay ciclos, partiendo un nodo miro si aparece el mismo elto de nuevo usando un vector 
para guardar los elementos e ir haciendo find. Se puede devolver un true o un contador con el numero de nodos que 
ocurre esto. 
Concepto de camino, de como recorrer el arbol y uso de estructuras extras
*/
template <typename T>
void numRepetidos_rec(typename Abin<T>::nodo n, int& contador, vector<T>& v,const Abin<T>& A){
    if(n!=Abin<T>::NODO_NULO){
        typename vector<T>::iterator it = find(v.begin(),v.end(),A.elemento(n));
        if(it==v.end())
            v.insert(v.begin(),A.elemento(n));
        else
            contador++;
        numRepetidos_rec(A.hijoIzqdo(n),contador,v,A);
        numRepetidos_rec(A.hijoDrcho(n),contador,v,A);
    }
}


template <typename T>
int numRepetidos(const Abin<T>& A){
    vector<T> v;
    int contador = 0;
    numRepetidos_rec(A.raiz(),contador,v,A);
    return contador;
}


template <typename T>
bool esABB_recv2(typename Abin<T>::nodo n, const Abin<T>& A, T minimo, T maximo){
    if(n == Abin<T>::NODO_NULO)
        return true;
    else{
        if(A.elemento(n)<maximo && A.elemento(n)>minimo)
            return true && esABB_recv2(A.hijoIzqdo(n),A,minimo,A.elemento(n)) && esABB_recv2(A.hijoDrcho(n),A,A.elemento(n),maximo);
        else{
            return false;
        }

    }
}

template <typename T>
int altura_rec(typename Abin<T>::nodo n ,const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return -1;
    else
        return 1+max(altura_rec(A.hijoIzqdo(n),A),altura_rec(A.hijoDrcho(n),A));
}

template <typename T>
int desequilibrio_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return 0;
    else    
        return max(max(desequilibrio_rec(A.hijoDrcho(n),A),desequilibrio_rec(A.hijoIzqdo(n),A)),abs(altura_rec(A.hijoIzqdo(n),A)-altura_rec(A.hijoDrcho(n),A)));
}

template <typename T>
int desequilibrio(const Abin<T>& A){
    return desequilibrio_rec(A.raiz(),A);
}

template <typename T>
bool factorEq_rec(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return true;
    else{
        int des = desequilibrio_rec(n,A);
        if(des > 1)
            return false;
        else{
            return true && factorEq_rec(A.hijoIzqdo(n),A) && factorEq_rec(A.hijoDrcho(n),A);
        }

    }
}

template <typename T>
bool factorEq(const Abin<T>& A){
    return factorEq_rec(A.raiz(),A);
}

template <typename T>
bool esAVL(const Abin<T>& A){
    return esABB(A) && factorEq(A);
}

/* Ejercicios de practicas a modo de repaso */
/* Act7 p1
 Implementa un subprograma que determine si un árbol binario es o no pseudocompleto. 
En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel 
del mismo cada uno de los nodos tiene dos hijos o ninguno.
*/

template <typename T>
int alturaa(const Abin<T>& A){
    return altura_recc(A.raiz(),A);
}

template <typename T>
int altura_recc(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return -1;
    else
        return 1+max(altura_recc(A.hijoIzqdo(n),A),altura_recc(A.hijoDrcho(n),A));
}

template <typename T>
int profundidad(typename Abin<T>::nodo n, const Abin<T>& A){
    if(n==Abin<T>::NODO_NULO)
        return -1;
    else
        return 1+profundidad(A.padre(n),A);
}

template <typename T>
bool pseudocompleto_rec(int penultimo, typename Abin<T>::nodo n, const Abin<T>& A){
    if(n ==  Abin<T>::NODO_NULO)
        return true;
    else{
        if(profundidad(n,A)==penultimo){
            int nHijos = numHijos(n,A);
            if(nHijos!=0 && nHijos!=2)
                return false;
        }
        return true && pseudocompleto_rec(penultimo,A.hijoIzqdo(n),A) && pseudocompleto_rec(penultimo,A.hijoDrcho(n),A);
    }
}

template<typename T>
bool pseudocompleto(const Abin<T>& A){
    return pseudocompleto_rec(alturaa(A)-1,A.raiz(),A);
}

int main () 
{ 
    /*
    Abin<tProposicion> A; 
    vector<bool> v;
    v = {true,true,true};
    A.insertarRaiz(tProposicion('O'));
    typename Abin<tProposicion>::nodo r = A.raiz();
    A.insertarHijoIzqdo(r,tProposicion('Y'));
    A.insertarHijoDrcho(r,tProposicion('N'));
    typename Abin<tProposicion>::nodo a = A.hijoIzqdo(r);
    typename Abin<tProposicion>::nodo b = A.hijoDrcho(r);
    A.insertarHijoIzqdo(a,tProposicion('O'));
    A.insertarHijoDrcho(a,tProposicion(3));
    typename Abin<tProposicion>::nodo c = A.hijoIzqdo(a);
    A.insertarHijoIzqdo(c,tProposicion(1));
    A.insertarHijoDrcho(c,tProposicion(2));
    A.insertarHijoIzqdo(b,tProposicion(1));


    if(resolverProposicion(A,v))
        cout << "Es verdadera" << endl;
    else
        cout << "Es falsa" << endl;

    
    */

    Abin<int> A;
    rellenarAbin(A,0);
    imprimirAbin(A);
    if(pseudocompleto(A))
        cout << "Es pseudocompleto";  
    else
        cout << "No es pseudocompleto";  
    


    return 0;
} 
