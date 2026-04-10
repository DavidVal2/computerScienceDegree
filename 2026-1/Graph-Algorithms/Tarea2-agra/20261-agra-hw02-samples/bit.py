#!/usr/bin/env python3
import sys

# grilla global para guardar los 0s y 1s
grilla = []
resultado = []

# buffer para leer caracter por caracter del input
char_buf = []
char_idx = 0

# devuelve el proximo caracter valido ('0', '1', 'D')
def siguiente_char():
    global char_buf, char_idx
    while True:
        if char_idx < len(char_buf):
            c = char_buf[char_idx]
            char_idx += 1
            if c in ('0', '1', 'D'):
                return c
            # ignora saltos de linea y espacios
        else:
            return None  # se acabo el input

# B -> D: si la region es toda igual emite ese valor, si no emite 'D' y divide
def encode(r, c, nr, nc):
    primero = grilla[r][c]
    todo_igual = True
    for rr in range(r, r + nr):
        for cc in range(c, c + nc):
            if grilla[rr][cc] != primero:
                todo_igual = False
                break
        if not todo_igual:
            break

    if todo_igual:
        resultado.append(primero)
        return

    resultado.append('D')

    if nr == 1:
        lc = (nc + 1) // 2
        encode(r, c, 1, lc)
        encode(r, c + lc, 1, nc - lc)
    elif nc == 1:
        tr = (nr + 1) // 2
        encode(r, c, tr, 1)
        encode(r + tr, c, nr - tr, 1)
    else:
        tr = (nr + 1) // 2
        lc = (nc + 1) // 2
        encode(r, c, tr, lc)
        encode(r, c + lc, tr, nc - lc)
        encode(r + tr, c, nr - tr, lc)
        encode(r + tr, c + lc, nr - tr, nc - lc)

# D -> B: lee el siguiente caracter y rellena la grilla
def decode(r, c, nr, nc):
    ch = siguiente_char()

    if ch in ('0', '1'):
        for rr in range(r, r + nr):
            for cc in range(c, c + nc):
                grilla[rr][cc] = ch
        return

    # ch == 'D', hay que dividir y seguir leyendo
    if nr == 1:
        lc = (nc + 1) // 2
        decode(r, c, 1, lc)
        decode(r, c + lc, 1, nc - lc)
    elif nc == 1:
        tr = (nr + 1) // 2
        decode(r, c, tr, 1)
        decode(r + tr, c, nr - tr, 1)
    else:
        tr = (nr + 1) // 2
        lc = (nc + 1) // 2
        decode(r, c, tr, lc)
        decode(r, c + lc, tr, nc - lc)
        decode(r + tr, c, nr - tr, lc)
        decode(r + tr, c + lc, nr - tr, nc - lc)

# imprime la cadena en lineas de 50 caracteres
def imprimir(s):
    for i in range(0, len(s), 50):
        print(s[i:i+50])

def main():
    global grilla, resultado, char_buf, char_idx

    datos = sys.stdin.read()
    char_buf = list(datos)
    char_idx = 0

    while True:
        # buscar el proximo formato valido ('B', 'D', o '#')
        fmt = None
        while char_idx < len(char_buf):
            c = char_buf[char_idx]
            char_idx += 1
            if c in ('B', 'D', '#'):
                fmt = c
                break

        if fmt is None or fmt == '#':
            break

        # leer filas y columnas
        nums = []
        num_actual = ""
        while len(nums) < 2:
            if char_idx >= len(char_buf):
                break
            c = char_buf[char_idx]
            char_idx += 1
            if c.isdigit():
                num_actual += c
            elif num_actual:
                nums.append(int(num_actual))
                num_actual = ""
        if num_actual:
            nums.append(int(num_actual))

        filas, cols = nums[0], nums[1]

        # reiniciar grilla para este caso
        grilla = [['' for _ in range(cols)] for _ in range(filas)]

        if fmt == 'B':
            # leer filas*cols caracteres validos y llenar grilla
            leidos = 0
            total = filas * cols
            while leidos < total:
                c = siguiente_char()
                grilla[leidos // cols][leidos % cols] = c
                leidos += 1

            resultado = []
            encode(0, 0, filas, cols)

            print(f"D {filas:4d} {cols:4d}")
            imprimir("".join(resultado))

        else:
            # leer la cadena D caracter por caracter durante el decode
            decode(0, 0, filas, cols)

            salida = ""
            for r in range(filas):
                for c in range(cols):
                    salida += grilla[r][c]

            print(f"B {filas:4d} {cols:4d}")
            imprimir(salida)

if __name__ == "__main__":
    # Python tiene limite de recursion, lo subimos por si acaso
    sys.setrecursionlimit(300000)
    main()