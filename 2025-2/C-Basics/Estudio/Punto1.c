#include <stdio.h>
#include <string.h>
struct Nodo {
    int dato;               // valor del nodo
    struct Nodo* siguiente; // puntero al siguiente nodo
};

void insertarInicio(struct Nodo** cabeza, int valor) {
    struct Nodo* nuevo = malloc(sizeof(struct Nodo)); // reserva memoria
    nuevo->dato = valor;
    nuevo->siguiente = *cabeza; // apunta al viejo primero
    *cabeza = nuevo;            // ahora el nuevo es la cabeza
}

void imprimirLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

void liberarLista(struct Nodo* cabeza) {
    struct Nodo* temp;
    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}

int contarCaracter(struct Nodo* cabeza, char caracter, char cadena[]) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cabeza->dato == caracter) {
            i++;
        }
    }
}

int main() {
    char cadena[] = "abacabad";
    struct Nodo* lista = NULL;

    // Insertar caracteres en la lista
    for (int i = 0; cadena[i] != '\0'; i++) {
        insertarInicio(&lista, cadena[i]);
    }

    // Imprimir la lista
    imprimirLista(lista);

    // Contar ocurrencias de un carácter
    char caracter = 'a';
    int ocurrencias = contarCaracter(lista, caracter);
    printf("El carácter '%c' aparece %d veces.\n", caracter, ocurrencias);

    // Liberar la lista
    liberarLista(lista);

    return 0;
}
    printf("%c\n", cadena[7]);
    return 0;
}