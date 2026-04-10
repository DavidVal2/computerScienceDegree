# david gutierrez
# codigo: 9019220
# complejidad:
# la mayor parte del trabajo es recorrer el grafo para puentes, componentes y
# el arbol comprimido, asi que eso es lineal: O(n + m). al final se ordena la
# respuesta, entonces siendo estrictos queda como O(n + m + k log k), y en el
# peor caso se puede pensar como O(n + m + n log n).

import sys


def resolver_caso(numero_nodos, numero_aristas, energias, aristas, nodo_inicial):
    grafo = [[] for _ in range(numero_nodos + 1)]

    for indice_arista, (nodo_u, nodo_v) in enumerate(aristas):
        grafo[nodo_u].append((nodo_v, indice_arista))
        grafo[nodo_v].append((nodo_u, indice_arista))

    tiempo_entrada = [0] * (numero_nodos + 1)
    low = [0] * (numero_nodos + 1)
    es_puente = [False] * numero_aristas
    tiempo = 0

    for raiz in range(1, numero_nodos + 1):
        if tiempo_entrada[raiz] != 0:
            continue

        pila = [(raiz, -1, -1, 0)]

        while pila:
            nodo_actual, padre, arista_padre, siguiente_posicion = pila.pop()

            if siguiente_posicion == 0 and tiempo_entrada[nodo_actual] == 0:
                tiempo += 1
                tiempo_entrada[nodo_actual] = tiempo
                low[nodo_actual] = tiempo

            if siguiente_posicion < len(grafo[nodo_actual]):
                nodo_vecino, indice_arista = grafo[nodo_actual][siguiente_posicion]
                pila.append((nodo_actual, padre, arista_padre, siguiente_posicion + 1))

                if indice_arista == arista_padre:
                    continue

                if tiempo_entrada[nodo_vecino] == 0:
                    pila.append((nodo_vecino, nodo_actual, indice_arista, 0))
                elif tiempo_entrada[nodo_vecino] < tiempo_entrada[nodo_actual]:
                    low[nodo_actual] = min(low[nodo_actual], tiempo_entrada[nodo_vecino])

            elif padre != -1:
                if low[nodo_actual] > tiempo_entrada[padre]:
                    es_puente[arista_padre] = True

                low[padre] = min(low[padre], low[nodo_actual])

    componente_de = [-1] * (numero_nodos + 1)
    energia_por_componente = []

    for nodo_actual in range(1, numero_nodos + 1):
        if componente_de[nodo_actual] != -1:
            continue

        indice_componente = len(energia_por_componente)
        energia_total = 0
        pila = [nodo_actual]
        componente_de[nodo_actual] = indice_componente

        while pila:
            nodo = pila.pop()
            energia_total += energias[nodo]

            for nodo_vecino, indice_arista in grafo[nodo]:
                if es_puente[indice_arista] or componente_de[nodo_vecino] != -1:
                    continue

                componente_de[nodo_vecino] = indice_componente
                pila.append(nodo_vecino)

        energia_por_componente.append(energia_total)

    arbol_componentes = [[] for _ in range(len(energia_por_componente))]

    for indice_arista, (nodo_u, nodo_v) in enumerate(aristas):
        if not es_puente[indice_arista]:
            continue

        componente_u = componente_de[nodo_u]
        componente_v = componente_de[nodo_v]
        arbol_componentes[componente_u].append(componente_v)
        arbol_componentes[componente_v].append(componente_u)

    componente_inicial = componente_de[nodo_inicial]
    componente_alcanzable = [False] * len(energia_por_componente)
    componente_alcanzable[componente_inicial] = True
    pila = [componente_inicial]

    while pila:
        componente_actual = pila.pop()
        energia_actual = energia_por_componente[componente_actual]

        for componente_vecina in arbol_componentes[componente_actual]:
            if (
                componente_alcanzable[componente_vecina] or
                energia_por_componente[componente_vecina] <= energia_actual
            ):
                continue

            componente_alcanzable[componente_vecina] = True
            pila.append(componente_vecina)

    respuesta = [
        nodo
        for nodo in range(1, numero_nodos + 1)
        if componente_alcanzable[componente_de[nodo]]
    ]

    respuesta.sort(
        key=lambda nodo: (
            energia_por_componente[componente_de[nodo]],
            energias[nodo],
            nodo
        )
    )

    return respuesta


def main():
    datos = list(map(int, sys.stdin.buffer.read().split()))
    indice = 0
    salida = []

    while indice < len(datos):
        numero_nodos = datos[indice]
        numero_aristas = datos[indice + 1]
        indice += 2

        energias = [0] + datos[indice:indice + numero_nodos]
        indice += numero_nodos

        aristas = []
        for _ in range(numero_aristas):
            nodo_u = datos[indice]
            nodo_v = datos[indice + 1]
            indice += 2
            aristas.append((nodo_u, nodo_v))

        nodo_inicial = datos[indice]
        indice += 1

        respuesta = resolver_caso(
            numero_nodos, numero_aristas, energias, aristas, nodo_inicial
        )
        salida.append(" ".join(map(str, respuesta)))

    sys.stdout.write("\n".join(salida))


if __name__ == "__main__":
    main()
