
#include <iostream>

#include "Arreglos.h"
#include "asterisco.h"
#include "numerizador.h"
#include "Tienda.h"
using namespace std;

    int main() {
        int opcion;

        do {
            cout << "--- MENU PRINCIPAL ---" << endl;
            cout << "1. Asterisco" << endl;
            cout << "2. Numeros" << endl;
            cout << "3. Tienda" << endl;
            cout << "4. Arreglos" << endl;
            cout << "5. Salir" << endl;
            cout << "Seleccione una opcion: " << endl;
            cin >> opcion;

            switch (opcion) {
                case 1:
                    void asterisco::dibujaLineas();
                    break;
                case 2:
                    void numerizador::juegoNumerizador();
                    break;
                case 3:
                    void Tienda::Tiendador();
                    break;
                case 4:
                    void Arreglos::arreglos();
                    break;
                case 5:
                    cout << "Saliendo del programa...\n";
                    break;
                default:
                    cout << "Opcion no valida. Intente de nuevo.\n";
            }

        } while (opcion != 5);

        return 0;
    }
