# COMPLEJIDAD: O(T * (100 * N)) = O(T * N)
# donde T = casos de prueba, N = cantidad de pies
# los 100 pasos de busqueda binaria son constantes

import math
import sys

def resolver():
    datos = sys.stdin.read().split()
    idx = 0
    T = int(datos[idx]); idx += 1
    
    for _ in range(T):
        N, F = int(datos[idx]), int(datos[idx+1]); idx += 2
        radios = [int(datos[idx+i]) for i in range(N)]; idx += N
        
        # personas = amigos + yo
        personas = F + 1
        
        # precalculo las areas para no recalcularlas en cada paso
        # de la busqueda binaria
        areas = [math.pi * r * r for r in radios]
        
        minimo, maximo = 0.0, max(areas)
        
        for _ in range(100):
            medio = (minimo + maximo) / 2
            if medio == 0:
                maximo = medio
                continue
            total = sum(int(a / medio) for a in areas)
            if total >= personas:
                minimo = medio
            else:
                maximo = medio
        
        print(f"{minimo:.4f}")

resolver()