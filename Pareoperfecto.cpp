/* Pareo perfecto utilizando blossom
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
       Encontrar si un grafo tiene pareo perfecto utilizando el matching maximo de blossom (emparejamientos maximos) para cualquier tipo de grafo menos ponderados y/o dirigidos

    Complejidad del codigo:
        Opera en O(n^3) 
    
    Notas: El algoritmo de blossom no tiene la restriccion de funcionar unicamente con grafos bipartitos. BLossom puede manejar
    grafos no bipartitos mas no maneja lo que son grafos con peso ni grafos dirigidos, ya que no existe un algoritmo consisitente hasta la fecha para grafos que sean dirigidos y ponderados.
*/

#include <bits/stdc++.h>
using namespace std;

//Decalaraciones generales

//Num max de nodos
const int MAXN = 500;

// Lista de adyacencia del grafo
vector<int> g[MAXN];

// match[v] = u significa que v esta emparejado con u.
int matchN[MAXN];

// p[v] = padre de v en el arbol alternante
int parentN[MAXN];

// base[v] = base del blossom al que pertenece v
int baseN[MAXN];

// Si un nodo ya fue usado en el BFS
bool usedN[MAXN];

// Marca los nodos que pertenecen a un blossom encontrado
bool blossomN[MAXN];

int n, m; // num de nodos

/*
 Función LCA (Least Common Ancestor):
    Encuentra el ancestro comun mas cercano dentro del árbol alternante.
    Esto permite detectar ciclos impares (blossoms).
*/
int lca(int a, int b) {
    static bool usedTemp[MAXN];
    memset(usedTemp, 0, sizeof(usedTemp));

    while (true) {
        a = baseN[a];
        usedTemp[a] = true;
        if (matchN[a] == -1) break;
        a = parentN[matchN[a]];
    }

    while (true) {
        b = baseN[b];
        if (usedTemp[b]) return b;
        b = parentN[matchN[b]];
    }
}

//Marca el camino desde un nodo v hasta la base b, usado al colapsar un blossom.

void mark_path(int v, int b, int child) {
    while (baseN[v] != b) {
        blossomN[baseN[v]] = blossomN[baseN[matchN[v]]] = true;
        parentN[v] = child;
        child = matchN[v];
        v = parentN[matchN[v]];
    }
}


//hacemos un bfs para encontrar aminos aumentantes en grafos generales.
    //Cuando encuentra un blossom lo colapsa
int find_path(int root) {
    memset(usedN, 0, sizeof(usedN));
    memset(parentN, -1, sizeof(parentN));

    for (int i = 0; i < n; i++)
        baseN[i] = i;

    queue<int> q;
    q.push(root);
    usedN[root] = true;

    while (!q.empty()) {
        int v = q.front(); q.pop();

        for (int u : g[v]) {
            if (baseN[v] == baseN[u] || matchN[v] == u) continue;

            // SI detecta un blossom
            if (u == root || (matchN[u] != -1 && parentN[matchN[u]] != -1)) {
                int curbase = lca(v, u);

                memset(blossomN, 0, sizeof(blossomN));
                mark_path(v, curbase, u);
                mark_path(u, curbase, v);

                for (int i = 0; i < n; i++) {
                    if (blossomN[baseN[i]]) {
                        baseN[i] = curbase;
                        if (!usedN[i]) {
                            usedN[i] = true;
                            q.push(i);
                        }
                    }
                }
            }
            else if (parentN[u] == -1) {
                parentN[u] = v;

                if (matchN[u] == -1) {
                    // 	Si encuentra un camino aumentante actualiza los nodos
                    int cur = u;
                    while (cur != -1) {
                        int prev = parentN[cur];
                        int next = (prev == -1 ? -1 : matchN[prev]);
                        matchN[cur] = prev;
                        if (prev != -1) matchN[prev] = cur;
                        cur = next;
                    }
                    return 1; // Se aumentó el matching
                }
                else {
                    usedN[matchN[u]] = true;
                    q.push(matchN[u]);
                }
            }
        }
    }
    return 0;
}


//Retorna el numero maximo de emparejamientos
int blossom_matching() {
    memset(matchN, -1, sizeof(matchN));
    int result = 0;

    for (int i = 0; i < n; i++)
        if (matchN[i] == -1)
            result += find_path(i);

    return result;
}


int main() {

    cout << "Este programa permite al usuario determinar si un grafo tiene pareo perfecto utilizando el Algoritmo Blossom (Edmonds).\n";
	 cout << "\nNota: Mientras se trate de un grafo no dirigido y no ponderado, pero no tiene la restriccion de que necesite ser bipartito \n";

    cout << "\nIngresa la cantidad de nodos: ";
    cin >> n;

    cout << "\nIngresa la cantidad de aristas: ";
    cin >> m;

    // Limpiar listas anteriores
    for (int i = 0; i < n; i++)
        g[i].clear();

    cout << "\nIngresa cada arista (ejemplo: 1 4):\n";
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int max_matching = blossom_matching();

   if (max_matching * 2 == n)
        cout << "\nEl grafo tiene pareo perfecto\n";
    else
        cout << "\nEl grafo no tiene pareo perfecto\n";

    return 0;
}





