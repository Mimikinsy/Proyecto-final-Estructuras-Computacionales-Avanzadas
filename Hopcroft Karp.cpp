/*
    ALGORITMOS DE EMPAREJAMIENTO - Hopcroft-Karp
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        Implementa el algoritmo Hopcroft–Karp para encontrar un emparejamiento máximo en un
        grafo bipartito. Utiliza una fase de BFS para construir niveles en un conjunto de
        caminos alternantes mínimos y una fase de DFS para recorrer dichos caminos y aumentar
        el emparejamiento. El proceso se repite hasta que no existan caminos aumentantes.

    Complejidad del algoritmo:
        Tiempo O(√V · E) en grafos bipartitos representados mediante listas de adyacencia
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct HopcroftKarp {
    int N, M; //N = número de nodos izquierdos, M = número de nodos derechos
    vector<vector<int>> adj; //Adyacencias de nodos de izquierda a derecha
     //Registro de los pareos (U = izquierda, V = derecha); dist se usa por BFS y DFS
    vector<int> pairU, pairV, dist;

    HopcroftKarp(int nleft, int nright) : N(nleft), M(nright) {
        adj.assign(N + 1, {});
        pairU.assign(N + 1, 0);
        pairV.assign(M + 1, 0);
        dist.assign(N + 1, 0);
    }

    //añade una arista de izquierda a derecha
    void addEdge(int u_left, int v_right) {
        adj[u_left].push_back(v_right);
    }

    //Encuentra el camino aumentado más corto y estructura niveles a los nodos izquierdos
    //esta estructura es usada por DFS para mejorar el emparejamiento en el camino aumentado
    bool bfs() {
        queue<int> q;
        //Añade a la queue todos los nodos izquierdos libres, con distancia 0
        //serán los inicios de los caminos alternados
        for (int u = 1; u <= N; ++u) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else { //Se indica como no visitados (INF) los nodos izquierdos pareados
                dist[u] = INF;
            }
        }
        //foundDist identifica el mínimo nivel en donde aparece un nodo libre en V
        int foundDist = INF;
        //BFS con queue, encuentra caminos aumentados y asigna niveles
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] >= foundDist) continue;
            for (int v : adj[u]) {
                if (pairV[v] == 0) {
                    foundDist = dist[u] + 1;
                } else if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
        //Si foundDist == INF, BFS no encontró un camino aumentado
        //se rompe el ciclo en maxMatching
        return foundDist != INF;
    }

    //Función recursiva DFS, una vez encuentra el nodo derecho libre
    //en el camino aumentado, invierte el emparejamiento del camino, aumentando el pareo en 1
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (pairV[v] == 0 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }
        //Si no encuentra ningún nodo derecho libre desde u, se descarta el nodo
        //con INF para dejar de considerarlo en iteraciones siguientes
        dist[u] = INF;
        return false;
    }

    //Funcion incial para encontrar el pareo máximo, devuelve la cantidad de pares encontrados
    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= N; ++u) {
                if (pairU[u] == 0 && dfs(u))
                    ++matching;
            }
        }
        return matching;
    }
};

int main() {
    int n,m;
    cout<<"Ingresa la cantidad de nodos que tiene el grafo: ";
    cin>>n;
    cout<<"Ingresa la cantidad de aristas que hay en el grafo: ";
    cin>>m;
    cout<<"Ingrese el inicio y destino de cada arista (ejemplo: 1 4):\n";

    //Vector de adyacencias iniciado en base 1 (la etiqueta de los nodos serán mayores a 0) 
    vector<int> g[n+1];

    for (int i = 0; i<m; i++){
        int x, y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    //Calcula la bipartición coloreando el grafo con BFS
    //O reporta si el grafo no es bipartito y aborta
    vector<int> color(n+1, -1);
    bool is_bipartite = true;
    for (int s = 1; s <= n; ++s) {
        if (color[s] != -1) continue;
        queue<int> q;
        color[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    is_bipartite = false;
                }
            }
        }
    }
    if (!is_bipartite) {
        cout << "Error: graph is not bipartite.\n";
        return 0;
    }

    //Mapea los nodos de etiquetas arbitrarias (index) con nuevas etiquetas (Id)
    //correspondientes a las etiquetas creadas por la biparticion izquierda / derecha
    vector<int> leftId(n+1, 0), rightId(n+1, 0);
    vector<int> leftIndexToVertex(1), rightIndexToVertex(1); //También en base 1
    int nL = 0, nR = 0; //Conteo de nodos izquierdos y derechos
    for (int v = 1; v <= n; ++v) {
        if (color[v] == 0) {
            leftId[v] = ++nL;
            leftIndexToVertex.push_back(v);
        } else {
            rightId[v] = ++nR;
            rightIndexToVertex.push_back(v);
        }
    }

    HopcroftKarp hk(nL, nR);
    //Añade las aristas de izquierda a derecha
    for (int u = 1; u <= n; ++u) {
        if (color[u] != 0) continue; //Solo del lado izquierdo
        for (int v : g[u]) {
            //Luego la adyacencia v será del lado derecho
            hk.addEdge(leftId[u], rightId[v]);
        }
    }

    int matching = hk.maxMatching();

    // Imprime los pareos con las etiquetas originales de los nodos
    cout << "Tamaño del pareo máximo: " << matching << "\n";
    for (int u = 1; u <= nL; ++u) {
        int v_idx = hk.pairU[u];
        if (v_idx != 0) {
            int u_orig = leftIndexToVertex[u];
            int v_orig = rightIndexToVertex[v_idx];
            cout << u_orig << " - " << v_orig << "\n";
        }
    }

    return 0;
}

/*
10 9
1 6
1 8
2 9
2 10
3 7
3 8
4 8
4 9
5 8

8 12
1 2
1 3
1 7 
2 4 
2 8
3 4
3 5
4 6
5 6
7 5
7 8
8 6

14 16
1 8
1 11
2 10
2 13
2 14
3 9
3 12
4 9
4 14
5 12
5 13
5 14
6 10
6 13
7 13
7 14

7 6
1 2
1 5
2 7
3 4
3 6
5 6
*/