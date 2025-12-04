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

typedef pair<int,int> pii; //esto ees para escribir pii en vez de pair de enteros

void prim(int n, vector<vector<pii>> & adj)
{
    vector<int>pesmin; //para buscar el peso mínimo 
    vector<int> respuesta (n, -1); //para guardar el camino
    vector<bool> visitados(n, 0); //para ver si el nnodo ya está en la repuesta

    priority_queue<pii, vector<pii>, greater<pii>> pq;// es una cola de prioridad, de pares en un vector de pares
    //grater<pii> es un parámetro para que priorice el menor valor

    //de aqui para abajo es casi como una bfs pero usando pesos
    pesmin[0] = 0; //inicializa en 0 el peso y l apq
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
    for(int i = 1; i < n; i++)
    {
        cout<<respuesta[i]<<" "<<i<<" peso: "<<pesmin[i]<<"\n";
    }
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
        cin>>x>>y>>z;
        adj[x].push_back({z, y});
        adj[y].push_back({z, x});
    }

    prim(vertices, adj);

    return 0;
}