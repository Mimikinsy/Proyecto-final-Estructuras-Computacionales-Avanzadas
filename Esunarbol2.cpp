/*
Es un arbol o no
Este código verifica si la estructura dada cumple con una condición par ser un arbol, en este caso
nos dira si es conexo o no, por lo que no importa si el arbol tiene peso o no.
El código acepta el peso pero no sirve para nada.
La complejidad total del algoritmo es O(n + m) porque la operación dominante es el DFS utilizado para
detectar ciclos en el grafo. El resto de las operaciones tienen costos menores ( de O(n) o O(1)),
por lo que no afectan la complejidad final. Como resultado nos da que el tiempo total del algoritmo está
determindado por el recorrido profundo del grafo, lo que nos da una complejidad global de O(n + m).
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