```c
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


void listaInsertarOrdenadamente(Nodo** head, int numero) {
    Nodo* nuevoNodo = crearNodo(numero);

    // nuevo numero mayor o igual que el primero
    if (*head == NULL || numero >= (*head)->valor) {
        nuevoNodo->sig = *head;
        *head = nuevoNodo;
        return;
    }

    // Buscar posicion
    Nodo* actual = *head;
    while (actual->sig != NULL && actual->sig->valor > numero) {
        actual = actual->sig;
    }

    // Insertar el nuevo nodo en la posicion encontrada
    nuevoNodo->sig = actual->sig;
    actual->sig = nuevoNodo;
}


void imprimirLista(Nodo* head) {
    Nodo* actual = head;
    while (actual != NULL) {
        printf("%d -> ", actual->valor);
        actual = actual->sig;
    }
    printf("NULL\n");
}


int main() {
    Nodo* lista = NULL; 

    listaInsertarOrdenadamente(&lista, 10);
    listaInsertarOrdenadamente(&lista, 50);
    listaInsertarOrdenadamente(&lista, -20);
    listaInsertarOrdenadamente(&lista, 30);
    listaInsertarOrdenadamente(&lista, 50); // repetido, igual entra

    printf("Lista ordenada (mayor a menor):\n");
    imprimirLista(lista);

    return 0;
}
```
