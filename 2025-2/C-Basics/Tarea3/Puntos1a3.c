#include <stdio.h>  
#include <stdlib.h> 

void punto1() {
    int numeros[] = {5, 12, 7, 9, 3, 15, 22, 8, 1, 6};

    int n = sizeof(numeros) / sizeof(numeros[0]);
    
       

                // Lineal
                int mayorL = numeros[0];
                int menorL = numeros[0];
                for (int i = 0; i < n; i++) {
                    if (numeros[i]>mayorL) {
                    mayorL = numeros[i];
                    }
                    if (numeros[i]<menorL) {
                    menorL = numeros[i];
                    }
                }
                printf("Mayor numero: %d\n", mayorL);
                printf("Menor numero: %f\n", menorL);
                

};


void punto2(){
    int numeros[] = {5, 12, 7, 9, 3, 15, 22, 8, 1, 6};

    int n = sizeof(numeros) / sizeof(numeros[0]);
    int mitad = n/2;
    int suma;
    
    for (int i = 0; i < mitad; i++) {
        suma += numeros[i];
    };
    if (suma>100){
        for (int j = mitad; j < n; j++){
            numeros[j] = 0;
        }
    }
    else if (suma<100){
        for (int j = mitad; j < n; j++){
            numeros[j] = 1;
    }
};
};
void punto3(){
    int numeros1[] = {5, 12, 7, 9, 3, 15, 22, 8, 1, 6};
    int numeros2[] = {6, 1, 8, 22, 15, 3, 9, 7, 12, 5};

    int n = sizeof(numeros1) / sizeof(numeros1[0]);
    int terminado = 0 ;
    
    for (int i = 0; i < n; i++) {
        if (numeros1[i] != numeros2[n-1-i]){
            printf("No son iguales");
            terminado= 1;
            break;
    };
    };
    if (terminado = 0) {
        printf("Son iguales");
    }

};



int main() {
    int opcion;
    int finalizar = 0;

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Ejecutar Punto 1\n");
        printf("2. Ejecutar Punto 2\n");
        printf("3. Ejecutar Punto 3\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                punto1();
                finalizar = 1;
            case 2:
                punto2();
                finalizar = 1;
            case 3:
                punto3();
                finalizar = 1;
            case 4:
                printf("Saliendo...\n");
                finalizar = 1;
            default:
                printf("Opcion no valida.\n");
        }

        system("pause"); // Pausa para Windows
    } while(finalizar != 1);

    return 0;
}