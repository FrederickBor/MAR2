
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
void tesoros(Matriz<EntInf> & m, vector<pair<int, int> > const& cofres) {
    for (int i=1; i < m.numfils(); i++){
        for (int j=1; j < m.numcols(); j++){
            if(3 * cofres[i-1].first > j)
                m[i][j] = m[i - 1][j];
            else
                m[i][j] = max(m[i - 1][j], m[i - 1][j - 3 * cofres[i-1].first] + cofres[i-1].second);
        }
    }
}

/**
 * Funcion que imprime el resultado en el formato que se especifica en el documento.
 */
void imprimirSolucion(Matriz<EntInf> const& m, vector<pair<int, int> > const& cofres){
	vector<int> sol;
    int i = m.numfils() - 1;
    int j = m.numcols() - 1;
    while(i > 0 && j > 0){
      if (m[i][j] != m[i - 1][j]){
          sol.push_back(i - 1);
          i--;
          j -= 3*cofres[i].first;
      }
      else
        i--;
    }
  
    /*
     Imprimimos la cantidad de cofres a recoger
    */
    cout << m[m.numfils()-1][m.numcols()-1] << endl; 
  	
    /*
     Imprimimos la cantidad de cofres recogidos
    */
  	cout << sol.size() << endl;
      
    /*
     Imprimimos en orden inverso los valores que se tomaron
    */
    for(i = sol.size() - 1; i >= 0; i--)
      cout << cofres[sol[i]].first << " " << cofres[sol[i]].second << endl; 
  
  	cout << "---" << endl;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    // leer los datos de la entrada
    int T, N;
    cin >> T >> N;
    
    if (!cin)  // fin de la entrada
        return false;

    vector<pair<int, int> > cofres;
    for (int i=0; i < N; i++){
        int profundidad, oro; 
        cin >> profundidad >> oro;
        cofres.push_back(make_pair(profundidad, oro));
    }

    // minimo posible para la solucion
    Matriz<EntInf> m(N+1, T+1,0);
    tesoros(m, cofres);

    imprimirSolucion(m, cofres);
    
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

