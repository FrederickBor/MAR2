
// Nombre y Apellidos
// Frederick Ernesto Borges Noronha

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void suma(Matriz<EntInf> & m, Matriz<int> const& matriz) {
    for (int j=0; j < m.numcols(); j++) m[0][j] = matriz[0][j];

    for (int i=1; i < m.numfils(); i++){
        for (int j=0; j < m.numcols(); j++){
            if(j == 0){
                if (j == m.numcols()-1)
                    m[i][j] = m[i-1][j] + matriz[i][j];
                else
                    m[i][j] = max(m[i-1][j], m[i-1][j+1]) + matriz[i][j];
            }
            else if (j == m.numcols()-1){
                m[i][j] = max(m[i-1][j], m[i-1][j-1]) + matriz[i][j];
            }
            else{
                m[i][j] = max(max(m[i-1][j], m[i-1][j+1]), m[i-1][j-1]) + matriz[i][j]; 
            }
        } 
    }

    int posMax = 0;
    for(int j = 1; j < m.numcols(); j ++){
        if(m[m.numfils()-1][posMax] < m[m.numfils()-1][j]){
            posMax = j;
        }
    }

    cout << m[m.numfils()-1][posMax] << " " << posMax+1 <<endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    // leer los datos de la entrada
    int N;
    cin >> N;
    
    if (!cin)  // fin de la entrada
        return false;
    
    Matriz<int> matriz(N, N,0);
    for (int i=0; i < N; i++){
        for (int j=0; j < N; j++){
            int valor;
            cin >> valor;
            matriz[i][j] = valor;
        }
    }

    // minimo posible para la solucion
    Matriz<EntInf> m(N, N,0);
    suma(m, matriz);
    
    return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.in");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}


