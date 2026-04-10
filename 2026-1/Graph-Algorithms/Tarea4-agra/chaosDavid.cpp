#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--) {

        int n, m;
        cin >> n >> m;

        // Mapeo nombre -> id
        map<string, int> id;

        // Lista para recuperar nombres luego (opcional pero útil)
        vector<string> nombres(n);

        // Leer nombres
        for (int i = 0; i < n; i++) {
            cin >> nombres[i];
            id[nombres[i]] = i;
        }

        // Grafo dirigido
        vector<vector<int>> grafo(n);

        // Leer aristas
        for (int i = 0; i < m; i++) {
            string a, b;
            cin >> a >> b;

            int u = id[a];
            int v = id[b];

            grafo[u].push_back(v);
        }

        // 🔥 Hasta aquí tienes TODO listo para Tarjan

    }

    return 0;
}