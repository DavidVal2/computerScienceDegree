# COMPLEJIDAD: O(M * log(V) * N*K)
# donde M = casos de prueba, N*K = baterias por caso,
# log(V) = busqueda binaria sobre el valor maximo de diferencia,
# N*K = costo de funciona_con_d en el peor caso
import sys

def funciona_con_d(diferencias, n, k, d):
    # si el primer par ya no cumple, no hay caso
    if diferencias[0] > d:
        return False
    
    anterior = 0
    maquinas = 1  # ya conté la primera maquina
    total = len(diferencias)
    
    while maquinas < n:
        start = anterior + 2
        end = min(2 * maquinas * k, total)
        encontrado = False
        
        # busco el primer par que cumpla la diferencia
        for i in range(start, end + 1):
            if diferencias[i] <= d:
                anterior = i
                maquinas += 1
                encontrado = True
                break
        
        if not encontrado:
            return False
    
    return True

def resolver(iterador):
    resultados = []
    try:
        while True:
            n = next(iterador)
            k = next(iterador)
            cantidad = 2 * n * k
            baterias = [next(iterador) for _ in range(cantidad)]
            baterias.sort()
            
            # precalculo diferencias entre pares consecutivos
            # para no restarlas en cada paso de la busqueda binaria
            diferencias = [baterias[i+1] - baterias[i] for i in range(cantidad - 1)]
            
            minimo = 0
            maximo = baterias[-1] - baterias[0]
            
            # busqueda binaria sobre d
            while minimo < maximo:
                medio = (minimo + maximo) // 2
                if funciona_con_d(diferencias, n, k, medio):
                    maximo = medio
                else:
                    minimo = medio + 1
            
            resultados.append(str(minimo))
    except StopIteration:
        pass
    
    return resultados

def main():
    datos = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(datos)
    salida = resolver(it)
    sys.stdout.write("\n".join(salida) + ("\n" if salida else ""))

if __name__ == "__main__":
    main()