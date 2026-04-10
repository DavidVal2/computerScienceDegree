//
// Created by david on 29/07/2025.
//

#include "Tienda.h"
#include <iostream>
using namespace std;

void Tienda::Tiendador() {
    int camionesA;
    int camionesB;
    int camiones34=0;
    int kgCebolla=0;
    int kgMango=0;
    int kgNaranja=0;
    int kgTomate=0;
    int kgPapa=0;
    int productos;
    int numKgs;

    cout << "Cuantos camiones tipo A llegan?: ";
    cin >> camionesA >> endl;
    cout << "Cuantos kilos de papa lleva?";
    cin >> kgPapa >> endl;
    cout << "Cuantos camiones tipo B llegan?: ";
    cin >> camionesB >> endl;
    for (int i = 0; camionesB; i++) {
        cout << "Cuantos productos llevan?: ";
        cin >> productos >> endl;
        if (productos == 2) {
            cout << "Cuantos kilos de Tomate lleva?";
            cin >> numKgs;
            kgTomate = kgTomate + numKgs;
            cout << "Cuantos kilos de Cebolla lleva?";
            cin >> numKgs;
            kgCebolla = kgCebolla + numKgs;
            }
        if (productos == 3) {
            cout << "Cuantos kilos de Tomate lleva?";
            cin >> numKgs;
            kgTomate = kgTomate + numKgs;
            cout << "Cuantos kilos de Cebolla lleva?";
            cin >> numKgs;
            kgCebolla = kgCebolla + numKgs;
            cout << "Cuantos kilos de Naranja lleva?";
            cin >> numKgs;
            kgNaranja = kgNaranja + numKgs;
            camiones34++;
        }
        if (productos == 4) {
            cout << "Cuantos kilos de Tomate lleva?";
            cin >> numKgs;
            kgTomate = kgTomate + numKgs;
            cout << "Cuantos kilos de Cebolla lleva?";
            cin >> numKgs;
            kgCebolla = kgCebolla + numKgs;
            cout << "Cuantos kilos de Naranja lleva?";
            cin >> numKgs;
            kgNaranja = kgNaranja + numKgs;
            cout << "Cuantos kilos de Mango lleva?";
            cin >> numKgs;
            kgMango = kgMango + numKgs;
            camiones34++;
        }
    }
    cout << "Hay en total" << camiones34 << "camiones de 3 y 4 productos" << endl;
    cout << "Hay en total" << camionesA << "camiones A" << endl;
    cout << "Hay en total" << kgCebolla << "de cebolla, " << kgMango << "kg de mango y" << kgNaranja << "kg de naranja"<< endl;


}
