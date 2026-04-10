/*
 *
 * B -> D: recursion que verifica si una region es toda igual.
 *         Si si, emite ese valor. Si no, emite 'D' y divide.
 *
 * D -> B: recursion que lee el siguiente caracter valido ('0','1','D')
 *         del input y rellena la grilla.
 *
 * COMPLEJIDAD: O(R*C) donde R=filas, C=columnas
 */

#include <bits/stdc++.h>
using namespace std;

char grilla[505][505];
string resultado;

// buffer para leer caracteres uno por uno
string bufer;
int pos;

// devuelve el proximo caracter valido ('0', '1', 'D')
char siguiente_char()
{
    while (true)
    {
        if (pos < (int)bufer.size())
        {
            char c = bufer[pos++];
            if (c == '0' || c == '1' || c == 'D')
                return c;
            // ignora saltos de linea y espacios
        }
        else
        {
            // leer mas caracteres del input
            char tmp[300005];
            if (scanf("%s", tmp) != 1)
                return 0;
            bufer = tmp;
            pos = 0;
        }
    }
}

// B -> D
void encode(int f, int c, int nf, int nc)
{
    char primero = grilla[f][c];
    bool todo_igual = true;
    for (int ff = f; ff < f + nf && todo_igual; ff++)
        for (int cc = c; cc < c + nc && todo_igual; cc++)
            if (grilla[ff][cc] != primero)
                todo_igual = false;

    if (todo_igual)
    {
        resultado += primero;
        return;
    }

    resultado += 'D';

    if (nf == 1)
    {
        int mitad_c = (nc + 1) / 2;
        encode(f, c, 1, mitad_c);
        encode(f, c + mitad_c, 1, nc - mitad_c);
    }
    else if (nc == 1)
    {
        int mitad_f = (nf + 1) / 2;
        encode(f, c, mitad_f, 1);
        encode(f + mitad_f, c, nf - mitad_f, 1);
    }
    else
    {
        int mitad_f = (nf + 1) / 2;
        int mitad_c = (nc + 1) / 2;
        encode(f, c, mitad_f, mitad_c);
        encode(f, c + mitad_c, mitad_f, nc - mitad_c);
        encode(f + mitad_f, c, nf - mitad_f, mitad_c);
        encode(f + mitad_f, c + mitad_c, nf - mitad_f, nc - mitad_c);
    }
}

// D -> B
void decode(int f, int c, int nf, int nc)
{
    char ch = siguiente_char();

    if (ch == '0' || ch == '1')
    {
        for (int ff = f; ff < f + nf; ff++)
            for (int cc = c; cc < c + nc; cc++)
                grilla[ff][cc] = ch;
        return;
    }

    // ch == 'D', dividir y seguir leyendo
    if (nf == 1)
    {
        int mitad_c = (nc + 1) / 2;
        decode(f, c, 1, mitad_c);
        decode(f, c + mitad_c, 1, nc - mitad_c);
    }
    else if (nc == 1)
    {
        int mitad_f = (nf + 1) / 2;
        decode(f, c, mitad_f, 1);
        decode(f + mitad_f, c, nf - mitad_f, 1);
    }
    else
    {
        int mitad_f = (nf + 1) / 2;
        int mitad_c = (nc + 1) / 2;
        decode(f, c, mitad_f, mitad_c);
        decode(f, c + mitad_c, mitad_f, nc - mitad_c);
        decode(f + mitad_f, c, nf - mitad_f, mitad_c);
        decode(f + mitad_f, c + mitad_c, nf - mitad_f, nc - mitad_c);
    }
}

// imprime la cadena en lineas de 50 caracteres
void imprimir(const string &s)
{
    for (int i = 0; i < (int)s.size(); i += 50)
        printf("%s\n", s.substr(i, 50).c_str());
}

int main()
{
    char fmt;

    while (scanf(" %c", &fmt) == 1 && fmt != '#')
    {
        int filas, cols;
        scanf("%d %d", &filas, &cols);

        // limpiar buffer para este caso :)
        bufer = "";
        pos = 0;

        if (fmt == 'B')
        {
            // leer filas*cols caracteres validos y llenar grilla
            int total = filas * cols;
            int leidos = 0;
            while (leidos < total)
            {
                char c = siguiente_char();
                grilla[leidos / cols][leidos % cols] = c;
                leidos++;
            }

            resultado = "";
            encode(0, 0, filas, cols);

            printf("D %4d %4d\n", filas, cols);
            imprimir(resultado);
        }
        else
        {
            // leer la cadena D caracter por caracter durante decode
            decode(0, 0, filas, cols);

            string salida = "";
            for (int f = 0; f < filas; f++)
                for (int c = 0; c < cols; c++)
                    salida += grilla[f][c];

            printf("B %4d %4d\n", filas, cols);
            imprimir(salida);
        }
    }

    return 0;
}