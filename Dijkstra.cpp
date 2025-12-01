/*
    ALGORITMO DE CAMINOS MÁS CORTOS - Dijkstra
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        Determina las distancias mínimas desde un nodo origen hacia todos los demás nodos del grafo.
        Recopila las aristas que contribuyen a dichas distancias, luego, las muestra en la consola,
        permitiendo reconstruir un árbol de caminos de costo mínimo.

    Complejidad del algoritmo:
        Utilizando una cola de prioridad y listas de adyacencia, Dijkstra opera en O((N + M) log N) sobre
        grafos con pesos no negativos.
*/

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout<<"\nEste programa buscará las distancias / pesos mínimos desde un nodo "
        <<"a los demás. Eligirá las aristas que cumplan este propósito y "
        <<"las mostrará en la consola, de las cuales es posible construir "
        <<"un arbol de caminos de costo mínimo\n\n";

    //n: nodos, m: aristas, d: dirigido, s: inicio
    int n,m,d,s;
    cout<<"Ingrese 1 si el grafo es dirigido o 0 si no es dirigido: ";
    cin>>d;
    cout<<"Ingresa la cantidad de nodos que tiene el grafo:";
    cin>>n;
    cout<<"Ingresa la cantidad de aristas que hay en el grafo:";
    cin>>m;
    cout<<"Ingrese el inicio y destino de cada arista, seguido por el peso (ejemplo: 1 4 2):\n";

    //Vectores de adyacencias iniciados en base 1 (la etiqueta de los nodos serán mayores a 0)
    vector<pair<int,long long>> adj[n+1]; //Lista de adyacencias <nodo, peso>

    for (long long i = 0; i<m; i++){
        static int x,y,z;
        cin>>x>>y>>z;
        adj[x].push_back({y,z});
        if (!d) adj[y].push_back({x,z}); //Si no es dirigido, se hace otra una arista en sentido contrario
    }
    
    cout<<"Ingresa el nodo inicial:";
    cin>>s;

    //Estructura de algoritmo Dijkstra usando set (funciona igual que al usar priority_queue)
    vector<long long> ws(n+1, -1); //Pesos acumulados hacia todos los nodos, se usa -1 como estado no visitado
    set<array<long long, 3>> dijkstra; //Set de arrays donde 0 = peso, 1 = nodo, 2 = padre
    vector<array<long long, 3>> edgs; //Aristas resultantes, en forma de array, donde  0 = inicio, 1 = fin, 3 = peso
    dijkstra.insert({0,s,s});

    while (!dijkstra.empty()){
        auto x = *dijkstra.begin();
        dijkstra.erase(dijkstra.begin());

        static long long w, v, p; //peso, nodo, padre
        w = x[0], v = x[1], p = x[2];

        if (ws[v] != -1) continue;
        ws[v] = w;
        edgs.push_back({p, v, w - ws[p]});
        for (auto y : adj[v])
            dijkstra.insert({w + y.second, y.first, v});
    }

    //Imprime los resultados
    cout<<"\nMínimas distancias desde el nodo inicial:\n";
    for (int i = 1; i<=n; i++){
        cout<<"Hacia "<<i<<": ";
        if (ws[i] < 0) cout<<"No hay camino"; else cout<<ws[i];
        cout<<endl;
    }

    cout<<"\nAristas resultantes del algoritmo:\n";
    for (int i = 1; i<edgs.size(); i++){
        cout<<edgs[i][0]<<" -> "<<edgs[i][1]<<" Peso: "<<edgs[i][2]<<endl;
    }

    return 0;
}

/*

3 4
1 2 6
1 3 2
3 2 3
1 3 4

10 20
8 5 1
9 10 2
7 9 8
9 8 8
10 9 9
7 8 10
8 9 2
7 10 10
4 5 8
5 6 1
4 2 1
5 3 6
10 7 3
3 5 2
5 4 7
1 2 9
2 3 2
6 7 5
3 4 10
3 2 10

9 18
1 2 3
1 3 2
2 4 4
2 5 5
3 2 2
3 5 6
3 7 8
4 7 3
4 6 3
4 9 11
5 1 10
5 7 1
6 1 5
7 6 4
8 7 5
8 9 4
9 6 4
9 5 6
*/