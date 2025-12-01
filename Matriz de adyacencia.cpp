/*
	MATRIZ DE ADYACENCIA 
    
    ESTRUCTURAS COMPUTACIONALES AVANZADAS (3 - A)
    Profesor Miguel Angel Meza de Luna

    Inregrantes:
        Anabel Romo Esparza
        Ariadna Vargas Medina
        Gaddiel Mohamed Pedroza Martínez
        Stephanie Paola Pérez Ramírez

    Propósito general:
        El código muestra la representacion de la matriz de adyacencia de un grafo.

    Complejidad del codigo:
        Opera en O(N^2) 
    
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Introduce el numero de vertices: ";
    cin >> n;

    int dirigido, ponderado;
    cout << "El grafo es dirigido? (1 = si, 0 = no): ";
    cin >> dirigido;
    cout << "El grafo es ponderado? (1 = si, 0 = no): ";
    cin >> ponderado;

    // Inicializacion
    vector<vector<int>> m(n, vector<int>(n, 0));

    cout << "\nIntroduce las aristas:\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = (dirigido ? 0 : i+1); j < n; j++) {

            if (i == j) continue;  // opcional

            int valor;
            if (ponderado)
                cout << "Peso de " << i+1 << " -> " << j+1 << " (0 si no hay): ";
            else
                cout << "Hay arista " << i+1 << " -> " << j+1 << "? (1/0): ";

            cin >> valor;
            m[i][j] = valor;

            // refleja la arista cuando no es un grafo dirigido
            if (!dirigido)
                m[j][i] = valor;
        }
    }

    cout << "\nMatriz de adyacencia:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << " ";
        cout << "\n";
    }

    return 0;
}


/* Tets de prueba

No dirigido:
Input:
3
0
0
1
1
0
Output: 
0 0 0
0 0 1
0 1 0

Dirigido:
Input:
3
1
0
1
0
0
1
9
Output:
0 1 0
0 0 1
0 0 0


Ponderado:
Input:
4
0
1
3
5
0
0
2
1
4
0
Output:
0 3 5 0
3 0 2 1
5 2 0 4
0 1 4 0


Dirigido y ponderado:
4
1
1
0
2
0
0
0
5
0
1
0
0
0
0
3
0
Output:
0 2 0 0
0 0 0 5
1 0 0 0
0 0 3 0







*/
