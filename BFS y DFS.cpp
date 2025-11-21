#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main(void)
{
    system("Color 7d");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int n,m,d,s,f;

    cout<<"\nEste programa buscará un camino entre dos nodos \n"
        <<"si hay un camino, BFS devolverá la distancia y el camino óptimo hacia n\n"
        <<"mientras que DFS devolverá un único camino, sea óptimo o no\n\n";

    cout<<"Ingrese 1 si el grafo es dirigido o 0 si no es dirigido: ";
    cin>>d;
    cout<<"Ingrese la cantidad de nodos que tiene el grafo:";
    cin>>n;
    cout<<"Ingrese la cantidad de aristas que hay en el grafo:";
    cin>>m;
    cout<<"Ingrese los nodos que estén conectados por una arista (ej. 1 4):\n";

    vector<int> adj[n+1];
    vector<int> invadj[n+1];

    for (int i = 0; i<m; i++){
        int x, y;
        cin>>x>>y;
        adj[x].push_back(y);
        if (!d) adj[y].push_back(x);
        invadj[y].push_back(x);
    }

    cout<<"Ingrese el nodo inicial y el nodo meta: (ej. 2 5)\n";
    cin>>s>>f;
    
    cout<<"\nRecorrido listo para iniciar\n\n"; system("pause"); system("cls");

    cout<<"BFS:\n";

    vector<int> dis(n+1, 0);
    queue<int> bfs;
    bfs.push(s);
    dis[s]++;

    while (!bfs.empty()){
        int x = bfs.front();
        bfs.pop();
        cout<<"\n\nBuscando en el nodo "<<x<<".\n";

        for (auto y : adj[x]){
            cout<<"Investigando el nodo adyacente "<<y<<"... ";
            if (dis[y] > 0){ cout<<"El nodo ya fue visitado\n";continue;}
            dis[y] = dis[x]+1;
            bfs.push(y);
            cout<<"Al nodo se le asignó la distancia "<<dis[y]<<endl;
        }
    }

    if (dis[f] == 0) cout<<"\n\nBFS no encontró un camino hacia el nodo "<<n;
    else{
        cout<<"\n\nBFS encontró un camino hacia el nodo "<<n
            <<"\nLa distancia desde "<<s<<" hasta "<<f<< " es: "<< dis[f]
            <<"\nCamino óptimo:\n";
        
        int x = f;
        vector<int> bfsPath;
        bfsPath.push_back(x);
        while (x != s){
            for (int y : invadj[x]){
                if (dis[y] == dis[x]-1){
                    x = y;
                    bfsPath.push_back(x);
                    break;
                }
            }
        }
        
        reverse(bfsPath.begin(), bfsPath.end());

        for (auto y : bfsPath) cout<<y<<" ";
    }

    cout<<endl;
    system("pause"); system("cls");

    cout<<"DFS:\n";

    vector<bool> vis(n+1, 0);
    vector<int> dfsPath;

    function<void(int)> dfs = [&](int node) {
        cout<<"\n\nBuscando en el nodo "<<node<<".\n";
        if (vis[node]) {cout<<"este nodo ya fue visitado\n\n"; return;}
        vis[node] = true;
        dfsPath.push_back(node);
        for (auto neighbor : adj[node]) {
            cout<<"Investigando el nodo adyacente de "<<node<<", "<<neighbor<<"... ";
            if(vis[f]){cout<<"El nodo "<<f<<" ya se encontró, abortando...\n"; return; }
            cout<<"Se tomará el camino por el nodo "<<neighbor<<".\n";
            dfs(neighbor);
        }
        if(vis[f])return;
        cout<<"Tomar el camino por el nodo "<<node<<" no dió resultado, regresando...\n";
        dfsPath.pop_back();
    };
    dfs(s);
    if (vis[f]) {
        cout<<"\nDFS encontró un camino hacia el nodo "<<n;
        cout<<"\nEl camino encontrado es:\n";
        for (auto y : dfsPath) cout<<y<<" ";
    } else {
        cout <<"\nDFS no encotró un camino hacia el nodo "<<n;
    }

    cout<<endl;
    system("pause");

    return 0;
}

/*
5 6
1 2
1 3
3 4
4 5
5 1
5 2
*/