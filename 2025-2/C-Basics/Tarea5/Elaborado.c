#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define URL_SIZE 100


typedef struct {
    char sitios[MAX][URL_SIZE];
    int top;
} Pila;

// Funciones de pila
void inicializar(Pila *p) {
    p->top = -1;
}

int estaVacia(Pila *p) {
    return p->top == -1;
}

int estaLlena(Pila *p) {
    return p->top == MAX - 1;
}

void apilar(Pila *p, char *url) {
    if (!estaLlena(p)) {
        p->top++;
        strcpy(p->sitios[p->top], url);
    } else {
        printf("La pila esta llena, no se puede agregar mas sitios.\n");
    }
}

char* desapilar(Pila *p) {
    if (!estaVacia(p)) {
        return p->sitios[p->top--];
    } else {
        return NULL;
    }
}

char* verTope(Pila *p) {
    if (!estaVacia(p)) {
        return p->sitios[p->top];
    } else {
        return NULL;
    }
}

// Programa principal
int main() {
    Pila atras, adelante;
    inicializar(&atras);
    inicializar(&adelante);

    char sitioActual[URL_SIZE] = "Inicio";
    int opcion;
    char nuevoSitio[URL_SIZE];

    do {
        printf("\n=== HISTORIAL DEL NAVEGADOR ===\n");
        printf("Sitio actual: %s\n", sitioActual);
        printf("1. Abrir un sitio\n");
        printf("2. Ir hacia atras\n");
        printf("3. Ir hacia adelante\n");
        printf("4. Cerrar navegador\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del sitio: ");
                fgets(nuevoSitio, URL_SIZE, stdin);
                nuevoSitio[strcspn(nuevoSitio, "\n")] = '\0'; // quitar salto de linea
                apilar(&atras, sitioActual); // guardar el actual en la pila de atras
                strcpy(sitioActual, nuevoSitio);
                inicializar(&adelante); // al abrir un nuevo sitio, se borra la pila "adelante"
                break;

            case 2:
                if (!estaVacia(&atras)) {
                    apilar(&adelante, sitioActual);
                    strcpy(sitioActual, desapilar(&atras));
                } else {
                    printf("No hay sitios anteriores.\n");
                }
                break;

            case 3:
                if (!estaVacia(&adelante)) {
                    apilar(&atras, sitioActual);
                    strcpy(sitioActual, desapilar(&adelante));
                } else {
                    printf("No hay sitios adelante.\n");
                }
                break;

            case 4:
                printf("Cerrando el navegador...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 4);

    return 0;
}

/*
================== EXPLICACION =============

1️⃣ Estructura elegida: PILAS
   - Simula el comportamiento del historial de un navegador, ultimo en llegar primero en salir.
   - Es mas facil de implementar que otras opciones.

2️⃣ Complejidad Big O:
   - Abrir un sitio: O(1)
   - Ir hacia atras: O(1)
   - Ir hacia adelante: O(1)
   - Cerrar navegador (liberar todo): O(n)

   */


