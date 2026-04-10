/*
 * Complejidad del código:
 * - Para cada caso de prueba, se simula la exploración del jugador con BFS.
 * - Cada casilla se encola y procesa como máximo una vez: O(W * H).
 * - Complejidad total por caso de prueba: O(W * H).
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int W, H;

    while (cin >> W >> H) {
        vector<string> mapa(H);
        for (int i = 0; i < H; i++) {
            cin >> mapa[i];
        }

        // Direcciones: arriba, abajo, izquierda, derecha
        int df[] = {-1, 1, 0, 0};
        int dc[] = { 0, 0,-1, 1};

        // Función auxiliar: ¿siente corriente en (fila, col)?
        // Siente corriente si algún vecino es trampa 'T'
        auto sienteCorriente = [&](int fila, int col) {
            for (int d = 0; d < 4; d++) {
                int nf = fila + df[d];
                int nc = col  + dc[d];
                if (nf >= 0 && nf < H && nc >= 0 && nc < W) {
                    if (mapa[nf][nc] == 'T') return true;
                }
            }
            return false;
        };

        // Encontrar posición inicial del jugador
        int inicioFila = 0, inicioCol = 0;
        for (int fila = 0; fila < H; fila++) {
            for (int col = 0; col < W; col++) {
                if (mapa[fila][col] == 'P') {
                    inicioFila = fila;
                    inicioCol  = col;
                }
            }
        }

        // BFS simulando el conocimiento del jugador
        // El jugador solo puede moverse a casillas que sabe con certeza que NO son trampa.
        // Una casilla se confirma como "no trampa" cuando algún vecino fue visitado
        //

        vector<vector<bool>> visitado(H, vector<bool>(W, false));
        queue<pair<int,int>> cola;

        cola.push({inicioFila, inicioCol});
        visitado[inicioFila][inicioCol] = true;

        int oroRecogido = 0;

        while (!cola.empty()) {
            auto [fila, col] = cola.front();
            cola.pop();

            // Recoger oro si hay
            if (mapa[fila][col] == 'G') {
                oroRecogido++;
            }

            // Solo expandimos vecinos si en esta casilla NO se siente corriente
            // (si se siente corriente, no sabemos cuál vecino es trampa)
            if (sienteCorriente(fila, col)) continue;

            // Sin corriente: todos los vecinos son seguros (no son trampa)
            // Podemos visitarlos si no son pared y no han sido visitados
            for (int d = 0; d < 4; d++) {
                int nf = fila + df[d];
                int nc = col  + dc[d];

                if (nf < 0 || nf >= H || nc < 0 || nc >= W) continue;
                if (visitado[nf][nc]) continue;
                if (mapa[nf][nc] == '#' || mapa[nf][nc] == 'T') continue;

                visitado[nf][nc] = true;
                cola.push({nf, nc});
            }
        }

        cout << oroRecogido << "\n";
    }

    return 0;
}