#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    int n,m, start;
    cout<<"Ingresa la cantidad de nodos que tiene el grafo:";
    cin>>n;
    cout<<"Ingresa la cantidad de aristas que hay en el grafo:";
    cin>>m;
    cout<<"Ingrese el inicio y destino de cada arista, seguido por el peso (ejemplo: 1 4 2):\n";

    vector<pair<int,long long>> adj[n+1]; 
    for (long long i = 0; i<m; i++){
        static int x,y,z;
        cin>>x>>y>>z;
        adj[x].push_back({y,z});
    }
    
    cout<<"Ingresa el nodo inicial:";
    cin>>start;

    vector<long long> dis(n+1, -1);
    set<array<long long, 3>> dijkstra;
    vector<array<long long, 3>> edgs;
    dijkstra.insert({0,start,start});

    while (!dijkstra.empty()){
        auto x = *dijkstra.begin();
        dijkstra.erase(dijkstra.begin());

        static long long w, v, p; //weight, node/vertex, parent
        w = x[0], v = x[1], p = x[2];

        if (dis[v] != -1) continue;
        dis[v] = w;
        edgs.push_back({p, v, w - dis[p]});
        for (auto y : adj[v])
            dijkstra.insert({w + y.second, y.first, v});
    }

    cout<<"\nMínimas distancias desde el nodo inicial:\n";
    for (int i = 1; i<=n; i++){
        cout<<"Hacia "<<i<<": ";
        if (dis[i] < 0) cout<<"No hay camino"; else cout<<dis[i];
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