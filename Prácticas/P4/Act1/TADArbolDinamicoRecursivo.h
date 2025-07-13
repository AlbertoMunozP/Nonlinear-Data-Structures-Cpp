#ifndef ABB_H
#define ABB_H
#include <cassert>
template <typename T>
 class Abb {
		public:
			Abb();
			const Abb& buscar(const T& e) const;
			void insertar(const T& e);
			void eliminar(const T& e);
			void poda(const T& e);
			bool vacio() const;
			const T& elemento() const;
			const Abb& izqdo() const;
			const Abb& drcho() const;
			Abb(const Abb& A); // ctor. de copia
			Abb& operator =(const Abb& A); // asig. �rboles
			~Abb(); // destructor
		private:
			struct arbol {
				T elto;
				Abb izq, der;
				arbol(const T& e): elto{e}, izq{}, der{} {}
			};
			arbol* r; // ra�z del �rbol
			T borrarMin();
};
template <typename T>
inline Abb<T>::Abb() : r{nullptr} {}

template <typename T>
inline bool Abb<T>::vacio() const
{
return (r == nullptr);
}

template <typename T>
const Abb<T>& Abb<T>::buscar(const T& e) const
{
	if (r == nullptr) // �rbol vac�o, e no encontrado.
		return *this;
	else if (e < r->elto) // Buscar en sub�rbol izqdo.
		return r->izq.buscar(e);
		else if (r->elto < e) // Buscar en sub�rbol drcho.
			return r->der.buscar(e);
			else // Encontrado e en la ra�z.
				return *this;
}

template <typename T>
void Abb<T>::insertar(const T& e)
{
if (r == nullptr) // �rbol vac�o.
	r = new arbol(e);
else if (e < r->elto) // Insertar en el sub�rbol izqdo.
		r->izq.insertar(e);
	else if (r->elto < e) // Insertar en el sub�rbol drcho.
			r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T& e)
{
	if (r != nullptr) { // �rbol no vac�o.
		if (e < r->elto) // Quitar e del sub�rbol izqdo.
			r->izq.eliminar(e);
		else if (r->elto < e) // Quitar e del sub�rbol drcho.
			r->der.eliminar(e);
			else // Quitar e de la ra�z.
				if (!r->izq.r && !r->der.r) { // 1. Ra�z es hoja.
					delete r;
					r = nullptr; // El �rbol queda vac�o.
				}
				else if (!r->der.r) { // 2. Ra�z s�lo tiene hijo izqdo.
					arbol* a = r->izq.r;
					r->izq.r = nullptr; // Evita destruir el sub�rbol izqdo.
					delete r;
					r = a;
				}
					else if (!r->izq.r) { // 3. Ra�z s�lo tiene hijo drcho.
							arbol* a = r->der.r;
							r->der.r = nullptr; // Evita destruir el sub�rbol drcho.
							delete r;
							r = a;
						}
						else // 4. Ra�z tiene dos hijos
						// Eliminar el m�nimo del sub�rbol derecho y sustituir
						// el elemento de la ra�z por �ste.
							r->elto = r->der.borrarMin();
	}
}
// Ejercicio 1 de la practica 4
template <typename T>
void Abb<T>::poda(const T& e)
{	
	if (r != nullptr){ // �rbol vac�o, e no encontrado.
		if (e < r->elto) // Buscar en sub�rbol izqdo.
			r->izq.poda(e);
		else if (r->elto < e) // Buscar en sub�rbol drcho.
			r->der.poda(e);
			else {
				delete r;
				r = nullptr;
			}			
	}
}
// Tambien se puede como externa, pero sería algo mas dificil

// M�todo privado

template <typename T>
T Abb<T>::borrarMin()
// Elimina el nodo que almacena el menor elemento
// del �rbol. Devuelve el elemento del nodo eliminado.
{
if (r->izq.r == nullptr) { // Sub�rbol izquierdo vac�o.
T e = r->elto;
arbol* hd = r->der.r;
r->der.r = nullptr; // Evita destruir sub�rbol drcho.
delete r;
r = hd; // Sustituir r por el sub�rbol drcho.
return e;
}
else
return r->izq.borrarMin();
}

template <typename T>
inline const T& Abb<T>::elemento() const
{
assert(r != nullptr);
return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const
{
assert(r != nullptr);
return r->izq;
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const
{
assert(r != nullptr);
return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T>& A): r{nullptr}
{
if (A.r != nullptr)
r = new arbol(*A.r); // Copiar ra�z y descendientes.
}

template <typename T>
Abb<T>& Abb<T>::operator =(const Abb<T>& A)
{
if (this != &A) { // Evitar autoasignaci�n.
this->~Abb(); // Vaciar el �rbol.
if (A.r != nullptr)
r = new arbol(*A.r); // Copiar ra�z y descendientes.
}
return *this;
}

template <typename T>
Abb<T>::~Abb()
{
if (r != nullptr) { // �rbol no vac�o.
delete r; // Destruir ra�z y descendientes con r->~arbol()
r = nullptr; // El �rbol queda vac�o.
}

}
#endif // ABB_H

