/*
 * Complejidad del código:
 * - Sea N el número de personas y M el número de relaciones entrenador→persona.
 * - Construcción del grafo: O(N + M)
 * - Orden topológico (algoritmo de Kahn) para calcular generaciones: O(N + M)
 *   Cada nodo y arista se procesa exactamente una vez.
 * - Selección del mejor entrenador por generación: O(N)
 * - Complejidad total por caso de prueba: O(N + M)
 *
 * Idea central:
 *   gen[v] = 1 + max(gen[p]) para todos los p que entrenaron a v.
 *   Generación 0: entrenadores que nadie (registrado) entrenó.
 *   Solo participan en la selección quienes entrenaron al menos a una persona (esCoach[i] = true).
 */

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for(int caso = 1; caso <= T; caso++){

        int N, M;
        cin >> N >> M;

        unordered_map<string,int> indice;
        vector<string> nombre(N);
        vector<int> anio(N);

        for(int i = 0; i < N; i++){
            cin >> nombre[i] >> anio[i];
            indice[nombre[i]] = i;
        }

        // grafo[u] = lista de personas que u entrenó directamente
        vector<vector<int>> grafo(N);
        vector<int> gradoEntrada(N, 0);
        vector<int> cantEntrenados(N, 0); // cuántas personas entrenó cada uno
        vector<bool> esCoach(N, false);   // true si entrenó al menos a alguien

        for(int i = 0; i < M; i++){
            string A, B;
            cin >> A >> B;
            int u = indice[A];
            int v = indice[B];
            grafo[u].push_back(v);
            gradoEntrada[v]++;
            cantEntrenados[u]++;
            esCoach[u] = true;
        }

        // Algoritmo de Kahn para calcular generaciones en orden topológico
        // gen[v] = generación de v = 1 + máximo de gen de sus entrenadores
        queue<int> cola;
        vector<int> gen(N, 0);
        vector<int> maxGenPadre(N, -1); // máxima generación de los entrenadores de v
        vector<int> gradoCopia = gradoEntrada;

        for(int i = 0; i < N; i++){
            if(gradoCopia[i] == 0){
                gen[i] = 0;
                cola.push(i);
            }
        }

        while(!cola.empty()){
            int u = cola.front();
            cola.pop();

            for(int v : grafo[u]){
                // Actualizar la máxima generación de los entrenadores de v
                maxGenPadre[v] = max(maxGenPadre[v], gen[u]);
                gradoCopia[v]--;
                if(gradoCopia[v] == 0){
                    gen[v] = maxGenPadre[v] + 1;
                    cola.push(v);
                }
            }
        }

        // Encontrar la generación máxima entre los coaches
        int maxGen = 0;
        for(int i = 0; i < N; i++){
            if(esCoach[i]) maxGen = max(maxGen, gen[i]);
        }

        // Para cada generación, encontrar el mejor coach:
        // 1. Más jugadores entrenados
        // 2. En empate: año de nacimiento menor (más viejo)
        // 3. En empate: nombre lexicográficamente menor
        vector<int> mejor(maxGen + 1, -1);

        for(int i = 0; i < N; i++){
            if(!esCoach[i]) continue; // solo participan quienes entrenaron a alguien

            int g = gen[i];

            if(mejor[g] == -1){
                mejor[g] = i;
                continue;
            }

            int act = mejor[g];

            if(cantEntrenados[i] > cantEntrenados[act]){
                mejor[g] = i;
            } else if(cantEntrenados[i] == cantEntrenados[act]){
                if(anio[i] < anio[act]){
                    mejor[g] = i;
                } else if(anio[i] == anio[act] && nombre[i] < nombre[act]){
                    mejor[g] = i;
                }
            }
        }

        cout << "Scenario #" << caso << ":\n";
        for(int g = 0; g <= maxGen; g++){
            if(mejor[g] != -1)
                cout << "Generation " << g << ": " << nombre[mejor[g]] << "\n";
        }

        if(caso < T) cout << "\n";
    }

    return 0;
}