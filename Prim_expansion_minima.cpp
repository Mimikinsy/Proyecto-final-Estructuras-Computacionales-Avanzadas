/*
	ALGORITMO DE PRIM

    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    *Integrantes:
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez
        Anabel Romo Esparza
        Ariadna Vargas Medina

    * Propósito general:
        Sacar el camino de menor peso en un grafo con el algortimo de Prim. En este algoritmo, a diferencia del de Kruskal,
    se parte de un nodo cualquiera y se va tomando otro nodo conectado a este que tenga menor peso en su arista.

    * IMPORTANTE:
        Como vimos en los otros dos códigos de expansión mínima, este algoritmo no solo puede emplearse en grafos conexos, 
    ponderadoa y no dirigidos

    Complejidad del codigo:
       O(m log n) porque se almacena en una lista de prioridad
       Aunque si se usa matriz de adyacencia la complejidad cambia a O(N^2)
    
*/

#include <bits/stdc++.h>
#include <locale>

using namespace std;

typedef pair<int,int> pii; //esto es para escribir pii en vez de pair de enteros

void prim(int n, vector<vector<pii>> & adj)
{
    vector<int>pesmin(n, 1e9); //para buscar el peso mínimo 
    vector<int> respuesta (n, -1); //para guardar el camino
    vector<bool> visitados(n, 0); //para ver si el nnodo ya está en la repuesta
    
    priority_queue<pii, vector<pii>, greater<pii>> pq;// es una cola de prioridad, de pares en un vector de pares
    //grater<pii> es un parámetro para que priorice el menor valor
    
    //de aqui para abajo es casi como una bfs pero usando pesos
    pesmin[0] = 0; //inicializa en 0 el peso y la pq
    pq.push({0,0});
    
    while(!pq.empty())
    {
        int x = pq.top().second;
        pq.pop();
        
        if(visitados[x]) continue;
        visitados[x] = true;
        
        for(auto &algo : adj[x])
        {
            int y = algo.second;
            int peso = algo.first;
            
            if(!visitados[y] && peso < pesmin[y])
            {
                pesmin[y] = peso;
                respuesta[y] = x;
                pq.push({pesmin[y], y});
            }
        }
    }
    
    //Imprime el resultado
    cout<<"\n Camino de menor peso:\n";
    int total = 0;
    for(int i = 1; i < n; i++)
    {
        cout<<respuesta[i]+1<<" "<<i+1<<" peso: "<<pesmin[i]<<"\n";
        total +=pesmin[i];
    }

    cout<<" El peso total es de: "<<total;
}

int main()
{
    setlocale(LC_ALL, "");

    //Información del grafos
    int vertices, aristas;
    cout<<" Ingrese el núero de vértices: ";
    cin>>vertices;
    cout<<" Ingrese el número de aristas: ";
    cin>>aristas;

    vector<vector<pii>>adj(vertices);

    cout<<" Ingrese las aristas (nodo nodo peso):\n";
    int x, y, z;
    for(int i = 0; i < aristas; i++)
    {
        cout<<"aristas ["<<i+1<<"]; ";
        cin>>x>>y>>z;
        x--;
        y--;
        adj[x].push_back({z, y}); //se pone primero el peso para priorizarlo después
        adj[y].push_back({z, x});
    }

    prim(vertices, adj);

    return 0;
}

/*
Ejemplos (los mismos que en kruskal y reverse kruscal para comprobar que si funciona):
*Grafo 1:
    Entrada:
    8
    13
    1 2 10
    1 3 8
    1 4 12
    2 5 12
    2 6 18
    3 6 15
    4 6 12
    4 7 8
    5 6 10
    5 8 13
    6 8 9
    6 7 10
    7 8 14

    Salida:
     Camino de menor peso:
    1 2 peso: 10
    1 3 peso: 8
    1 4 peso: 12
    6 5 peso: 10
    7 6 peso: 10
    4 7 peso: 8
    6 8 peso: 9
     El peso total es de: 67

*Grafo 2:
    Entrada:
    7
    11
    1 2 7
    1 4 5
    2 3 8
    2 4 9
    2 5 7
    3 5 5
    4 6 6
    4 5 15
    5 6 8
    5 7 9
    6 7 11

    Salida:
    El camino con menor peso es:
    1 2 peso: 7
    5 3 peso: 5
    1 4 peso: 5
    2 5 peso: 7
    4 6 peso: 6
    5 7 peso: 9
     El peso total es de: 39
*/