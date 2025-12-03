/*
	REVERSE-DELETE ALGORITHM (REVERSE KRUSKAL)
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    *Integrantes:
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez
        Anabel Romo Esparza
        Ariadna Vargas Medina

    * Propósito general:
        Desarrollar un código del algoritmo de reverse kruskal para encontrar el camino de menor peso.
    Reverse kruscal usa la estrategia de tamar todo el grafo e ir borrando aristas de mayor peso, siempre verificando que 
    el grafo siga siendo conexo. 

    * IMPORTANTE:
        AL igual que en el algoritmo de Kuskal, este algoritmo solo se puede 
    emplera en grafos ponderados(ya que su función es encontrar el menor peso)
    y no dirigidos ya que para lso grafos dirigidos usa otro tipo de algoritmo

    Complejidad del codigo:
    O(E log E + EV)    
    
*/

#include <bits/stdc++.h>
#include <locale>

using namespace std;

struct infograf{ //para poder poner los nodos que están unidos y el peso que tienen
    int u, v, peso;
};

//Estructura de union-find
struct DSU{
    vector<int> padre, rango;//en kruskal usamos estos vectores como globales pero esta es otra forma de ponerlo

    DSU(int n){  //se llenan los vectores
        padre.resize(n+1);
        rango.resize(n+1, 0);
        iota(padre.begin(), padre.end(), 0);
    }

    int find (int x) //se encuentra al padre/representante de el nodo
    {
        if(padre[x] != x)
            padre[x] = find(padre[x]);
        return padre[x];
    }

    void unite(int a, int b) //une los nodos en el mismo conjunto
    {
        a = find(a);
        b = find(b);
        if(a != b)
        {
            if(rango[a] < rango[b]) swap(a, b);
            padre[b] = a;
            if(rango[a] == rango[b]) rango[a]++;
        }
    }
};


bool comp(infograf a, infograf b) //si es verdad la condición lo cambia
{
    return a.peso < b.peso;
}

int main()
{
    setlocale(LC_ALL, "");
    //pedir la info del grafo
    int vertices, aristas;
    cout<<"\n Ingrese el número de vértices: ";
    cin>>vertices;
    cout<<" Ingrese el número de aristas: ";
    cin>>aristas;

    vector<infograf>grafo(aristas);

    cout<<" Ingrese las aritas (nodo nodo peso): \n";
    for(int i = 0; i < aristas; i++)
    {
        cout<<" Arista ["<<i+1<<"]: ";
        cin>>grafo[i].u>>grafo[i].v>>grafo[i].peso;
    }

    //ordenamos las aristas de mayor a menor peso
    sort(grafo.begin(), grafo.end(), comp);

    vector<infograf>respuesta; //vector para poner el camino de menor peso
    int total = 0;
    //parte de reverse delete
    for(auto &algo : grafo)
    {
        //en esta función se borra
        DSU dsu(vertices);

        //agrega de nuevo todas las aristas excepto esta
        for(auto &lo : respuesta)
            dsu.unite(lo.u, lo.v);

        //revisa si al eliminarla el grafo deja de ser conexo
        if(dsu.find(algo.u) != dsu.find(algo.v))
        {
            //si sí entonces lo agrega a la solución, ya que es un arista importante
            respuesta.push_back(algo);
            total+=algo.peso;
        }
    }

    cout<<"\n EL camino con menor peso es:\n";
    for(auto &a : respuesta)
    {
        cout<<a.u<<" "<<a.v<<" peso: "<<a.peso<<"\n";
    }
    cout<<"\n Con un peso de: "<<total;

    return 0;
}

/*
Ejemplos: son los mismos que los de kruskal para comprobar que los resultados son iguales
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
    El camino con menor peso es:
    1 3  peso: 8
    4 7  peso: 8
    6 8  peso: 9
    1 2  peso: 10
    5 6  peso: 10
    6 7  peso: 10
    1 4  peso: 12

    Con peso de: 67

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
    1 4  peso: 5
    3 5  peso: 5
    4 6  peso: 6
    1 2  peso: 7
    2 5  peso: 7
    5 7  peso: 9

    Con peso de: 39
*/