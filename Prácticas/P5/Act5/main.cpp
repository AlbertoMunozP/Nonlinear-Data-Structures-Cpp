#include<iostream>
#include<string>
#include<vector>
#include "Agen.h"
#include "agen_E-S.h"

using namespace std;

// Clase de Juanfran
/* Conocemos donde colocamos cada color, cada nodo es un
struct para saber el color y las dimensiones 
2^k siendo k el nivel
*/
struct Pixel{
    std::string color;
    int x0,x1,y0,y1;
    Pixel(int a, int b, int c, int d, string co ="") : 
    color(co), x0(a), x1(b), y0(c), y1(d) {}
};

void rellenarMatriz(typename Agen<Pixel>::nodo n, vector<vector<string>>& matriz, const Agen<Pixel>& A) {
    if (n != Agen<Pixel>::NODO_NULO) {
        if (A.elemento(n).color == "") {
            typename Agen<Pixel>::nodo hijo = A.hijoIzqdo(n);
            while (hijo != Agen<Pixel>::NODO_NULO) {
                rellenarMatriz(hijo, matriz, A);
                hijo = A.hermDrcho(hijo);
            }
        } else {
            int x = A.elemento(n).x0;
            int hastax = A.elemento(n).x1;
            int y = A.elemento(n).y0;
            int hastay = A.elemento(n).y1;
            for (int i = x; i <= hastax; i++) {
                for (int j = y; j <= hastay; j++) {
                    matriz[i][j] = A.elemento(n).color;
                }
            }
        }
    }
}



void printearMatriz(const vector<vector<string>>& m){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
                if(m[i][j] == "Blanco")
                    cout << "B ";
                else
                    cout << "N ";
        }
        cout<< endl;
    }
}

int main() {
    vector<vector<string>> v(8, vector<string>(8, ""));;
    Agen<Pixel> A;
    A.insertarRaiz(Pixel(0,7,0,7,""));
    A.insertarHijoIzqdo(A.raiz(),Pixel(0,3,0,3,""));
    typename Agen<Pixel>::nodo hijo = A.hijoIzqdo(A.raiz());
    A.insertarHijoIzqdo(hijo,Pixel(0,1,0,1,"Blanco"));    
    typename Agen<Pixel>::nodo h1 = A.hijoIzqdo(hijo);
    A.insertarHermDrcho(h1,Pixel(2,3,0,1,"Blanco"));
    h1 = A.hermDrcho(h1);
    A.insertarHermDrcho(h1,Pixel(0,1,2,3,"Blanco"));
    h1 = A.hermDrcho(h1);
    A.insertarHermDrcho(h1,Pixel(2,3,2,3,"Negro"));

    
    
    A.insertarHermDrcho(hijo,Pixel(4,7,0,4,"Negro"));
    hijo = A.hermDrcho(hijo);
    A.insertarHermDrcho(hijo,Pixel(0,3,4,7,"Negro"));
    hijo = A.hermDrcho(hijo);
    A.insertarHermDrcho(hijo,Pixel(4,7,4,7,"Blanco"));
    

    rellenarMatriz(A.raiz(),v,A);
    printearMatriz(v);
   
    return 0;
}