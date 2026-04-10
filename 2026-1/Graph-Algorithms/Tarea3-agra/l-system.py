# Complejidad del código:
# - Complejidad total por caso: O(UMBRAL * P + ciclo * (P + N) * L),
#   donde ciclo es el período del ciclo (muy pequeño en la práctica).

import sys

def resolver(prod_a, prod_b, omega, z):
    L = len(z)
    if L == 0:
        return "YES"
    
    prod = {'a': prod_a, 'b': prod_b}
    UMBRAL = 4000
    
    # Fase 1: simulación directa mientras la cadena sea corta
    cadena = omega
    for _ in range(500):
        if z in cadena:
            return "YES"
        if len(cadena) > UMBRAL:
            break
        cadena = ''.join(prod[c] for c in cadena)
    
    if z in cadena:
        return "YES"
    
    if L == 1:
        return "NO"
    
    BORDE = L - 1
    
    pref = {'a': 'a'[:BORDE], 'b': 'b'[:BORDE]}
    suf  = {'a': 'a'[-BORDE:], 'b': 'b'[-BORDE:]}
    lon  = {'a': 1, 'b': 1}
    
    def verificar():
        """Verifica si z aparece en alguna unión entre chars consecutivos,
           tanto en las producciones como en omega."""
        # En las uniones internas de las producciones (cubre z dentro de cualquier expansión)
        for x in ['a', 'b']:
            p = prod[x]
            for i in range(len(p) - 1):
                union = suf[p[i]] + pref[p[i + 1]]
                if z in union:
                    return True
        # En las uniones entre chars consecutivos de omega
        for i in range(len(omega) - 1):
            union = suf[omega[i]] + pref[omega[i + 1]]
            if z in union:
                return True
        return False
    
    # Usar conjunto de estados vistos para detectar ciclos
    estados_vistos = set()
    
    for _ in range(10000):
        estado = (pref['a'], pref['b'], suf['a'], suf['b'])
        
        # Si este estado ya fue procesado, no estamos en un ciclo 
        if estado in estados_vistos:
            return "NO"
        estados_vistos.add(estado)
        
        if verificar():
            return "YES"
        
        # Calcular nuevos 
        nuevo_pref = {}
        nuevo_suf  = {}
        nuevo_lon  = {}
        
        for x in ['a', 'b']:
            p = prod[x]
            
            
            np = ""
            for c in p:
                necesito = BORDE - len(np)
                if necesito <= 0:
                    break
                tomar = min(necesito, lon[c])
                np += pref[c][:tomar]
            nuevo_pref[x] = np[:BORDE]
            
            
            ns = ""
            for c in reversed(p):
                necesito = BORDE - len(ns)
                if necesito <= 0:
                    break
                tomar = min(necesito, lon[c])
                ns = suf[c][-tomar:] + ns
            nuevo_suf[x] = ns[-BORDE:]
            
            # Longitud capped
            nl = sum(lon[c] for c in p)
            nuevo_lon[x] = min(nl, BORDE + 1)
        
        pref = nuevo_pref
        suf  = nuevo_suf
        lon  = nuevo_lon
    
    return "NO"

lineas = sys.stdin.read().splitlines()
i = 0
resultados = []
while i < len(lineas):
    while i < len(lineas) and lineas[i].strip() == '':
        i += 1
    if i + 3 >= len(lineas):
        break
    prod_a = lineas[i].strip()
    prod_b = lineas[i + 1].strip()
    omega  = lineas[i + 2].strip()
    z      = lineas[i + 3].strip()
    i += 4
    if prod_a and prod_b and omega and z:
        resultados.append(resolver(prod_a, prod_b, omega, z))

print('\n'.join(resultados))