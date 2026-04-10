# Complejidad del código:
# - Por cada caso de prueba con N reportes, V ciudades y E rutas:
#   - Construye el grafo: O(E), y recorre todas las ciudades en los reportes.
#   - BFS desde S hasta T: O(V + E), cada ciudad y arista se procesa una vez.
#   - Reconstruye el camino: O(V), siguiendo los padres desde T hasta S.
# - Complejidad total por caso: O(V + E).

import sys
from collections import deque, defaultdict

def resolver(data, idx):
    # Leer N (número de reportes)
    N = int(data[idx].strip())
    idx += 1

    # Construir el grafo como lista de adyacencia (no dirigido)
    grafo = defaultdict(set)

    for _ in range(N):
        partes = data[idx].strip().split()
        idx += 1
        if len(partes) < 2:
            continue
        origen = partes[0]
        for destino in partes[1:]:
            grafo[origen].add(destino)
            grafo[destino].add(origen)

    # Leer S y T (ciudades de origen y destino)
    linea_final = data[idx].strip().split()
    idx += 1
    S, T = linea_final[0], linea_final[1]

    # Caso trivial: ya está en el destino
    if S == T:
        print(S)
        return idx

    # BFS para encontrar el camino más corto (menos ciudades)
    # visitado[ciudad] = ciudad desde la que llegamos (padre en el árbol BFS)
    visitado = {S: None}
    cola = deque([S])

    encontrado = False
    while cola:
        ciudad = cola.popleft()
        if ciudad == T:
            encontrado = True
            break
        for vecino in grafo[ciudad]:
            if vecino not in visitado:
                visitado[vecino] = ciudad
                cola.append(vecino)

    if not encontrado:
        print("no route found")
        return idx

    # Reconstruir el camino siguiendo los padres desde T hasta S
    camino = []
    actual = T
    while actual is not None:
        camino.append(actual)
        actual = visitado[actual]

    camino.reverse()
    print(' '.join(camino))
    return idx

# Leer toda la entrada y procesar todos los casos
data = sys.stdin.read().split('\n')
idx = 0
while idx < len(data):
    # Saltar líneas vacías entre casos
    while idx < len(data) and data[idx].strip() == '':
        idx += 1
    if idx >= len(data):
        break
    idx = resolver(data, idx)