# Nombre: Julian Hurtado
# Codigo: 9024180
# Complejidad: O(|V| + |E|) tiempo y espacio — Tarjan SCC en una sola DFS
# Fuentes: https://www.w3schools.com/python/default.asp https://www.geeksforgeeks.org/python/difference-between-input-and-sys-stdin-readline/  
# IA para solucion de errores/guia  (como forward-edge y back-edge en la deteccion)
import sys

def tarjan_scc(adj_list):
    """
    Identifica SCCs usando el algoritmo de Tarjan (una sola DFS).
    Tiempo: O(|V| + |E|), Espacio: O(|V|)
    Retorna los ciclos en una lista de listas.
    """
    n = len(adj_list)
    index = 0
    stack = []
    on_stack = [False] * n
    indices = [-1] * n
    lowlinks = [-1] * n
    sccs = []
    back_edge_count = [0] * n
    is_cactus = True

    def strongconnect(v):
        nonlocal index
        nonlocal is_cactus
        indices[v] = lowlinks[v] = index
        index += 1
        stack.append(v)
        on_stack[v] = True

        for w in adj_list[v]:
            if indices[w] == -1:
                strongconnect(w)
                lowlinks[v] = min(lowlinks[v], lowlinks[w])
            elif on_stack[w]:
                if indices[w] < indices[v]:  # back-edge real
                    lowlinks[v] = min(lowlinks[v], indices[w])
                    back_edge_count[w] += 1
                else:  # forward-edge → no es cactus
                    is_cactus = False
            else:
                is_cactus = False  # cross/forward-edge → no es cactus

        if lowlinks[v] == indices[v]:
            component = []
            w = None
            while w != v:
                w = stack.pop()
                on_stack[w] = False
                component.append(w)
            sccs.append(component)

    for v in range(n):
        if indices[v] == -1:
            strongconnect(v)
    return sccs, back_edge_count, is_cactus


def check(sccs, back_edge_count, is_cactus):
    if len(sccs) > 1:
        print("NO")
    elif not is_cactus:
        print("NO")
    elif any(x > 1 for x in back_edge_count):
        print("NO")
    else:
        print("YES")


def main():
    sys.setrecursionlimit(100000)
    t = int(sys.stdin.readline().strip())
    while (t > 0):
        vertices = int(sys.stdin.readline().strip())
        edges = int(sys.stdin.readline().strip())
        conteo = 0
        graph = [[] for _ in range(vertices)]
        while (conteo < edges):
            u, v = map(int, sys.stdin.readline().strip().split())
            graph[u].append(v)
            conteo += 1
        sccs, back_edge_count, is_cactus = tarjan_scc(graph)
        check(sccs, back_edge_count, is_cactus)
        t -= 1


if __name__ == "__main__":
    main()
