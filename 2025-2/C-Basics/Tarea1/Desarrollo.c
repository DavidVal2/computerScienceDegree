#include <stdio.h>  
#include <stdlib.h> 

void punto1();
void punto2();

int main() {
    int opcion;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Ejecutar Punto 1\n");
        printf("2. Ejecutar Punto 2\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                punto1();
                break;
            case 2:
                punto2();
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }

        system("pause"); // Pausa para Windows
    } while(opcion != 3);

    return 0;
}

// FUNCIONES

void punto1() {
    printf("\nEjecutando Punto 1...\n");
    int numeros[] = {5, 12, 7, 9, 3, 15, 22, 8, 1, 6};
    int numeroBuscado = 5;
    int n = sizeof(numeros) / sizeof(numeros[0]);
    int encontrado = 0;
    for (int i = 0;  i < n; i++) {
        if (i == numeroBuscado) {
            encontrado = 1;
        }
    };
    if (encontrado == 1) {
        printf("\nEl numero SI esta en el vector\n");
    } 
    else {
        printf("\nEl numero NO esta en el vector\n");
    };
}

void punto2() {
    printf("\nEjecutando Punto 2...\n");
    int numeros1[] = {5, 12, 7, 9, 3, 15, 22, 8, 1, 6};
    int numeros2[] = {5, 13, 8, 9, 4, 16, 23, 8, 2, 7};
    int numeroBuscado = 5;
    int n = sizeof(numeros1) / sizeof(numeros1[0]);
    int estaEn1 = 0;
    int estaEn2 = 0;

    for (int i = 0; i < n; i++) {
        if (numeros1[i] == numeroBuscado) {
            estaEn1 = 1;
        }
        if (numeros2[i] == numeroBuscado) {
            estaEn2 = 1;
        }
    }

    if (estaEn1 && estaEn2) {
        printf("El numero SI esta en ambos vectores\n");
    } else {
        printf("El numero NO esta en ambos vectores\n");
    }
}
