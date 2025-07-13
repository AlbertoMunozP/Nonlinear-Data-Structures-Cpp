#include <iostream> 
#include <fstream> 
#include <vector>
#include <limits> // Para el examen de esAbb
#include <stack>
#include <climits>
#include "TADArbolDinamicoRecursivo.h" 
#include "abb_E-S.h" 

using namespace std; 

/*
Tenemos un diccionario con su palabra española (string) y su traducción al zuelandés 
(string). Se deben implementar las siguientes operaciones: 
• Construir un diccionario vacío 
• Insertar una palabra española con su traducción al zuelandés 
• Eliminar una palabra española y su traducción. 
• Buscar la traducción de esa palabra en español. 
• Listar las palabras españolas con su traducción al zuelandés en orden 
alfabético.  
*/

struct tPalabra{
    string pSpanish, pZuelandes;
    tPalabra (string a, string b="") : pSpanish(a), pZuelandes(b){}
    // Función miembro para sobrecargar el operador <
    bool operator<(const tPalabra& p) const {
        return pZuelandes.compare(p.pSpanish)<0;
    }
};

class Diccionario{
    public:
        Diccionario(){}
        void insertarPalabra(string esp, string trad);
        void eliminarPalabra(string esp,string trad);
        string traduccion(string zue);
        vector<tPalabra> listar();
        const Abb<tPalabra> palabras() const {return dicc;} 
    private:
        Abb<tPalabra> dicc;
        void listado_rec(vector<tPalabra>& v,const Abb<tPalabra>& A);
};

void Diccionario::insertarPalabra(string esp, string trad){
    dicc.insertar(tPalabra(esp,trad));
}

void Diccionario::eliminarPalabra(string esp, string trad){
    dicc.eliminar(tPalabra(esp,trad));
}

string Diccionario::traduccion(string zue){
    return dicc.buscar(zue).elemento().pSpanish;
} 

vector<tPalabra> Diccionario::listar(){
    vector<tPalabra> v;
    listado_rec(v,dicc);
    return v;

}

void Diccionario::listado_rec(vector<tPalabra>& v,const Abb<tPalabra>& A){
    if(!A.vacio()){
        listado_rec(v,A.izqdo());
        v.push_back(A.elemento());
        listado_rec(v,A.drcho());
    }
}


struct tContacto{
    long telefono;
    string nombre;
    tContacto(long t, string n="") : telefono(t), nombre(n) {}
    bool operator < (tContacto c) const{
        return telefono < c.telefono;
    }
};

class Agenda{
    public:
        Agenda(){};
        void insertarContacto(long numero, string nombre);
        void eliminarContacto(long numero);
        void eliminarContacto(long numero, string nombre);
        string nombre(long numero);
        void listar(const Abb<tContacto>& c);
        const Abb<tContacto>& contactos() const {return aContacto;}
    private:
        Abb<tContacto> aContacto;
};

void Agenda::insertarContacto(long numero, string nombre){
    aContacto.insertar(tContacto(numero,nombre));
}

void Agenda::eliminarContacto(long numero){
    aContacto.eliminar(numero);
}

void Agenda::eliminarContacto(long numero, string nombre){
    aContacto.eliminar(tContacto(numero,nombre));
}

string Agenda::nombre(long numero){
    return aContacto.buscar(numero).elemento().nombre;
}

void Agenda::listar(const Abb<tContacto>& c){
    if(!c.vacio()){
        listar(c.izqdo());
        cout << c.elemento().nombre << "   " << c.elemento().telefono << endl;
        listar(c.drcho());
    }
}

/*
Dado un conjunto ordenado no vacío A, se define el ínfimo de x como el mayor 
elemento de A menor o igual que x, si existe. Análogamente, el supremo de x en A, si 
existe, es el menor elemento de A mayor o igual que x. 
Implementa dos funciones de O(log n) en promedio que dados un valor x cualquiera y 
un ABB A no vacío devuelvan, respectivamente, el ínfimo y el supremo de x en A.  
Si no existe el ínfimo de x en A, la función correspondiente devolverá el mínimo de A. 
Así mismo, la otra función devolverá el máximo de A, en el caso de que no existe el 
supremo. 
Nota: Es absolutamente necesario definir todos los tipos de datos implicados en la 
resolución del ejercicio, así como los prototipos de las operaciones utilizadas de los 
TADs conocidos.
*/

template <typename T>
void minimo(const Abb<T>& A, T& min)
{
    if(!A.vacio())
    {
        min = A.elemento();
        minimo(A.izqdo(), min);
    }
}

template <typename T>
void maximo(const Abb<T>& A, T& max)
{
    if(!A.vacio())
    {
        max = A.elemento();
        maximo(A.drcho(), max);
    }
}

template <typename T>
void infimo(const Abb<T>& A, T x, T& min)
{
    if(!A.vacio())
    {
        if(A.elemento() > x)
            infimo(A.izqdo(), x, min);
        else if(A.elemento() < x)
        {
            if(A.elemento() > min)
                min = A.elemento();
            infimo(A.drcho(), x, min);
        }
    }
}

template <typename T>
void supremo(const Abb<T>& A, T x, T& max)
{
    if(!A.vacio())
    {
        if(A.elemento() > x)
        {
            if(A.elemento() < max)
                max = A.elemento();
            supremo(A.izqdo(), x, max);
        }
        else if(A.elemento() < x)
            supremo(A.drcho(), x, max);
    }
}

template <typename T>
void calcular(const Abb<T>& A, T x)
{
    T min = numeric_limits<T>::min(), max = numeric_limits<T>::max();
    infimo(A, x, min);
    if(min == numeric_limits<T>::min())
    {
        minimo(A, min);
        std::cout << "Minimo: " << min << std::endl;
    }
    else 
        std::cout << "Infimo: " << min << std::endl;
    supremo(A, x, max);
    if(max == numeric_limits<T>::max())
    {
        maximo(A, max);
        std::cout << "Maximo: " << max << std::endl;
    }
    else
        std::cout << "Supremo: " << max << std::endl;
}

/* Propuesto por Juanfran
Dado un ABB y dos elementos busca el antecesor
común entre los dos
*/




int main(){
    
    Diccionario d;
    d.insertarPalabra("Coche","Car");
    d.insertarPalabra("Cerrado","Close");
    d.insertarPalabra("Telefono","Phone");
    d.insertarPalabra("Abierto","Open");
    d.insertarPalabra("Futbol","Football");
    d.insertarPalabra("Rojo","Red");
    vector<tPalabra> v = d.listar();
    for(int i = 0; i < v.size(); i++){
        cout << "Español: " << v[i].pSpanish << "......" << " Zuelandes: " << v[i].pZuelandes << endl;
    }
    d.eliminarPalabra("Futbol","Football");
    d.eliminarPalabra("Coche","Car");
    cout << endl << endl << "Tras la eliminacion ... " << endl << endl;
    vector<tPalabra> x = d.listar();
    for(int i = 0; i < x.size(); i++){
        cout << "Español: " << x[i].pSpanish << "......" << " Zuelandes: " << x[i].pZuelandes << endl;
    }
    /*
    Examen agenda

    Agenda A;
    A.insertarContacto(644130592,"Alberto Munoz");
    A.insertarContacto(643650592,"Adrian Munoz");
    A.insertarContacto(644137866,"Pedro Munoz");
    A.insertarContacto(654123492,"Juan Munoz");

    A.listar(A.contactos());
    cout << endl << endl << "Tras la eliminacion ... " << endl << endl;
    A.eliminarContacto(644130592);
    A.listar(A.contactos());
    
   Abb<int> A;
   rellenarAbb(A,0);
   calcular(A,7);
   // cout << infimoAbb(A,7);
    */
    return 0; 
}