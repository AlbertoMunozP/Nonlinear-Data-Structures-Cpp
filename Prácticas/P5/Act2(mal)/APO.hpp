#ifndef APO_HPP
#define APO_HPP
#include <cassert>
using std::size_t;

template <typename T> 
class Apo 
{
public:
    explicit Apo(size_t maxNodos); // constructor
    void insertar(const T& e);
    void suprimir();
    const T& cima() const;
    bool vacio() const;
    Apo(const Apo<T>& A); // ctor. de copia
    Apo<T>& operator =(const Apo<T>& A); // asignaci�n de apo
    ~Apo(); // destructor
private:
    typedef size_t nodo; // �ndice del vector
    // entre 0 y maxNodos-1
    T* nodos; // vector de nodos
    size_t maxNodos; // tama�o del vector
    size_t numNodos; // �ltimo nodo del �rbol
    nodo padre(nodo i) const { return (i - 1) / 2; }
    nodo hIzq(nodo i) const { return 2 * i + 1; }
    nodo hDer(nodo i) const { return 2 * i + 2; }
    void flotar(nodo i);
    void hundir(nodo i);
};

template <typename T>
inline Apo<T>::Apo(size_t maxNodos) :
    nodos(new T[maxNodos]),
    maxNodos(maxNodos),
    numNodos(0){} /* Apo vac�o.*/

template <typename T>
inline const T& Apo<T>::cima() const
{
    assert(numNodos > 0); // Apo no vac�o.
    return nodos[0];
}

template <typename T>
inline bool Apo<T>::vacio() const
{
    return (numNodos == 0);
}

template <typename T>
inline void Apo<T>::insertar(const T& e)
{
    assert(numNodos < maxNodos); // Apo no lleno.
    nodos[numNodos] = e;
    if (++numNodos > 1) //si APO no estaba vacio
        flotar(numNodos-1); // Reordenar.
}

template <typename T>
void Apo<T>::flotar(nodo i)
{
    T e = nodos[i];
    while (i > 0 && e < nodos[padre(i)])
    {
        nodos[i] = nodos[padre(i)];
        i = padre(i);
    }
    nodos[i] = e;
}

template <typename T>
inline void Apo<T>::suprimir()
{
    assert(numNodos > 0); // Apo no vac�o.
    if (--numNodos > 0) // Apo no queda vac�o.
    {
        nodos[0] = nodos[numNodos];
        if (numNodos > 1) // Quedan dos o m�s elementos.
            hundir(0); // Reordenar.
    }
}

template <typename T>
void Apo<T>::hundir(nodo i)
{
    Apo<T>::nodo i = numNodos;
    if (log2(i+1) % 2 == 0) { // NIVEL MIN (log2(i+1) es la profundidad del nodo i)
        if (nodos[i] > nodos[padre(i)]) {// Está mal colocado con respecto a su padre
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(i);
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote > nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            }

            nodos[indiceFlote] = eltoFlote;
        }
        else if (nodos[i] < nodos[padre(padre(i))]) {   // Está mal colocado con respecto a su abuelo
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(padre(i));
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote < nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            } 

            nodos[indiceFlote] = eltoFlote;
        }
    }
    else {  // Máximos
       if (nodos[i] < nodos[padre(i)]) {// Está mal colocado con respecto a su padre
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(i);
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote < nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            }

            nodos[indiceFlote] = eltoFlote;
        }
        else if (nodos[i] > nodos[padre(padre(i))]) {   // Está mal colocado con respecto a su abuelo
            T eltoFlote = nodos[i];
            nodo indiceFlote = padre(padre(i));
            nodos[i] = nodos[indiceFlote];

            while (padre(padre(indiceFlote)) > 0 && eltoFlote > nodos[padre(padre(indiceFlote))])
            {
                nodos[indiceFlote] = nodos[padre(padre(indiceFlote))];
                indiceFlote = padre(padre(indiceFlote));
            } 

            nodos[indiceFlote] = eltoFlote;
        }
    }
}

template <typename T>
inline Apo<T>::~Apo()
{
    delete[] nodos;
}

template <typename T>
Apo<T>::Apo(const Apo<T>& A) :
    nodos(new T[A.maxNodos]),
    maxNodos(A.maxNodos),
    numNodos(A.numNodos)
    {
    // Copiar el vector.
        for (nodo n = 0; n < numNodos; n++)
            nodos[n] = A.nodos[n];
    }

template <typename T>
Apo<T>& Apo<T>::operator=(const Apo<T>& A)
{
    if (this != &A) // Evitar autoasignaci�n.
    { // Destruir el vector y crear uno nuevo si es necesario.
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        numNodos = A.numNodos;
        // Copiar el vector
        for (nodo n = 0; n < numNodos; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
#endif // APO_HPP
