#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
    int valor;
    struct nodo* sig;
} Nodo;


Nodo* crearNodo(int numero) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    nuevoNodo->valor = numero;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

void listaInsertarInicio(Nodo** head, int numero) {
    Nodo* nuevoNodo = crearNodo(numero);
    nuevoNodo->sig = *head;
    *head = nuevoNodo;
}


void imprimirLista(Nodo* head) {
    Nodo* actual = head;
    while (actual != NULL) {
        printf("%d -> ", actual->valor);
        actual = actual->sig;
    }
    printf("NULL\n");
}


void listaEliminarMenoresOIguales(Nodo** head, int limite) {
    Nodo* actual = *head;
    Nodo* anterior = NULL;

    while (actual != NULL) {
        if (actual->valor <= limite) {
            // Eliminar nodo
            Nodo* temp = actual;
            if (anterior == NULL) {
                // Caso: el nodo esta en el head
                *head = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            actual = actual->sig;
            free(temp);
        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
}

int main() {
    Nodo* lista = NULL;
    int cantidad, numero, limite;

    printf("Cuantos numeros desea ingresar en la lista? ");
    scanf("%d", &cantidad);

    for (int i = 0; i < cantidad; i++) {
        printf("Ingrese un numero entre -100 y 100: ");
        scanf("%d", &numero);
        listaInsertarInicio(&lista, numero);
    }

    printf("\nLista original:\n");
    imprimirLista(lista);

    printf("\nIngrese el valor limite: ");
    scanf("%d", &limite);

    listaEliminarMenoresOIguales(&lista, limite);

    printf("\nLista despues de eliminar valores <= %d:\n", limite);
    imprimirLista(lista);

    return 0;
}
