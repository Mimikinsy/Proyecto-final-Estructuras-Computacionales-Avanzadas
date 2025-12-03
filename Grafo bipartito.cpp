/*
 Este código analiza si un grafo es bipartito o no, para saber si un grafo es bipartito se utiliza la
 tecnica del coloreado y un DFS para recorrer el grafo, es importante usar las dos ya que uno recorre 
 el grafo y el otro nos dice si el vecino y el nodo actual tienen diferente color, las únicas formas que 
 vimos este semestre para recorrer un grafo son DFS/BFS y no es posible ver si una arista esta uniendo 
 dos vertices del mismo conjunto sin el coloreo, por lo que hacer dos códigos que utilizen las tecnicas por separado no seria posible
 con los conocimientos adquiridos durante el curso. 
 ¿Por qué es inrrelevante el peso? Al recorrer un grafo con DFS y BFS el peso no tiene importancia
 entonces como la base de nuestro algoritmo es un DFS el peso no toma relevancia. Si puedes usar grafos
 con peso para saber si son bipartito o no, pero solo para tareas muy especificas como buscar el emparejamiento
 máximo ponderado, en flujos en redes bipartitas o problemas de optimización, pero en un algoritmo que lo único 
 que busca es saber si es o no un grafo bipartito el peso es algo que pasa desapercibido.
 Complejidad:
 La complejidad de este algoritmo es O(n+m) donde n representa el número de vertices y m el número de aristas. 
 Como podemos observar, esta tambien es la complejidad del DFS, esto es porque es la operación más compleja.
 O(n+m) hace referencia a que cada n (vertice) sera visitado una vez y cada m (arista) se recorre una vez en 
 cada dirección de la lista de adyacencia.
*/

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> grafo; // lista de adyacencia
vector<int> color; // 0 = no visitado, 1 = azul, 2 = rojo
bool esBipartito = true;

// DFS para colorear y verificar
void dfs(int nodo, int colorActual) {
    color[nodo] = colorActual;

    // Recorremos todos los vecinos
    for (int vecino : grafo[nodo]) {
        if (color[vecino] == 0) {
            // Si el vecino no ha sido visitado, le damos el color opuesto
            dfs(vecino, (colorActual == 1 ? 2 : 1));
        } 
        else if (color[vecino] == colorActual) {
            esBipartito = false; // como tienen el mismo color, no es bipartito
        }
    }
}

int main() {
    int n, m;
    cout << "Numero de nodos: ";
    cin >> n;
    cout << "Numero de aristas: ";
    cin >> m;

    grafo.assign(n, {});
    color.assign(n, 0);

    cout << "Ingresa las aristas (nodo1 nodo2):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // para que todo empiece en 0 y no en 1
        grafo[u].push_back(v);
        grafo[v].push_back(u); 
    }

    // Se realiza DFS desde cada nodo no visitado por si el grafo es disconexo
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i, 1); 
        }
    }

    cout << "\nResultado:\n";
    if (esBipartito)
        cout << "El grafo es bipartito :)\n";
    else
        cout << "El grafo NO es bipartito :(\n";
}

/*
    Pruebas:

    4
    4
    1 3
    1 4
    2 3
    2 4
    Outpud: El grafo es bipartito :)

    3
    3
    1 2
    2 3
    3 1
    Outpud: El grafo NO es bipartito :(

    5
    4
    1 2
    2 3
    3 4
    4 5
    Outpud: El grafo es bipartito :)

    4
    5
    1 2
    2 3
    3 4
    4 1
    2 4
    Outpud: El grafo NO es bipartito :(


*/
