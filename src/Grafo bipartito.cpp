/*
Grafos Bipartitos
 
 ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        Este código te muestra si un grafo es bipartito o no, basandose en el método del coloreo y DFS.

    Complejidad del codigo:
        Opera en O(N+M) 

	Nota:
		Los grafos bipartitos estan definidos como grafos no dirigidos y pero tambien se puede verificar si un grafo dirigido
		es bipartitoo no, lo que no hace el código es aceptar grafos con peso y esto es debido al DFS ya que el no acepta peso 
		y es la base de este algoritmo, aparte para saber si un grafo ponderado es bipartito o no se necesitan de algoritmos 
		mas complejos.

	Impoertante:
		En este tema es solo un algoritmo porque las dos opciones que se dieron en el word son las dos partes funcamentales que 
		se necesitan para el algoritmo, es decir, no puedo sabe si un grafo es bipartito solo por el DFS ya que necesito algo 
		para marcar que la ninguno de sus vecinos sea del mismo conjunto o no puedo usar el coloreo sin una forma de recorrer
		el grafo. 
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
    int n, m, diri;
    cout << "Numero de nodos: ";
    cin >> n;
    cout << "Numero de aristas: ";
    cin >> m;
    cout << "¿El grafo es dirigido? (1 = sí, 0 = no): ";
    cin >> diri;

    grafo.assign(n, {});
    color.assign(n, 0);

    cout << "Ingresa las aristas (nodo1 nodo2):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // para que todo empiece en 0 y no en 1
        grafo[u].push_back(v);
        if (diri==0) {
            grafo[v].push_back(u); // si no es dirigido, añadimos la arista inversa
        }
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
    0
    1 3
    1 4
    2 3
    2 4
    Outpud: El grafo es bipartito :)

    3
    3
    0
    1 2
    2 3
    3 1
    Outpud: El grafo NO es bipartito :(

    5
    4
    0
    1 2
    2 3
    3 4
    4 5
    Outpud: El grafo es bipartito :)

    4
    5
    0
    1 2
    2 3
    3 4
    4 1
    2 4
    Outpud: El grafo NO es bipartito :(

    4
    4
    1
    1 3
    1 4
    2 3
    2 4
    Outpud: El grafo es bipartito :)

    3
    3
    1
    1 2
    2 3
    3 1
    Output: El grafo NO es bipartito :(
*/


