/*
 * Complejidad del código:
 * - Por cada consulta (nodo_inicio, TTL):
 *   Se hace un BFS limitado por TTL: cada nodo se visita a lo sumo una vez.
 *   En el peor caso se recorren todos los nodos y aristas: O(V + E).
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int NC;
    int numeroCaso = 1;

    while (cin >> NC && NC != 0) {
        map<int, vector<int>> grafo;
        set<int> todosLosNodos;

        for (int i = 0; i < NC; i++) {
            int u, v;
            cin >> u >> v;
            grafo[u].push_back(v);
            grafo[v].push_back(u);
            todosLosNodos.insert(u);
            todosLosNodos.insert(v);
        }

        int nodoInicio, TTL;
        while (cin >> nodoInicio >> TTL && (nodoInicio != 0 || TTL != 0)) {
            // El nodo de inicio siempre existe aunque no tenga conexiones
            todosLosNodos.insert(nodoInicio);
            int totalNodos = todosLosNodos.size();


            map<int, int> distancia;
            queue<int> cola;

            distancia[nodoInicio] = 0;
            cola.push(nodoInicio);

            while (!cola.empty()) {
                int actual = cola.front();
                cola.pop();

                int distActual = distancia[actual];

                // Solo reenviamos desde este nodo si aún le queda TTL
                if (distActual >= TTL) continue;

                for (int vecino : grafo[actual]) {
                    if (distancia.find(vecino) == distancia.end()) {
                        distancia[vecino] = distActual + 1;
                        cola.push(vecino);
                    }
                }
            }

            int alcanzables = distancia.size();
            int noAlcanzables = totalNodos - alcanzables;

            cout << "Case " << numeroCaso << ": "
                 << noAlcanzables << " nodes not reachable from node "
                 << nodoInicio << " with TTL = " << TTL << ".\n";
            numeroCaso++;
        }
    }

    return 0;
}