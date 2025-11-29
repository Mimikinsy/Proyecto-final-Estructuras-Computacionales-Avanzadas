/*
    ALGORITMOS DE RECORRIDO - BFS Y DFS
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        El código muestra la ejecución paso a paso de ambos recorridos y la forma en que
        construyen caminos bajo sus respectivas políticas de búsqueda.

    Complejidad del algoritmo:
        Ambos recorridos operan en O(N + M) sobre listas de adyacencia
    
    Notas: de estos algoritmos no creamos dos distintos, ya que son algoritmos primitivos
        (a partir de estos se construyen algoritmos más complejos). Cualquier otro algoritmo
        que viole las políticas de recorrido de estos algoritmos dejarán de ser BFS o DFS.
*/

#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    //n: nodos, m: aristas, d: dirigido, s: inicio, f: final
    int n,m,d,s,f;

    cout<<"\nEste programa buscará un camino entre dos nodos \n"
        <<"Si hay un camino, BFS devolverá la distancia y el camino óptimo hacia n\n"
        <<"Mientras que DFS devolverá un único camino, sea óptimo o no\n\n";

    cout<<"Ingrese 1 si el grafo es dirigido o 0 si no es dirigido: ";
    cin>>d;
    cout<<"Ingrese la cantidad de nodos que tiene el grafo: ";
    cin>>n;
    cout<<"Ingrese la cantidad de aristas que hay en el grafo: ";
    cin>>m;
    cout<<"Ingrese los nodos que estén conectados por una arista (ej. 1 4):\n";

    //Vectores de adyacencias iniciados en base 1 (la etiqueta de los nodos serán mayores a 0)
    vector<int> adj[n+1]; //Lista de adyacencias
    vector<int> invadj[n+1]; //Lista inversa de adyacencias, para reportar el camino por BFS

    //Bucle para registrar todas las aristas
    for (int i = 0; i<m; i++){
        int x, y;
        cin>>x>>y;
        adj[x].push_back(y);
        if (!d) adj[y].push_back(x); //Si no es dirigido, se hace otra una arista en sentido contrario
        invadj[y].push_back(x); //Añade la arista en sentido contrario a la lista inversa
    }

    cout<<"Ingrese el nodo inicial y el nodo meta (ej. 2 5):\n";
    cin>>s>>f;
    
    cout<<"\nRecorrido listo para iniciar\n\n"; system("pause"); system("cls");


    /* RECORRIDO POR BFS
    Estructura de BFS utilizando queue y ciclo while
    Registra distancias mínimas desde el nodo inicial */
    cout<<"BFS:\n";

    vector<int> dis(n+1, 0); //Distancias de todos los nodos
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

    /* Si se asignó una distancia a la meta, BFS encontró un camino a ese nodo
    Luego, buscará el camino de vuelta al inicio usando la lista inversa para imprimir el camino óptimo
    De otro modo, no se encontró un camino a la meta */
    if (!dis[f]) cout<<"\n\nBFS no encontró un camino hacia el nodo "<<n;
    else{
        cout<<"\n\nBFS encontró un camino hacia el nodo "<<n
            <<"\nLa distancia desde "<<s<<" hasta "<<f<< " es: "<< dis[f]
            <<"\nCamino óptimo:\n";
        
        int x = f;
        vector<int> bfsPath;
        bfsPath.push_back(x);
        //El nodo anterior, por el cual se llegó al actual, será el que tenga la distancia del actual -1
        while (x != s){
            for (int y : invadj[x]){
                if (dis[y] == dis[x]-1){
                    x = y;
                    bfsPath.push_back(x);
                    break;
                }
            }
        }
        
        //El camino encontrado va desde la meta al inicio, por lo cual se invierte
        reverse(bfsPath.begin(), bfsPath.end());

        for (auto y : bfsPath) cout<<y<<" ";
    }

    cout<<endl;
    system("pause"); system("cls");

    /* RECORRIDO POR DFS
    Estructura de DFS utilizando una función recursiva
    Buscará cualquier camino hacia la meta, sea óptimo o no */
    cout<<"DFS:\n";

    vector<bool> vis(n+1, 0); //Estado de visitado de todos los nodos
    vector<int> dfsPath; //El camino actual de DFS

    //Función lambda recursiva
    function<void(int)> dfs = [&](int node) {
        cout<<"\n\nBuscando en el nodo "<<node<<".\n";
        if (vis[node]) {cout<<"este nodo ya fue visitado\n\n"; return;}
        vis[node] = true;
        dfsPath.push_back(node);
        for (auto neighbor : adj[node]) {
            cout<<"Investigando el nodo adyacente de "<<node<<", "<<neighbor<<"... ";
            //Corte temprano cuando la meta ya fue visitada
            if(vis[f]){cout<<"El nodo "<<f<<" ya se encontró, abortando...\n"; return; }
            cout<<"Se tomará el camino por el nodo "<<neighbor<<".\n";
            dfs(neighbor);
        }
        if(vis[f])return;
        //Backtracking: remueve nodos de la rama si falló en encontrar el camino
    cout<<"Tomar el camino por el nodo "<<node<<" no dió resultado, regresando...\n";
        dfsPath.pop_back();
    };
    //Empieza la recursión desde el nodo inicial
    dfs(s);

    //Si la meta fue visitada, DFS encontró un camino, el cual se guardo en dfsPath durante el proceso
    //De otro modo, no se encontró un camino
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