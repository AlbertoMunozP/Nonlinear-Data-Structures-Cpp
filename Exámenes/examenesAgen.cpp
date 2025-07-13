#include <iostream> 
#include <fstream> 
#include "agen_E-S.h"
#include <algorithm>


/* Calcular la densidad de una arbol. Densidad = gradoMax/numHojas */

template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else{
        int cont = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO){
            cont++;
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int grado(const Agen<T>& A){
    return grado_rec(A.raiz(),A);
}

template <typename T>
int grado_rec(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else{
        int grado = numHijos(n,A);
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO){
            grado = std::max(grado,grado_rec(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return grado;
    }
}

template <typename T>
int numHojas(const Agen<T>& A){
    if(A.raiz() == Agen<T>::NODO_NULO)
        return 0;
    else
        return numHojas_rec(A.raiz(),A);
}

template <typename T>
int numHojas_rec(typename Agen<T>::nodo n, const Agen<T>& A)
{
    if (A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 1;
    else {
        int contador = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO)
        {
            contador += numHojas_rec(hijo, A);
            hijo = A.hermDrcho(hijo);
        }

        return contador;
    }
}

template <typename T>
int numHojasV2(const Agen<T>& A){
   int nHojas = 0;
   numHojas_recV2(A.raiz(),nHojas,A);
   return nHojas;
}

template <typename T>
void numHojas_recV2(typename Agen<T>::nodo n,int& cont, const Agen<T>& A)
{
    if(n!=Agen<T>::NODO_NULO){
        if(A.hijoIzqdo(n)==Agen<T>::NODO_NULO)
            cont++;
        else{
            typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
            while(hijo!=Agen<T>::NODO_NULO){
                numHojas_recV2(hijo,cont,A);
                hijo = A.hermDrcho(hijo);
            }
        }
    }
}

template <typename T>
double densidad(const Agen<T>& A){
    return (double)grado(A)/numHojas(A);
}

/* Implementa un subprograma que devuelva el porcentaje de descendientes propios de 
un árbol general que sean múltiplos de 3. 
Dos formas diferentes de entenderlo denido al corto enunciado:
1- Numero de nodos cuyo numero de descendientes propios es multiplo de 3
(numDescendientesPropios % 3 == 0)
2- Numero de nodos cuyo contenido sea un int que sea multiplo de 3
(cada nodo que A.elemento(n) % 3 == 0)
*/

// Versión 1, la que más sentido tiene para mí

template <typename T>
int numDescendientesPropios(typename Agen<T>::nodo n, const Agen<T>& A) {
    if (n == Agen<T>::NODO_NULO)
        return 0;
    else{
        int cont = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO){
            cont += (1+numDescendientesPropios(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

template <typename T>
int multiplos3descPropios(const Agen<T>& A){
    return multiplos3descPropios_rec(A.raiz(),A);
}

template <typename T>
int multiplos3descPropios_rec(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return 0;
    else{
        int cont = 0;
        int nDesP = numDescendientesPropios(n,A);
        if(nDesP % 3 == 0 & nDesP>0)
            cont++;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO){
            cont += multiplos3descPropios_rec(hijo,A);
            hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}

//Version 2

template <typename T>
int multiplos3descPropiosv2(const Agen<T>& A){
    int cont = 0;
    multiplos3descPropios_recv2(A.raiz(),A,cont);
    return cont;
}

template <typename T>
void multiplos3descPropios_recv2(typename Agen<T>::nodo n, const Agen<T>& A, int& cont){
    if(n != Agen<T>::NODO_NULO){
        if(A.elemento(n)%3==0 && A.elemento(n)>0)
            cont++;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<T>::NODO_NULO){
            multiplos3descPropios_recv2(hijo,A,cont);
            hijo = A.hermDrcho(hijo);
       }
    }
}

/* PARCIAL ABRIL 2023
Una empresa ha desarrollado un programa de generación 
de laberintos mediante árboles generales.
Para comparar estos laberintos generados, quieren desarrollar 
una función que determine la similitud de dos laberintos generados 
(mediante árboles generales).Dos árboles son similares cuando 
tienen la misma ramificación y el mismo elemento 
(sólo en los nodos hojas).
*/

template<typename T>
bool esHoja(typename Agen<T>::nodo n, const Agen<T>& A){
    return A.hijoIzqdo(n) == Agen<T>::NODO_NULO;
}

template<typename T>
bool similares(const Agen<T>& A, const Agen<T>& B){
    return similares_rec(A.raiz(),B.raiz(),A,B);
}

template<typename T>
bool similares_rec(typename Agen<T>::nodo n1, typename Agen<T>::nodo n2, const Agen<T>& A, const Agen<T>& B){
    if(n1 == Agen<T>::NODO_NULO && n2 == Agen<T>::NODO_NULO)
        return true;
    else{
        if(n1 == Agen<T>::NODO_NULO || n2 == Agen<T>::NODO_NULO)
            return false;
        else {
            if(esHoja(n1,A) && esHoja(n2,B))
                return A.elemento(n1) == B.elemento(n2); 
            else{
                if(numHijos(n1,A)!=numHijos(n2,B))
                    return false;
                bool control = true;
                typename Agen<T>::nodo hijo1 = A.hijoIzqdo(n1);
                typename Agen<T>::nodo hijo2 = B.hijoIzqdo(n2);
                while(control && hijo1 != Agen<T>::NODO_NULO && hijo2 != Agen<T>::NODO_NULO){
                    control = control && similares_rec(hijo1,hijo2,A,B);
                    hijo1 = A.hermDrcho(hijo1);
                    hijo2 = A.hermDrcho(hijo2);
                }
                return control && hijo1 == Agen<T>::NODO_NULO && hijo2 == Agen<T>::NODO_NULO;
            }
        }
    }
}

template<typename T>
bool similares_recV2(typename Agen<T>::nodo n1, typename Agen<T>::nodo n2, const Agen<T>& A, const Agen<T>& B){
    if(n1 == Agen<T>::NODO_NULO && n2 == Agen<T>::NODO_NULO)
        return true;
    else{
        if(n1 == Agen<T>::NODO_NULO || n2 == Agen<T>::NODO_NULO)
            return false;
        else {
            if(esHoja(n1,A) && esHoja(n2,B))
                return A.elemento(n1) == B.elemento(n2); 
            else{
                bool control = true;
                typename Agen<T>::nodo hijo1 = A.hijoIzqdo(n1);
                typename Agen<T>::nodo hijo2 = B.hijoIzqdo(n2);
                while(control && hijo1!=Agen<T>::NODO_NULO && hijo2!=Agen<T>::NODO_NULO){
                    control = control && similares_recV2(hijo1,hijo2,A,B);
                    hijo1 = A.hermDrcho(hijo1);
                    hijo2 = A.hermDrcho(hijo2);
                }
                return  hijo1!=Agen<T>::NODO_NULO && hijo2!=Agen<T>::NODO_NULO;
            }
        }
    }
}

/* Queremos calcular que herencia va a recibir cada heredero cuando se muera su 
ancestro, es decir, si el ancestro está muerto se repartirá su herencia entre sus 
descendientes. Si uno de los descendientes falleció, esta suma con la herencia que 
posee dicho descendiente pasará a los descendientes de los descendientes
Intuyo que te daran un Agen de bool siendo True vivo y false muerto.
No termino de entender el enunciado, no esta claro que se pide
*/

struct nodoHerencia
{
    bool estaVivo;
    double riqueza;
    nodoHerencia(bool v, double cant=0) : estaVivo(v), riqueza(cant){}
};





void herencias_rec(typename Agen<nodoHerencia>::nodo n, Agen<nodoHerencia>& A, double r){
   if(n!=Agen<nodoHerencia>::NODO_NULO){
        A.elemento(n).riqueza = r;
        int nHijos = numHijos(n,A);
        typename Agen<nodoHerencia>::nodo hijo = A.hijoIzqdo(n);
        double cantidad = r/nHijos;
        while(hijo != Agen<nodoHerencia>::NODO_NULO){
            herencias_rec(hijo,A,cantidad);
            hijo = A.hermDrcho(hijo);
        }
   }
}

void herencias(Agen<nodoHerencia>& A, double riquezaRaiz){
    herencias_rec(A.raiz(),A,riquezaRaiz);
}

/* Septiembre 2023
Dadp un agen podar cada subarbol cuya raiz este en el penultimo nivel y 
tenga un numero de hijos par.
Mas o menos era así y podaré incluyendo el elemento del penultimo nivel
*/

template<typename T>
void podarRec(typename Agen<T>::nodo n, Agen<T>& A){
	while( A.hijoIzqdo(n)!=Agen<T>::NODO_NULO){
			podarRec( A.hijoIzqdo(n),A);
			A.eliminarHijoIzqdo(n);
	}

}

template <typename T>
int altura_rec(typename Agen<T>::nodo n, const Agen<T>& A){
    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return 0;
    else{
        int alturaMax = -1;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
            alturaMax = std::max(alturaMax, altura_rec(hijo,A));
            hijo = A.hermDrcho(hijo);
        }
        return 1+alturaMax;
    }
}

template <typename T>
int profundidad(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == Agen<T>::NODO_NULO)
        return -1;
    else
        return 1+profundidad(A.padre(n),A);
}


template <typename T>
void podaPenultimoNivel(Agen<T>& A){
    if(A.raiz()!=Agen<T>::NODO_NULO)
        podaPenultimoNivel_rec(A.raiz(),altura_rec(A.raiz(),A)-1,A);
    
}

template <typename T>
void podaPenultimoNivel_rec(typename Agen<T>::nodo n, int profundidadM, Agen<T>& A){
    if(n!=Agen<T>::NODO_NULO){
        if(profundidad(n,A)==profundidadM-1 && numHijos(n,A)%2==0){
            podarRec(n,A);
		    typename Agen<T>::nodo aux = A.hijoIzqdo(A.padre(n));
            T elto = A.elemento(n);
		    if(A.elemento(aux) == elto)
    			A.eliminarHijoIzqdo(A.padre(aux));
		    else{
    			while(A.elemento(A.hermDrcho(aux))!=elto)
				    aux = A.hermDrcho(aux);
			    A.eliminarHermDrcho(aux);
		    }
        }
        else{
            typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
            while(hijo!=Agen<T>::NODO_NULO){
                podaPenultimoNivel_rec(hijo,profundidadM,A);
                hijo = A.hermDrcho(hijo);
            }
        }
    }
}

/* Examen de Agen de reparto de dinero hecho en clase con Juanfran
A la hora de repartir cuando un hijo de la raiz tiene hijos se lo reparte a ellos, el se queda sin. El dinero
se queda en las ---hojas---. Actualizo el nodo antes de la llamada dentro del while
seria:
aux
while
    mod
    llamdarec   
    hermdrcho
Repartir propiedades en lugar de dinero, con la posibilidad de que sea el con mas hijos el que se quede con estas
por delante del dinero.
Cualquier cosa que yo implemente usando un ABB, tengo que sobrecargar el operador <
Solo si esta equilibrado la busqueda podria ser logaritmica
*/

/* Dado un ABB saber si es AVL, factor de equilibrio*/

/*Revisar el de similares*/

/* Inventado por mi
Dados dos arboles generales podar a los descendientes propios de los nodos cuyos numero de hijos 
sean diferentes en ambos arboles para que como resultado los dos arboles se conviertan en dos 
arboles con la misma estructura de ramificacion
*/
/*
template <typename T>
int numHijos(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n==Agen<T>::NODO_NULO)
        return 0;
    else{
        int cont = 0;
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=Agen<T>::NODO_NULO){
                cont++;
                hijo = A.hermDrcho(hijo);
        }
        return cont;
    }
}
*/

template <typename T>
void podaDesc(typename Agen<T>::nodo n, Agen<T>& A){
   if(n!=Agen<T>::NODO_NULO){
        while(A.hijoIzqdo(n)!=Agen<T>::NODO_NULO){
            podaDesc(A.hijoIzqdo(n),A);
            A.eliminarHijoIzqdo(n);
        }
   }
}

template <typename T>
void podaInc(typename Agen<T>::nodo n, Agen<T>& A){
   if(n!=Agen<T>::NODO_NULO){
        podaDesc(n,A);
        typename Agen<T>::nodo padre = A.padre(n);
        if(A.hijoIzqdo(padre)==n)
            A.eliminarHijoIzqdo(padre);
        else{
            typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
            while(A.hermDrcho(hijo)!=n){
                hijo = A.hermDrcho(hijo);
            }
            A.eliminarHermDrcho(hijo);
        }
   }
}

template <typename T>
void crearSimilares_rec(typename Agen<T>::nodo n1, typename Agen<T>::nodo n2, Agen<T>& A, Agen<T>& B){
    if(n1!=Agen<T>::NODO_NULO && n2!=Agen<T>::NODO_NULO){
        if(numHijos(n1,A)!=numHijos(n2,B)){
            podaDesc(n1,A);
            podaDesc(n2,B);
        }
        else{
            typename Agen<T>::nodo hijo1 = A.hijoIzqdo(n1);
            typename Agen<T>::nodo hijo2 = B.hijoIzqdo(n2);
            while(hijo1!=Agen<T>::NODO_NULO){
                crearSimilares_rec(hijo1,hijo2,A,B);
                hijo1 = A.hermDrcho(hijo1);
                hijo2 = A.hermDrcho(hijo2);
            }
        }       
    }
    else{
        if(n1==Agen<T>::NODO_NULO && n2!=Agen<T>::NODO_NULO){
            podaInc(n2,B);
        }
        else if(n1!=Agen<T>::NODO_NULO && n2==Agen<T>::NODO_NULO){
            podaInc(n1,A);
        }
        
    }
}



template <typename T>
void crearSimilares(Agen<T>& A, Agen<T>& B){
    crearSimilares_rec(A.raiz(),B.raiz(),A,B);
}


template <typename T>
void reflejo_rec(typename Agen<T>::nodo nA, typename Agen<T>::nodo nN, const  Agen<T>& A, Agen<T>& N){
    if(nA!=Agen<T>::NODO_NULO){
        typename Agen<T>::nodo hijoA = A.hijoIzqdo(nA);
        while(hijoA!=Agen<T>::NODO_NULO){
            N.insertarHijoIzqdo(nN,A.elemento(hijoA));
            reflejo_rec(hijoA,N.hijoIzqdo(nN),A,N);
            hijoA = A.hermDrcho(hijoA);
        }
    }
}

template <typename T>
Agen<T> reflejo(const Agen<T>& A){
    Agen<T> nuevo;
    if(A.raiz()!=Agen<T>::NODO_NULO){
        nuevo.insertarRaiz(A.elemento(A.raiz()));
        reflejo_rec(A.raiz(),nuevo.raiz(),A,nuevo);
    }
    return nuevo;
}






int main(){
    Agen<int> A,B;
    rellenarAgen(A,0);
     cout << endl;
      cout << endl;
    imprimirAgen(A);
     cout << endl;
      cout << endl;
    B = reflejo(A);
    cout<< endl;
    cout << endl; 
    imprimirAgen(B);
    
    return 0;
}