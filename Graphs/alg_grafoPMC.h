#ifndef ALG_GRAFO_P_H
#define ALG_GRAFO_P_H

#include <cassert>
#include "grafoPMC.h"       
#include <vector>           
#include "matriz.h"         
#include "apo.h"            
#include "particion.h"      

template <typename tCoste> tCoste suma(tCoste x, tCoste y)
{
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   if (x == INFINITO || y == INFINITO)
      return INFINITO;
   else
      return x + y;
}

template <typename tCoste>
vector<tCoste> Dijkstra(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice origen,
                        vector<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);                  
   vector<tCoste> D;                          

   D = G[origen];
   D[origen] = 0;                             
   P = vector<vertice>(n, origen);

   S[origen] = true;                          
   for (size_t i = 1; i <= n-2; i++) {
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < n; v++)
         if (!S[v] && D[v] <= costeMin) {
            costeMin = D[v];
            w = v;
         }
      S[w] = true;                          
      for (v = 0; v < n; v++)
         if (!S[v]) {
            tCoste Owv = suma(D[w], G[w][v]);
            if (Owv < D[v]) {
               D[v] = Owv;
               P[v] = w;
            }
         }
   }
   return D;
}

template <typename tCoste> typename GrafoP<tCoste>::tCamino
camino(typename GrafoP<tCoste>::vertice orig,
       typename GrafoP<tCoste>::vertice v,
       const vector<typename GrafoP<tCoste>::vertice>& P)
{
   typename GrafoP<tCoste>::tCamino C;

   C.insertar(v, C.primera());
   do {
      C.insertar(P[v], C.primera());
      v = P[v];
   } while (v != orig);
   return C;
}

template <typename tCoste>
matriz<tCoste> Floyd(const GrafoP<tCoste>& G,
                     matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n);   

   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++) {
      A[i] = G[i];                    
      A[i][i] = 0;                    
      P[i] = vector<vertice>(n, i);   
   }
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++) {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if (ikj < A[i][j]) {
               A[i][j] = ikj;
               P[i][j] = k;
            }
         }
   return A;
}

template <typename tCoste> typename GrafoP<tCoste>::tCamino
caminoAux(typename GrafoP<tCoste>::vertice v,
          typename GrafoP<tCoste>::vertice w,
          const matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typename GrafoP<tCoste>::tCamino C1, C2;
   typename GrafoP<tCoste>::vertice u = P[v][w];

   if (u != v) {
      C1 = caminoAux<tCoste>(v, u, P);
      C1.insertar(u, C1.fin());
      C2 = caminoAux<tCoste>(u, w, P);// Lista<vertice>::operator +=(), concatena C1 y C2
   }
   return C1;
}

template <typename tCoste> typename GrafoP<tCoste>::tCamino
camino(typename GrafoP<tCoste>::vertice v,
       typename GrafoP<tCoste>::vertice w,
       const matriz<typename GrafoP<tCoste>::vertice>& P)
{
   typename GrafoP<tCoste>::tCamino C = caminoAux<tCoste>(v, w, P);
   C.insertar(v, C.primera());
   C.insertar(w, C.fin());
   return C;
}


template <typename tCoste>
GrafoP<tCoste> Prim(const GrafoP<tCoste>& G)
{
   assert(!G.esDirigido());

   typedef typename GrafoP<tCoste>::vertice vertice;
   typedef typename GrafoP<tCoste>::arista arista;
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   arista a;
   const size_t n = G.numVert();
   GrafoP<tCoste> g(n);      
   vector<bool> U(n, false); 
   Apo<arista> A(n*(n-1)/2-n+2); 
   U[0] = true;   
   for (vertice v = 1; v < n; v++)
      if (G[0][v] != INFINITO)
         A.insertar(arista(0, v, G[0][v]));
   for (size_t i = 1; i <= n-1; i++) {     
      do {
         a = A.cima();
         A.suprimir();
      } while (U[a.dest]);
      g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
      vertice u = a.dest;
      U[u] = true;
     
      for (vertice v = 0; v < n; v++)
         if (!U[v] && G[u][v] != INFINITO)
            A.insertar(arista(u, v, G[u][v]));
   }
   return g;
}

template <typename tCoste>
GrafoP<tCoste> Kruskall(const GrafoP<tCoste>& G)

{
   assert(!G.esDirigido());

   typedef typename GrafoP<tCoste>::vertice vertice;
   typedef typename GrafoP<tCoste>::arista arista;
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   const size_t n = G.numVert();
   GrafoP<tCoste> g(n);   
   Particion P(n);   
   Apo<arista> A(n*n);    

   for (vertice u = 0; u < n; u++)
      for (vertice v = u+1; v < n; v++)
         if (G[u][v] != INFINITO)
            A.insertar(arista(u, v, G[u][v]));

   size_t i = 1;
   while (i <= n-1) {   
      arista a = A.cima(); 
      A.suprimir();
      vertice u = P.encontrar(a.orig);
      vertice v = P.encontrar(a.dest);
      if (u != v) { 
         P.unir(u, v);
         g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
         i++;
      }
   }
   return g;
}


template <typename tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste> &G, typename GrafoP<tCoste>::vertice destino,
                           vector<typename GrafoP<tCoste>::vertice> &P)
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false); 
   vector<tCoste> D(n);

   for (int i = 0; i < n; i++)
      D[i] = G[i][destino];

   D[destino] = 0;
   P = vector<vertice>(n, destino);

   S[destino] = true;
   for (size_t i = 1; i <= n - 2; i++)
   {
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < n; v++)
         if (!S[v] && D[v] <= costeMin)
         {
            costeMin = D[v];
            w = v;
         }
      S[w] = true;
      for (v = 0; v < n; v++)
         if (!S[v])
         {
            tCoste Owv = suma(D[w], G[v][w]);
            if (Owv < D[v])
            {
               D[v] = Owv;
               P[v] = w;
            }
         }
   }
   return D;
}



#endif   // ALG_GRAFO_P_H
