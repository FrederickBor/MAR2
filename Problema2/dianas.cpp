
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

/**
 * Función imprimeSolucion
 * 
 * @param[in] m [Matriz] Matriz que contiene la solución al problema
 * @param[in] v [Vector] Vector que contiene los valores de los sectores
 * @param[in] N [Integer] Valor deseado a alcanzar 
 */
void imprimeSolucion(Matriz<EntInf> const& m, vector<int> const& v, int N){
    vector<int> sol;
    int i = v.size();
    int filas = m.numfils() -1;
    while (N > 0){
        if (v[i-1] <= N && 
            m[filas][N] == m[filas][N - v[i-1]] +1)
        {
            sol.push_back(v[i-1]);
            N -= v[i-1];
        }
        else i--;
    }
  	
	// imprimimos la solución
    for (int k=0; k < sol.size(); k++){
        cout << sol[k];
        if (k != sol.size()-1) cout << " ";
    }
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
EntInf minimoPosible(Matriz<EntInf> & m, vector<int> const& v) {
    m[0][0] = 0; // No es necesario

    for (int i=1; i < m.numfils(); i++) m[i][0] = 0;
    for (int j=1; j < m.numcols(); j++) m[0][j] = Infinito;

    for (long long int i=1; i < m.numfils(); i++){
        for (long long int j=1; j < m.numcols(); j++){
            if(j < v[i-1])
                m[i][j] = m[i - 1][j];
            else
                m[i][j] = min(m[i - 1][j], m[i][j - v[i-1]] + 1); 
        } 
    }

    return m[m.numfils() - 1][m.numcols() - 1];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    // leer los datos de la entrada
    int N,S;
    cin >> N >> S;
    
    if (!cin)  // fin de la entrada
        return false;
    
    vector<int> sectores;
    for (int i=0; i < S; i++){
        int sector;
        cin >> sector;
        sectores.push_back(sector);
    }

    // minimo posible para la solucion
    Matriz<EntInf> m(S+1, N+1,0);
    EntInf minPosible = minimoPosible(m, sectores);

    // escribir sol
    if (minPosible == Infinito)
        cout << "Imposible" << endl;
    else{
        cout << minPosible << ": ";
        // imprimir los valores
        imprimeSolucion(m, sectores, N);
        cout << endl;
    }
    
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


