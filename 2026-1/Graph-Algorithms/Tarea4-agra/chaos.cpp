// david gutierrez
// codigo: 9019220
// complejidad:
// esto corre bastante bien porque casi todo va una vez por nodos y aristas.
// la parte pesada de verdad es el topo con las prioridades, entonces al final
// queda mas o menos en O((n + m) log n). en memoria tambien va en O(n + m).

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numero_casos;
    cin >> numero_casos;

    for (int caso_actual = 0; caso_actual < numero_casos; ++caso_actual) {
        int numero_personajes, numero_relaciones;
        cin >> numero_personajes >> numero_relaciones;

        vector<string> nombres(numero_personajes);
        vector<long long> influencias(numero_personajes);
        unordered_map<string, int> indice_de_nombre;
        indice_de_nombre.reserve(static_cast<size_t>(numero_personajes) * 2);
        indice_de_nombre.max_load_factor(0.7f);

        for (int i = 0; i < numero_personajes; ++i) {
            cin >> nombres[i] >> influencias[i];
            indice_de_nombre[nombres[i]] = i;
        }

        vector<vector<int>> grafo(numero_personajes);
        vector<vector<int>> grafo_invertido(numero_personajes);

        for (int i = 0; i < numero_relaciones; ++i) {
            string origen, destino;
            cin >> origen >> destino;

            int desde = indice_de_nombre[origen];
            int hacia = indice_de_nombre[destino];

            grafo[desde].push_back(hacia);
            grafo_invertido[hacia].push_back(desde);
        }

        vector<char> visitado(numero_personajes, 0);
        vector<int> posicion_arista(numero_personajes, 0);
        vector<int> orden_salida;
        orden_salida.reserve(numero_personajes);

        for (int nodo_inicial = 0; nodo_inicial < numero_personajes; ++nodo_inicial) {
            if (visitado[nodo_inicial]) {
                continue;
            }

            vector<int> pila;
            pila.push_back(nodo_inicial);
            visitado[nodo_inicial] = 1;

            while (!pila.empty()) {
                int nodo_actual = pila.back();

                if (posicion_arista[nodo_actual] < static_cast<int>(grafo[nodo_actual].size())) {
                    int siguiente_nodo = grafo[nodo_actual][posicion_arista[nodo_actual]++];

                    if (!visitado[siguiente_nodo]) {
                        visitado[siguiente_nodo] = 1;
                        pila.push_back(siguiente_nodo);
                    }
                } else {
                    pila.pop_back();
                    orden_salida.push_back(nodo_actual);
                }
            }
        }

        vector<int> componente_de(numero_personajes, -1);
        vector<int> representante_de_componente;
        representante_de_componente.reserve(numero_personajes);
        int numero_componentes = 0;

        for (int i = numero_personajes - 1; i >= 0; --i) {
            int nodo_inicial = orden_salida[i];

            if (componente_de[nodo_inicial] != -1) {
                continue;
            }

            vector<int> pila;
            vector<int> nodos_de_componente;
            pila.push_back(nodo_inicial);
            componente_de[nodo_inicial] = numero_componentes;

            while (!pila.empty()) {
                int nodo_actual = pila.back();
                pila.pop_back();
                nodos_de_componente.push_back(nodo_actual);

                for (int nodo_vecino : grafo_invertido[nodo_actual]) {
                    if (componente_de[nodo_vecino] == -1) {
                        componente_de[nodo_vecino] = numero_componentes;
                        pila.push_back(nodo_vecino);
                    }
                }
            }

            int representante = -1;
            int indice_cartman = -1;
            bool es_componente_de_un_solo_nodo = (nodos_de_componente.size() == 1);

            for (int nodo : nodos_de_componente) {
                if (nombres[nodo] == "Cartman") {
                    indice_cartman = nodo;
                    break;
                }
            }

            if (indice_cartman != -1) {
                representante = indice_cartman;
            } else {
                for (int nodo : nodos_de_componente) {
                    if (!es_componente_de_un_solo_nodo && nombres[nodo] == "Butters") {
                        continue;
                    }

                    if (
                        representante == -1 ||
                        influencias[nodo] > influencias[representante] ||
                        (influencias[nodo] == influencias[representante] && nombres[nodo] < nombres[representante])
                    ) {
                        representante = nodo;
                    }
                }
            }

            representante_de_componente.push_back(representante);
            ++numero_componentes;
        }

        vector<vector<int>> grafo_componentes(numero_componentes);
        vector<int> grado_entrada(numero_componentes, 0);

        for (int nodo_actual = 0; nodo_actual < numero_personajes; ++nodo_actual) {
            int componente_actual = componente_de[nodo_actual];

            for (int nodo_vecino : grafo[nodo_actual]) {
                int componente_vecina = componente_de[nodo_vecino];

                if (componente_actual != componente_vecina) {
                    grafo_componentes[componente_actual].push_back(componente_vecina);
                    ++grado_entrada[componente_vecina];
                }
            }
        }

        using NodoDeCola = pair<string, int>;
        priority_queue<NodoDeCola, vector<NodoDeCola>, greater<NodoDeCola>> cola_prioridad;

        for (int componente = 0; componente < numero_componentes; ++componente) {
            if (grado_entrada[componente] == 0) {
                cola_prioridad.push({nombres[representante_de_componente[componente]], componente});
            }
        }

        vector<string> respuesta;
        respuesta.reserve(numero_componentes);

        while (!cola_prioridad.empty()) {
            auto [nombre_representante, componente_actual] = cola_prioridad.top();
            cola_prioridad.pop();
            respuesta.push_back(nombre_representante);

            for (int componente_vecina : grafo_componentes[componente_actual]) {
                --grado_entrada[componente_vecina];

                if (grado_entrada[componente_vecina] == 0) {
                    cola_prioridad.push({
                        nombres[representante_de_componente[componente_vecina]],
                        componente_vecina
                    });
                }
            }
        }

        for (const string& nombre_representante : respuesta) {
            cout << nombre_representante << '\n';
        }

        if (caso_actual + 1 < numero_casos) {
            cout << '\n';
        }
    }

    return 0;
}
