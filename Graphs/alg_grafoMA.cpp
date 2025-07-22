

#include "alg_grafoMA.h"
#include "pilaenla.h" 
#include "colaenla.h" 

using namespace std;

matriz<bool> Warshall(const Grafo& G)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();

   matriz<bool> A(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];
      A[i][i] = true;
   }

   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++)
            if (!A[i][j])
               A[i][j] = A[i][k] && A[k][j];
   return A;
}

enum visitas {NO_VISITADO, VISITADO};

static Lista<Grafo::vertice> Profun(const Grafo& G, Grafo::vertice v,
                                    vector<visitas>& marcas)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   Lista<vertice> Lv;

   marcas[v] = VISITADO;
   Lv.insertar(v, Lv.fin());
   for (vertice w = 0; w < n; w++)
      if (G[v][w] && marcas[w] == NO_VISITADO)
            Lv += Profun(G, w, marcas);
   return Lv;
}

Lista<Grafo::vertice> Profundidad(const Grafo& G, Grafo::vertice v)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Lista<vertice> Lv;
   vertice i = v;

   do {
      if (marcas[i] == NO_VISITADO)
         Lv += Profun(G, i, marcas);
      i = (i+1) % n;
   } while (i != v);
   return Lv;
}

Lista<Grafo::vertice> Profundidad2(const Grafo& G, Grafo::vertice u)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Pila<vertice> P;
   Lista<vertice> Lv;
   vertice i = u;

   do {
      if (marcas[i] == NO_VISITADO) {
         P.push(i);
         do {
            vertice v = P.tope();
            P.pop();
            if (marcas[v] == NO_VISITADO) {
               // Marcar y procesar v
               marcas[v] = VISITADO;
               Lv.insertar(v, Lv.fin());
               // Meter en la pila los adyacentes no visitados
               for (vertice w = n; w > 0; w--)
                  if (G[v][w-1] && marcas[w-1] == NO_VISITADO)
                     P.push(w-1);
            }
         } while (!P.vacia());
      }
      i = (i+1) % n;
   } while (i != u);
   return Lv;
}

Lista<Grafo::vertice> Anchura(const Grafo& G, Grafo::vertice u)
{
   typedef Grafo::vertice vertice;
   const size_t n = G.numVert();
   vector<visitas> marcas(n, NO_VISITADO);
   Cola<vertice> C;
   Lista<vertice> Lv;
   vertice i = u;

   do {
      if (marcas[i] == NO_VISITADO) {
         C.push(i);
         do {
            vertice v = C.frente();
            C.pop();
            if (marcas[v] == NO_VISITADO) {
               marcas[v] = VISITADO;
               Lv.insertar(v, Lv.fin());
               for (vertice w = n; w > 0; w--)
                  if (G[v][w-1] && marcas[w-1] == NO_VISITADO)
                     C.push(w-1);
            }
         } while (!C.vacia());
      }
      i = (i+1) % n;
   } while (i != u);
   return Lv;
}
