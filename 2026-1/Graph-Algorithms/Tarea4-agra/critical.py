# david gutierrez
# codigo: 9019220
# complejidad:
# aca casi todo sale del dfs de tarjan, o sea que se recorre cada nodo y cada
# conexion una vez. por eso queda en O(n + m). en memoria tambien se va por
# O(n + m) por el grafo y los arreglos auxiliares.

import sys

input = sys.stdin.readline


def tarjan_articulaciones(numeroEstaciones, graph):
    tiempo = 0

    disc = [-1] * numeroEstaciones
    low = [-1] * numeroEstaciones
    padre = [-1] * numeroEstaciones

    es_critico = [False] * numeroEstaciones
    nodos_criticos = []

    graph_parts = []
    parte = -1

    def dfs(estacionActual):
        nonlocal tiempo

        disc[estacionActual] = tiempo
        low[estacionActual] = tiempo
        tiempo += 1

        tam_actual = 1
        hijos = 0

        for estacionVecina in graph[estacionActual]:
            if disc[estacionVecina] == -1:
                padre[estacionVecina] = estacionActual
                hijos += 1

                tam_actual += dfs(estacionVecina)

                low[estacionActual] = min(low[estacionActual], low[estacionVecina])

                if padre[estacionActual] != -1 and low[estacionVecina] >= disc[estacionActual]:
                    if not es_critico[estacionActual]:
                        es_critico[estacionActual] = True
                        nodos_criticos.append((estacionActual, parte))

            elif estacionVecina != padre[estacionActual]:
                low[estacionActual] = min(low[estacionActual], disc[estacionVecina])

        if padre[estacionActual] == -1 and hijos > 1:
            if not es_critico[estacionActual]:
                es_critico[estacionActual] = True
                nodos_criticos.append((estacionActual, parte))

        return tam_actual

    for i in range(numeroEstaciones):
        if disc[i] == -1:
            parte += 1
            tam_componente = dfs(i)
            graph_parts.append(tam_componente)

    return nodos_criticos, graph_parts


def calculadora_de_mas_critico(nodos_criticos, graph_parts, lista_de_capacidades):
    if not nodos_criticos:
        return None

    max_tam = max(graph_parts[parte] for _, parte in nodos_criticos)

    mayor_capacidad = -1
    mas_critico = -1

    for nodo, parte_nodo in nodos_criticos:
        if graph_parts[parte_nodo] != max_tam:
            continue

        capacidad = lista_de_capacidades[nodo]

        if capacidad > mayor_capacidad:
            mayor_capacidad = capacidad
            mas_critico = nodo
        elif capacidad == mayor_capacidad and nodo < mas_critico:
            mas_critico = nodo

    return mas_critico, max_tam - 1


def main():
    lineas = sys.stdin.read().strip().splitlines()
    i = 0

    while i < len(lineas):
        numeroEstaciones, numeroConexiones = map(int, lineas[i].split())
        i += 1

        lista_de_capacidades = list(map(int, lineas[i].split()))
        i += 1

        graph = [[] for _ in range(numeroEstaciones)]

        for _ in range(numeroConexiones):
            estacionesU, estacionesV = map(int, lineas[i].split())
            i += 1
            graph[estacionesU].append(estacionesV)
            graph[estacionesV].append(estacionesU)

        nodos_criticos, graph_parts = tarjan_articulaciones(numeroEstaciones, graph)

        resultado = calculadora_de_mas_critico(
            nodos_criticos, graph_parts, lista_de_capacidades
        )

        if resultado is None:
            print(-1)
        else:
            print(*resultado)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        sys.stdin = open(sys.argv[1], "r")
    main()
