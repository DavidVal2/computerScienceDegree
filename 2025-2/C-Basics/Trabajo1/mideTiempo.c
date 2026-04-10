#include <stdio.h>
#include <time.h>   // Para clock(), CLOCKS_PER_SEC

// Suma los números de 1 hasta n
long long sumarHastan(long long n) {
    long long suma = 0;
    for (long long i = 1; i <= n; i++) {
        suma += i;
    }
    return suma;
}

int main() {
    long long n = 1000000000;

    clock_t inicio, fin;
    double tiempo_usado;

    inicio = clock(); // Tomar tiempo inicial

    long long resultado = sumarHastan(n);

    fin = clock(); // Tomar tiempo final

    // Calcular tiempo en segundos
    tiempo_usado = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Resultado: %lld\n", resultado);
    printf("Tiempo de ejecucion: %.6f segundos\n", tiempo_usado);

    return 0;
}
