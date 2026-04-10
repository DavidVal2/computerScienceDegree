#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long tripletas(int A[], int n, int T) {
    long c = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (A[i] + A[j] + A[k] == T) {
                    c++;
                }
            }
        }
    }
    return c;
}

void prueba(int n, int T) {
    int *A = (int *)malloc(n * sizeof(int));
    if (A == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        return;
    }

    // Llenar arreglo con valores aleatorios
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // valores entre 0 y 99
    }

    clock_t inicio, fin;
    double tiempo;

    inicio = clock();
    long resultado = tripletas(A, n, T);
    fin = clock();

    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("n = %d → Tripletas encontradas: %ld | Tiempo: %.4f segundos\n",
           n, resultado, tiempo);

    free(A);
}

int main(void) {
    srand(time(NULL));

    int T = 50; // número objetivo

    printf("=== PRUEBAS DE TRIPLETAS ===\n");

    prueba(10000, T);     // Prueba 1
    prueba(100000, T);    // Prueba 2
    prueba(500000, T);    // Prueba 3

    return 0;
}
