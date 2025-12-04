/*
Es un arbol o no
Este código verifica si la estructura dada cumple con una condición par ser un arbol, en este caso
nos dira si tiene ciclos o no, por lo que no importa si el arbol tiene peso o no.
El código acepta el peso pero no sirve para nada.
La complejidad total del algoritmo es O(n + m) porque la operación dominante es el DFS utilizado para
detectar ciclos en el grafo. El resto de las operaciones tienen costos menores ( de O(n) o O(1)),
por lo que no afectan la complejidad final. Como resultado nos da que el tiempo total del algoritmo está
determindado por el recorrido profundo del grafo, lo que nos da una complejidad global de O(n + m).
*/

#include <iostream>
#include <vector>
using namespace std;

bool tieneCiclo(int nodo, int padre, vector<vector<int>>& grafo, vector<bool>& visitado) {
    visitado[nodo] = true;
    for (int vecino : grafo[nodo]) {
        if (!visitado[vecino]) {
            if (tieneCiclo(vecino, nodo, grafo, visitado)) return true;
        } else if (vecino != padre) {
            return true; 
        }
    }
    return false;
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
    for (int i = 0; i < a; i++) {
        int u, v,w;
        cin >> u >> v>>w; //no se guarda el peso porque no tiene relevancia para el problema
        u--; v--; 
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    if (tieneCiclo(0, -1, grafo, visitado)) {
        cout << " El grafo no es un arbol ya que contiene un ciclo.\n";
    
    } else {
        cout << " El grafo no tiene ciclos por lo tanto cumple con una de las condiciones para ser un arbol\n";
    }

    return 0;
}

/*
Casos prueba:

4 3
1 2 5
1 3 7
1 4 2
Output: El grafo no tiene ciclos por lo tanto cumple con una de las condiciones para ser un arbol

6 4
1 2 1
2 3 1
3 1 1     
5 6 2    
Output: El grafo no es un arbol ya que contiene un ciclo.

7 6
1 2 3
1 3 1
2 4 8
2 5 2
3 6 4
3 7 6
Output: El grafo no tiene ciclos por lo tanto cumple con una de las condiciones para ser un arbol

6 6
1 2 5
2 3 7
3 1 3
3 4 2
4 5 2
5 3 1
Output: El grafo no es un arbol ya que contiene un ciclo.

*/
