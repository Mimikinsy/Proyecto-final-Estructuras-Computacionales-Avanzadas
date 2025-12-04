/*    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        El código muestra si un grafo cumple con una de las tres condiciones para ser un arbol. En este caso verifica si un grafo es
        conexo o no.

    Complejidad del codigo:
        Opera en O(N+M) 
*/

#include <iostream>
#include <vector>
using namespace std;

void recorrido(int nodo, vector<vector<int>>& grafo, vector<bool>& visitado) {
    visitado[nodo] = true; //DFS complejidad O(n+m)
    for (int vecino : grafo[nodo]) {
        if (!visitado[vecino]) {
            recorrido(vecino, grafo, visitado);
        }
    }
}


bool esConexo(vector<bool>& visitado) {
    for (bool v : visitado) // v representa cada valor de visitado, es decir agarra los valores de true o false de visitado de 0 a visitadi.size()
        if (!v) return false;
    return true;
}

int main() {
    int n, a;
    cout << "Numero de nodos: \n";
    cin >> n;
    cout << "Numero de aristas: \n";
    cin >> a;
    vector<bool> visitado(n, false);
    vector<vector<int>> grafo(n); //lista de adyacencia 
    
    cout << "Ingresa cada arista como: nodo_inicial nodo_final peso:\n";
    for (int i = 0; i < a; i++) { //O(m)
        int u, v,w;
        cin >> u >> v>>w; //no se guarda el peso porque no tiene relevancia para el problema
        u--; v--; 
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    recorrido(0, grafo, visitado);

    if (!esConexo(visitado)) {
        cout << " El grafo no es un arbol ya que es disconexo.\n";
    } else {
        cout << " El grafo es conexo, por lo tanto cumple una de las condiciones para ser un arbol.\n";
    }

    return 0;
}

/*
Casos prueba:

4 3
1 2 5
1 3 7
1 4 2
Output: El grafo es conexo, por lo tanto cumple una de las condiciones para ser un arbol.

6 5
1 2 1
2 3 1
4 5 1
5 6 1
3 2 1    
Output: El grafo no es un arbol ya que es disconexo.

7 6
1 2 3
1 3 1
2 4 8
2 5 2
3 6 4
3 7 6
Output: El grafo es conexo, por lo tanto cumple una de las condiciones para ser un arbol.

5 4
1 2 3
3 4 6
4 5 9
5 3 2
Output: El grafo no es un arbol ya que es disconexo.


*/
