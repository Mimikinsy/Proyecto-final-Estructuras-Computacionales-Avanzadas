/*
	EXPANCIÓN MÍNIMA CON KRUSKAL
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    *Integrantes:
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez
        Anabel Romo Esparza
        Ariadna Vargas Medina

    * Propósito general:
        Realizar un programa que mediante el algoritmo de Kruscal encuentre 
    el árbol de expansión mínima en un grafo conexo y ponderado, es decir, el 
    conjunto de aristas que conecte todos los vértices con el menor costo posible.
        Kruskal es un algoritmo que toma las aristas de peso más bajo hasta unir 
    todos los vértices y con union-find checa que no haya ciclos.

    * IMPORTANTE:
        Este algoritmo solo se puede hacer en grafos ponderados y no dirijidos:
        Debido a qu eel objetivo es encontrar el camino con menor peso, en el caso de
    los grafos no ponderados no tendría sentido usarlo, ya que no hay peso en ningún 
    arista por lo tanto todos los caminos son optimos.
        En el caso de gráfos dirigidos no es posible emplearlo, ya que más bien se emplearían 
    otros algoritmos como "el algoritmo de Edmonds".

    Complejidad del codigo:
        O(E log V)
    
*/
#include <bits/stdc++.h>
#include <locale>
using namespace std;


vector<int> parent, rango; //estos vectores se declaran aquí para poder usarlas más comodo en las funciones

int findSet(int x) { // devuelve al padre de un conjunto en que está x
    if (x == parent[x]) return x; //si x es su propio parde
    return parent[x] = findSet(parent[x]); //busca recursivamente al padre de x de forma recursiva
}

void unionSet(int a, int b) { //aquí se unirán los conjuntos
    a = findSet(a); //obtenemos los representantes
    b = findSet(b);

    if (a != b) { //verifique que no estén ya en el mismo conjunto para ni hacer ciclo
        if (rango[a] < rango[b]) swap(a, b); //se buca que el rango a sea siempre mayor al rango b
        parent[b] = a; //hace que a sea padre de b para unir los conjuntos
        if (rango[a] == rango[b]) rango[a]++;//si ambos tiene el mismo rango se aumenta el rango de a
    }
}

struct Arista { //esto son como usar pair pero de la froma en que venía en la página (lo usan en los vectores)
    int u, v, peso; 
};

bool comp(Arista a, Arista b) { //compara para el sort
    return a.peso < b.peso; //si la comdicion se cumple devuelve verdadero
}

int main() {
    setlocale(LC_ALL, ""); //se usa con la libreria locale
    
    // pide informacion del grafo
    int vertice, aristas;
    cout << "Número de vértices: ";
    cin >> vertice;
    cout << "Número de aristas: ";
    cin >> aristas;

    vector<Arista> grafo(aristas); //aquí usamos Arista para poner los parametros u, v, peso del struct

    cout<<"Ingresa nodo, nodo , peso:\n";
    for (int i = 0; i < aristas; i++) {
        cout<<"arista ["<<i<<"]: ";
        cin>>grafo[i].u>>grafo[i].v>>grafo[i].peso;
    }

    //resize sirve para modifircar(o en este caso establecer) el tamaño del vector
    parent.resize(vertice + 1); //este vector servirá para ver los padres de cada nodo
    rango.resize(vertice + 1, 0); //

    iota(parent.begin(), parent.end(), 0); //cada vértice empieza siendo su propio padre
    //esta finción me la dio copy para llenar el vector con números del 0 hasta el tamaño del vector :D

    sort(grafo.begin(), grafo.end(), comp); //ordena las aristas por peso de menor a mayor y usa la función comp

    vector<Arista> resultado; //para el resultado, agarra las aristas elegidas
    int total = 0; //para el peso del resultado


    for (auto &a : grafo) { //para recorrer las aristas
        if (findSet(a.u) != findSet(a.v)) {  //se fija que estén en el mismo conjunto para no hacer ciclo
            unionSet(a.u, a.v); //se unen los conjuntotos
            resultado.push_back(a); //aquí guarda la arista 
            total += a.peso; // y suma el peso
        }
    }

    //aqui solo imprime lso resultados
    cout << "\nArbol de expansión mínima:\n";
    for (auto &a : resultado) {
        cout << a.u << " " << a.v << "  peso: " << a.peso << "\n";
    }

    cout << "\nCon un peso de: " << total << endl;

    return 0;
}


/*
Ejeplos de entradas
    
* Grafo 1:
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
    Arbol de expansión mínima:
    1 3  peso: 8
    4 7  peso: 8
    6 8  peso: 9
    1 2  peso: 10
    5 6  peso: 10
    6 7  peso: 10
    1 4  peso: 12

    Con un peso de: 67

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
    Arbol de expansión mínima:
    1 4  peso: 5
    3 5  peso: 5
    4 6  peso: 6
    1 2  peso: 7
    2 5  peso: 7
    5 7  peso: 9

    Con un peso de: 39
*/