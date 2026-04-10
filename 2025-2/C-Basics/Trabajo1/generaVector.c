#include <stdio.h>
#include <time.h>

// Constante
int obtenerNumeroC(int numeros[], int n) {
    return numeros[n - 1];
}

// Lineal
int obtenerNumeroL(int numeros[], int n) {
    int ultimoNumeroL = 0;
    for (int i = 0; i < n; i++) {
        ultimoNumeroL = numeros[i];
    }
    return ultimoNumeroL;
}

int main() {
    int numeros[100000];
    for (int i = 0; i < 10000; i++) {
        numeros[i] = i+5;
    }

    int n = sizeof(numeros) / sizeof(numeros[0]);
    clock_t inicio, fin;
    double tiempo;

        // Lineal
    inicio = clock();
    int ultimoL = obtenerNumeroL(numeros, n);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Ultimo numero (O(n)): %d\n", ultimoL);
    printf("Tiempo O(n): %f segundos\n", tiempo);


    // Constante
    inicio = clock();
    int ultimoC = obtenerNumeroC(numeros, n);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Ultimo numero (O(1)): %d\n", ultimoC);
    printf("Tiempo O(1): %f segundos\n", tiempo);

    return 0;
}