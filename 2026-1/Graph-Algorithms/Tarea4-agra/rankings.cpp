// david gutierrez
// codigo: 9019220
// complejidad:
// aca el golpe fuerte es el doble for que arma las relaciones entre todos los
// pares del ranking anterior, asi que se va en O(n^2). lo demas ya es leer
// cambios y hacer el topologico, entonces el total queda como O(n^2 + m).
// en memoria tambien toca guardar bastantes relaciones, asi que se siente como
// O(n^2).

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

inline long long codificar_par(int equipo_a, int equipo_b) {
    if (equipo_a > equipo_b) {
        swap(equipo_a, equipo_b);
    }

    return static_cast<long long>(equipo_a) * 200001 + equipo_b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numero_casos;
    cin >> numero_casos;

    while (numero_casos--) {
        int numero_equipos;
        cin >> numero_equipos;

        vector<int> ranking_anterior(numero_equipos + 1);
        for (int posicion = 1; posicion <= numero_equipos; posicion++) {
            cin >> ranking_anterior[posicion];
        }

        int numero_cambios;
        cin >> numero_cambios;

        unordered_set<long long> pares_invertidos;
        for (int i = 0; i < numero_cambios; i++) {
            int equipo_a, equipo_b;
            cin >> equipo_a >> equipo_b;
            pares_invertidos.insert(codificar_par(equipo_a, equipo_b));
        }

        vector<vector<int>> grafo(numero_equipos + 1);
        vector<int> grado_entrada(numero_equipos + 1, 0);

        for (int i = 1; i <= numero_equipos; i++) {
            for (int j = i + 1; j <= numero_equipos; j++) {
                int equipo_mejor = ranking_anterior[i];
                int equipo_peor = ranking_anterior[j];

                if (pares_invertidos.count(codificar_par(equipo_mejor, equipo_peor))) {
                    swap(equipo_mejor, equipo_peor);
                }

                grafo[equipo_mejor].push_back(equipo_peor);
                grado_entrada[equipo_peor]++;
            }
        }

        queue<int> cola_listos;
        for (int equipo = 1; equipo <= numero_equipos; equipo++) {
            if (grado_entrada[equipo] == 0) {
                cola_listos.push(equipo);
            }
        }

        vector<int> orden_final;
        vector<bool> posicion_dudosa(numero_equipos + 1, false);

        while (!cola_listos.empty()) {
            if (cola_listos.size() > 1) {
                queue<int> copia = cola_listos;

                while (!copia.empty()) {
                    posicion_dudosa[copia.front()] = true;
                    copia.pop();
                }
            }

            int equipo_actual = cola_listos.front();
            cola_listos.pop();
            orden_final.push_back(equipo_actual);

            for (int equipo_vecino : grafo[equipo_actual]) {
                grado_entrada[equipo_vecino]--;

                if (grado_entrada[equipo_vecino] == 0) {
                    cola_listos.push(equipo_vecino);
                }
            }
        }

        if (static_cast<int>(orden_final.size()) < numero_equipos) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        for (int i = 0; i < numero_equipos; i++) {
            if (i > 0) {
                cout << ' ';
            }

            if (posicion_dudosa[orden_final[i]]) {
                cout << '?';
            } else {
                cout << orden_final[i];
            }
        }

        cout << '\n';
    }

    return 0;
}
