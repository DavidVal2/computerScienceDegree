//
// Created by david on 28/07/2025.
//

#include "numerizador.h"

#include <iostream>
using namespace std;

void numerizador::juegoNumerizador() {
    int numNumeros;
    int num71 = 0;
    int total = 0;

    cout << "Introduce el numero de numeros que quieres digitar: ";
    cin >> numNumeros;
    for (int i = 0; i < numNumeros; i++) {
        int numeroActual =0;
        cout << "Introduce el numero; ";
        cin >> numeroActual;
        if (numeroActual == 71) {
            if (num71 == 0) {
                cout << "Felicidades!" << endl;
                num71++;
            }
            else if (num71 == 1) {
                cout << "Felicidades! Ven por un premio mañana" << endl;
                num71++;
            }
            else {
                cout << "Sospechoso!" << endl;
            }
        }
        else {
            total += numeroActual;
        }


    }
    int promedio = total / numNumeros;
    cout << promedio << endl;

}
