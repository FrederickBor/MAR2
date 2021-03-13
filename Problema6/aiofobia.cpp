
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
EntInf aiofobia(Matriz<EntInf> & m, string const& palabra, int i, int j) {
    EntInf & res = m[i][j];
    // Si no hemos calculado anteriormente el valor, entonces lo calculamos,
    // en caso contrario devolvemos directamente el valor
    if (res == -1) {
        // Si la i sobrepasa la j entonce no necesitamos nada para
        // hacerlo palindromo.
        if (i > j) res = 0;
        // Si la i es igual a la j entonces es palindromo.
        else if (i == j) res = 0;
        // Si no son iguales la i y la j pero la posición en la palabra
        // contiene la misma letra, entonces pasamos a los siguientes por
        // ambos lados.
        else if (palabra[i] == palabra[j])
            res = aiofobia(m, palabra, i+1, j-1);
        // En caso contrario buscamos el minimo posible entre quitar una
        // letra por la izquierda o quitar una letra por la derecha.
        else
            res = min(aiofobia(m, palabra, i, j-1),
                    aiofobia(m, palabra, i+1, j)) + 1;
    }

    return res;
}

void imprimirSolucion(Matriz<EntInf> & m, string const& palabra, int i, int j, string & sol){
    if (i > j) return;
    if (i == j) sol.push_back(palabra[i]);
    else if (palabra[i] == palabra[j]) {
        sol.push_back(palabra[i]);
        imprimirSolucion(m, palabra, i+1, j-1, sol);
        sol.push_back(palabra[j]);
    } 
    else if (m[i][j] == m[i][j-1] + 1){
        sol.push_back(palabra[j]);
        imprimirSolucion(m, palabra, i, j-1, sol);
        sol.push_back(palabra[j]);
    }
    else{
        sol.push_back(palabra[i]);
        imprimirSolucion(m, palabra, i+1, j, sol);
        sol.push_back(palabra[i]);
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    // leer los datos de la entrada
    string palabra;
    cin >> palabra;
    
    if (!cin)  // fin de la entrada
        return false;

    int n = palabra.length();

    // minimo posible para la solucion
    Matriz<EntInf> m(n, n, -1);
    cout << aiofobia(m, palabra, 0, n-1) << " ";

    string sol;
    imprimirSolucion(m, palabra, 0, n-1, sol);

    cout << sol << endl;
    
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


