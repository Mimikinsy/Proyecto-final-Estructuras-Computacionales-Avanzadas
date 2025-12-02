/*
	LISTA DE ADYASCENCIA
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez
        Anabel Romo Esparza
        Ariadna Vargas Medina

    Propósito general:
        Almacenar un grafo en una lista de adyascencia y mostrarla de igual manera. 
    Funciona con grafos dirigidos, no dirigidos, ponderados y no ponderados

    Complejidad del codigo:
        O(n)
    
*/

#include <iostream>
#include <vector>
#include <locale> //esta la uso para poner acentos y usar la ñ

using namespace std;

void menu()
{
    //primero se pide que ingrese los datos del hgráfo
    int vertices, aristas;
    cout<<" Ingrese el número de vértices: ";
    cin>>vertices;
    cout<<" Ingrese el número de aristas: ";
    cin>>aristas;
    
    //aquí se especifíca si es dirigido, ponderado, etc.
    bool dirigido, ponderado;
    cout<<" El grafo es dirigido (1), o no dirigido (0): ";
    cin>>dirigido;
    cout<<" EL gráfo es ponerado (1), o no ponderado (0): ";
    cin>>ponderado;
    
    //aquí pediremos las conexiones
    vector<pair<int,int>> conexiones[vertices+1];
    int x, y, peso;
    cout<<"\n Ingrese el nodo de origen y el nodo de destino";
    if(ponderado)
    cout<<" y peso";
    cout<<"\n";
    for (int i = 1; i <= aristas; i++)
    {
        cout<<" Arista ["<<i<< "]: ";
        if(!ponderado) //verificar si no es ponderado
        {
            cin>>x>>y;
            conexiones[x].push_back({y,1});
            if(!dirigido) //si no es dirigido guarda la conexion en ambos nodos
            {
                conexiones[y].push_back({x,1});
            }
        }
        else //si es ponderado
        {
            int p; //para el peso
            cin>>x>>y>>p;
            conexiones[x].push_back({y,p});
            if(!dirigido) //si no es dirigido guarda la conexion en ambos nodos
            {
                conexiones[y].push_back({x,p});
            }
        }
    }

    //ahora lo imprimimos
    cout<<"\n lista de adyacencia:\n";
    for(int i = 1; i <= vertices; i++)
    {
        cout<<i<<": ";
        if(!ponderado)
        for(auto u:conexiones[i])
        {
            cout<<" "<<u.first; //aqui si no es ponderado ignora el peso
        }
        else
        for(auto u:conexiones[i])
        {
            cout<<" ("<<u.first<<","<<u.second<<")"; //aquí si imprime el peso
        }

        cout<<"\n";
    }
}

int main()
{
    setlocale(LC_ALL,"");
    menu();
    return 0;
}

/*
Ejemplos
* grafo no dirigido ni ponderado
    Entrada:
    4
    4
    0
    0
    1 2
    1 3
    1 4
    2 3

    Salida esperada:
    1: 2 3 4
    2: 1 3
    3: 1 2
    4: 1

* Grafo dirigido y no ponderado
    Entrada:
    5
    5
    1
    0
    1 2
    2 4
    2 3
    3 4
    3 5

    Salida esperada:
   1: 2
   2: 4 3
   3: 4 5
   4:
   5:

* Grafo pondeorado no dirigido
    Entrada:
    3
    2
    0
    1
    1 2 10
    2 3 1
    Salida:
    1: (2,10)
    2: (1,10) (3,1)
    3: (2,1)

* Grafo ponderado dirigido
    Entrada:
    4
    4
    1
    1
    1 2 8
    1 4 3
    2 3 7
    2 4 9
    
    Salida:
    1: (2,8) (4,3)
    2: (3,7) (4,9)
    3:
    4:
*/
