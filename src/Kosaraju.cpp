/* Algoritmo de Kosaraju
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        Kosaraju sirve para encontrar componentes fuertemente conexas en grafos dirigidos y dirigidos ponderados

    Complejidad del codigo:
        Opera en O(N+M) 
    
    Notas: El algoritmo de Kosaraju no funciona para grafos no dirigidos ni grafos con aristas bidireccionales porque en un grafo no dirigido 
	cada arista se considera en ambos sentidos (asi como en las bidireccionales),asi que todas las partes conexas ya serian fuertemente conexas
	y usar Kosaraju no tendria sentido.
*/

#include <bits/stdc++.h>
using namespace std;

class Kosaraju {
public:
    int n; 
    vector<vector<int>> adj;         // grafo original
    vector<vector<int>> adj_rev;     // grafo transpuesto
    vector<bool> visited;
    stack<int> orden;

    Kosaraju(int n) : n(n) {
        adj.resize(n);
        adj_rev.resize(n);
        visited.assign(n, false);
    }

    void agregarArista(int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u); // transpuesta al mismo tiempo
    }

    void dfs1(int u) {
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v]) dfs1(v);
        orden.push(u); // lo metes cuando termina su DFS
    }

    void dfs2(int u, vector<int>& componente) {
        visited[u] = true;
        componente.push_back(u);
        for (int v : adj_rev[u])
            if (!visited[v]) dfs2(v, componente);
    }

    vector<vector<int>> obtenerSCC() {
    /* Realizamos un DFS desde cada vértice no visitado para obtener
    el orden de finalización (finishing times). Cada vértice se
    apila cuando termina su recorrido. Esto nos permite procesar
     más adelante los vértices en el orden correcto para hallar las SCC.*/
    for (int i = 0; i < n; i++)
        if (!visited[i]) 
            dfs1(i);

    
    /* Limpiamos el vector de visitados para reutilizarlo en la segunda
    	pasada del algoritmo. Ahora utilizaremos DFS sobre el grafo
    transpuesto, así que es necesario que todos los vértices estén marcados como no visitados.*/ 
    
    fill(visited.begin(), visited.end(), false);

    vector<vector<int>> scc; // Aquí almacenaremos las componentes fuertemente conexas


    /* Procesamos los vértices en el orden inverso de finalización obtenido anteriormente.
		Cada vez que iniciamos un nuevo DFS sobre el grafo transpuesto, obtenemos exactamente una
    	componente fuertemente conexa completa.*/
    while (!orden.empty()) {
        int u = orden.top();
        orden.pop();

        /*Si este vértice aún no ha sido visitado en la segunda fase,
        entonces inicia una nueva SCC.*/
        if (!visited[u]) {
            vector<int> comp;

            /* dfs2 recorre únicamente los vértices que pertenecen a la misma
            SCC que 'u' dentro del grafo transpuesto.*/
            dfs2(u, comp);

            /* Al finalizar el DFS, 'comp' contiene todos los vértices de una SCC,
            y se agrega al vector de resultados.*/
            scc.push_back(comp);
        }
    }

    // Retornamos la lista completa de todas las SCC encontradas
    return scc;
}

};

int main() {
    int n, m;

    cout << "Ingrese el numero de nodos: ";
    cin >> n;

    cout << "Ingrese el numero de aristas dirigidas: ";
    cin >> m;

    // Creamos el objeto de Kosaraju con n nodos
    Kosaraju g(n);

    cout << "Ingrese las aristas en formato: u v\n";
    cout << "(Esto representa una arista dirigida de u -> v)\n";

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Arista invalida, intenta nuevamente.\n";
            i--;
            continue;
        }

        g.agregarArista(u, v);
    }

    // Obtenemos las SCC con el algoritmo de Kosaraju
    auto scc = g.obtenerSCC();

    cout << "\nComponentes fuertemente conexas encontradas:\n";
    for (auto& comp : scc) {
        for (int x : comp) 
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}

/*
Test cases

Input:

6
6
aristas:
0 1
1 2
2 0
2 3
3 4
4 3

Output:

0 2 1
3 4
5

Input
6
5
aristas:
0 1
1 2
2 3
3 4
4 5

Output:
0
1
2
3
4
5

Input:
8
9
aristas:
0 1
1 2
2 0
2 3
3 4
4 3
4 5
5 6
6 7

Output:
0 1 2
3 4
5
6
7

*/
