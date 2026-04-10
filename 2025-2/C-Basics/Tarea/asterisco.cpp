//
// Created by david on 28/07/2025.
//

#include "asterisco.h"
#include <iostream>
using namespace std;

void dibujaLineas() {
    int numero;
    int cantidadLineas;
    do {
        cout << "Introduce el numero: ";
        cin >> numero;
        if (numero < 1) {
            break;
        }
        if (numero <=15) {
            int linea =0;
            do {
                cout << numero;
                for (int i = 0; i < numero; i++) {
                    cout << "*";
                }
                cout << numero << endl;
                linea++;
                cantidadLineas++;

            }while (linea < 2);
        }

    }   while (cantidadLineas < 20);
}


