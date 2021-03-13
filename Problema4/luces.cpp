
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
/**
 * 
 */
void luces(Matriz<EntInf> & m, vector<int> const& potencias, vector<int> const& costes) {
   for (int j = 1; j < m.numcols(); j++)
      m[0][j] = Infinito;
   
   for (int i = 1; i < m.numfils(); i++){
      for (int j = 1; j < m.numcols(); j++){
         if (potencias[i - 1] > j) // no se toma este tipo de bombilla
            m[i][j] = m[i-1][j];
         else // se toma (o no) el tipo de bombilla
            m[i][j] = min( m[i-1][j], m[i][j - potencias[i-1]] + costes[i-1]);
      }
   }
}

/**
 * Funcion que imprime el resultado en el formato que se especifica en el documento.
 */
void imprimirSolucion(Matriz<EntInf> const& m, int const& pmin){
   EntInf minCoste = Infinito;
   int posCosteMin;

   for (int j = pmin; j < m.numcols(); j++){
      if (m[m.numfils() - 1][j] < minCoste){
         minCoste = m[m.numfils() - 1][j];
         posCosteMin = j;
      }
   }

   if (minCoste == Infinito){
      cout << "IMPOSIBLE" << endl;
      return;
   }

   cout << minCoste << " " << posCosteMin << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   // leer los datos de la entrada
   int n, pmax, pmin;
   cin >> n >> pmax >> pmin;
   
   if (!cin)  // fin de la entrada
      return false;

   // Leemos las bombillas
   vector<int> potencias;
   vector<int> costes;

   for (int i=0; i < n; i++){
      int potencia;
      cin >> potencia;
      potencias.push_back(potencia);
   }

   for (int i=0; i < n; i++){
      int coste;
      cin >> coste;
      costes.push_back(coste);
   }

   // minimo posible para la solucion
   Matriz<EntInf> m(n+1, pmax + 1, 0);
   luces(m, potencias, costes);

   imprimirSolucion(m, pmin);
   
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
