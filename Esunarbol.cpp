#include <iostream>
#include <vector>
using namespace std;

bool tieneCiclo(int nodo, int padre, vector<vector<int>>& grafo, vector<bool>& visitado) {
    visitado[nodo] = true;
    for (int vecino : grafo[nodo]) {
        if (!visitado[vecino]) {
            if (tieneCiclo(vecino, nodo, grafo, visitado)) return true;
        } else if (vecino != padre) {
            return true; 
        }
    }
    return false;
}

bool esConexo(vector<bool>& visitado) {
    for (bool v : visitado) // v representa cada valor de visitado, es decir agarra los valores de true o false de visitado de 0 a visitadi.size()
        if (!v) return false;
    return true;
}

int main() {
    int n, a;
    cout << "Numero de nodos: \n";
    cin >> n;
    cout << "Numero de aristas: \n";
    cin >> a;
    vector<bool> visitado(n, false);
    vector<vector<int>> grafo(n); //lista de adyacencia 
    if (a!=n-1) {
        cout << "El numero de aristas es diferente a n-1 por lo tanto no es un arbol\n"; 
        return 0;
    }
    cout << "Ingresa cada arista como: nodo_inicial nodo_final :\n";
    for (int i = 0; i < a; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        grafo[u].push_back(v);
        grafo[v].push_back(u);
    }
    if (tieneCiclo(0, -1, grafo, visitado)) {
        cout << " El grafo no es un arbol ya que contiene un ciclo.\n";
    } else if (!esConexo(visitado)) {
        cout << " El grafo no es un arbol ya que es disconexo.\n";
    } else {
        cout << " El grafo es un arbol.\n";
    }

    return 0;
}
