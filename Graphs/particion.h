
#ifndef PARTICION_H
#define PARTICION_H

#include <vector>

class Particion {
public:
   Particion(int n): padre(n, -1) {}
   void unir(int a, int b);
   int encontrar(int x) const;
private:
   mutable std::vector<int> padre;
};

#endif   // PARTICION_H
