//Bellman-Ford para encontrar el camino mas corto
/*

Anabel Romo Esparza
Ariadna Vargas Medina
Gaddiel Mohamed Pedroza Martinez
Stephanie Paola Perez Ramirez

Materia: Estructuras computacionales avanzadas

Bellman Ford funciona con pesos negativos pero no con ciclos negativos
*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
    vector<int> dist(V, 1e8); // distancia inicial "infinita"
    dist[src] = 0;

    // Relajamos todas las aristas V-1 veces. 
    for (int i = 0; i < V - 1; i++) {
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }
    /* Relajar las aristas significa actualizar la ruta o camino 
	con la distancia mas corta a un nodo si se encuntra un camino mas corto desde otro nodo*/

    // Verificacion de ciclo negativo
    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
            cout << "\nEl grafo contiene un ciclo negativo, no se puede proseguir con este algoritmo\n";
            return {};
        }
    }

    return dist;
}


int main() {
	
    int V, E;
    
    cout << "Introduce el numero de vertices: ";
    
    cin >> V;
    
    cout << "Introduce el numero de aristas: ";
    
    cin >> E;

    vector<vector<int>> edges;
    
    cout << "\nIntroduce las aristas en el formato: origen destino peso\n";
    cout << "(Ejemplo: 0 1 5)\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    int src;
    cout << "\nIntroduce el vertice origen: ";
    cin >> src;

    vector<int> dist = bellmanFord(V, edges, src);

    if (!dist.empty()) {
        cout << "\nDistancias mas cortas desde el vertice " << src << ":\n";
        for (int i = 0; i < V; i++) {
            if (dist[i] == 1e8)
                cout << "→ Nodo " << i << ": No se puede alcanzar\n";
            else
                cout << "→ Nodo " << i << ": " << dist[i] << "\n";
        }
    }

    return 0;
}

/*
	GRafos de prueba:
	
	1) Deberia funcionar
  
   5
  10
  
	0 1 6
	0 2 7
	1 2 8
	1 3 5
	1 4 -4
	2 3 -3
	2 4 9
	3 1 -2
	4 0 2
	4 3 7


	2) No funciona por ciclo negativo
	
	 4
	 4
	 0 1 1
	1 2 -1
	2 3 -1
	3 1 -1

	3) No funciona por aristas inalcanzabeles

	5
	4
	0 1 4
	0 2 1
	2 1 2
	1 3 1

	4) Pesos negativos

	3
	3
	0 1 4
	0 2 5
	1 2 -2

*/