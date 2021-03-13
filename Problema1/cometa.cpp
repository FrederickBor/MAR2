
// Nombre y Apellidos
// Frederick Ernesto Borges Noronha

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

using namespace std;

long long int sumNumbers(long long int a, long long int b){ 
   if (a==LLONG_MAX || b==LLONG_MAX) return LLONG_MAX;
   return a + b;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
long long int calculaSoluciones(Matriz<long long int> & m, vector<pair<long long int,long long int> > const&  v) {
   m[0][0] = 1;
   
   for(long long int i=1; i < m.numfils(); i++)
      m[i][0] = 1;

   for(long long int j=1; j < m.numcols(); j++)
      m[0][j] =0;

   for (long long int i=1; i < m.numfils(); i++){
      for (long long int j=1; j < m.numcols(); j++){
         if(j < v[i-1].first)
            m[i][j] = m[i - 1][j];
         else
            m[i][j] = m[i - 1][j] + m[i - 1][j - v[i-1].first];
      }
   }

   return m[m.numfils() - 1][m.numcols() - 1];
}

long long int minimoPosible(Matriz<long long int> & m, vector<pair<long long int,long long int> > const& v) {
   m[0][0] = 0;

   for(long long int i=1; i < m.numfils(); i++) 
      m[i][0] = 0;

   for(long long int j=1; j < m.numcols(); j++)
      m[0][j] = LLONG_MAX;

   for (long long int i=1; i < m.numfils(); i++){
      for (long long int j=1; j < m.numcols(); j++){
         if(j < v[i-1].first)
            m[i][j] = m[i - 1][j];
         else
            m[i][j] = min(m[i - 1][j], sumNumbers(m[i - 1][j - v[i-1].first], 1)); 
      } 
   }

   return m[m.numfils() - 1][m.numcols() - 1]; 
}

long long int minimoCoste(Matriz<long long int> & m, vector<pair<long long int,long long int> > const& v){
   m[0][0] = 0;
  
   for(long long int i=1; i < m.numfils(); i++) 
      m[i][0] = 0;
  
   for(long long int j=1; j < m.numcols(); j++)
      m[0][j] = LLONG_MAX;
  
   for (long long int i=1; i < m.numfils(); i++){
      for (long long int j=1; j < m.numcols(); j++){
			if(j < v[i-1].first)
            m[i][j] = m[i - 1][j];
        	else {
            m[i][j] = min(m[i - 1][j], sumNumbers(m[i - 1][j - v[i-1].first], v[i-1].second));
         }
      } 
   }

  return m[m.numfils() - 1][m.numcols() - 1]; 
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   // leer los datos de la entrada
   long long int N,L;
   cin >> N >> L; 

   if (!cin)  // fin de la entrada
      return false;
     

   vector< pair<long long int,long long int> > v; 

   for (long long int i=0; i < N; i++){
      long long int longitud, coste;
      cin >> longitud >> coste;
      v.push_back(make_pair(longitud, coste));
   }

   // soluciones posibles
   Matriz<long long int> m1(N+1,L+1,0);
   long long int numSoluciones = calculaSoluciones(m1, v);
  
  	if (numSoluciones == 0){
      cout << "NO" << endl;
      return true;
   }
   
   // minimo posible para la solucion
   Matriz<long long int> m2(N+1,L+1,0);
   long long int minPosible = minimoPosible(m2, v);

   // minimo coste para la solucion
   Matriz<long long int> m3(N+1,L+1,0);
   long long int minCoste = minimoCoste(m3, v);
   
   // escribir sol
   
   cout << "SI " << numSoluciones << " " << minPosible << " " << minCoste << endl; 
  
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
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
