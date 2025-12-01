/*
	Componentes Conexas
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        El código muestra las componentes conexas de un grafo para todo tipo de grafos.

    Complejidad del codigo:
        Opera en O(N+M) 
    
*/
#include <bits/stdc++.h>
using namespace std;

void dfs(int inicio, vector<vector<int>>& g, vector<bool>& vis, vector<int>& comp) {
    stack<int> s;
    s.push(inicio);
    vis[inicio] = true;

    while (!s.empty()) {
        int u = s.top(); s.pop();
        comp.push_back(u);

        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                s.push(v);
            }
        }
    }
}

int main() {
	 cout << "Este programa permite al usuario encontrar las componentes conexas de un grafo";
    int n, m;
    cout << "Nodos y aristas: ";
    cin >> n >> m;

    int dirigido, ponderado;
    cout << "Dirigido? (1 = si / 0 = no): ";
    cin >> dirigido;
    cout << "Ponderado? (1/0): ";
    cin >> ponderado;

    vector<vector<int>> grafo(n + 1);

    cout << "Introduce las aristas:\n";
    for (int i = 0; i < m; i++) {
        int u, v, w = 1;

        if (ponderado) {
            cin >> u >> v >> w;
        } else {
            cin >> u >> v;
        }

        grafo[u].push_back(v);
        if (!dirigido) grafo[v].push_back(u);
    }

    vector<bool> vis(n + 1, false);
    vector<vector<int>> comps;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> comp;
            dfs(i, grafo, vis, comp);
            comps.push_back(comp);
        }
    }

    cout << "\nComponentes encontradas:\n";
    for (int i = 0; i < comps.size(); i++) {
        cout << "Componente " << i + 1 << ": ";
        for (int x : comps[i])
            cout << x << " ";
        cout << "\n";
    }

    return 0;
}
/*

No dirigido y no ponderado
Input:
5 3
0
0
1 2
2 3
4 5

output:
Componentes encontradas:
Componente 1: 1 2 3
Componente 2: 4 5


No dirigido, no ponderado y disconexo:
Input:
4 0
0
0
Output:
Componentes encontradas:
Componente 1: 1
Componente 2: 2
Componente 3: 3
Componente 4: 4

Ponderado no dirigido:
Input:
4 3
0
1
1 2 5
2 3 8
3 4 1
Output:
Componentes encontradas:
Componente 1: 1 2 3 4

Dirigido no ponderado:
Input:
6 4
1
0
1 2
2 3
4 5
5 6
Output:
Componentes encontradas:
Componente 1: 1 2 3
Componente 2: 4 5 6

Dirigido y ponderado:
Input:
5 4
1
1
1 2 3
2 5 10
3 4 2
5 3 7
Output:
Componentes encontradas:
Componente 1: 1 2 5 3 4




*/