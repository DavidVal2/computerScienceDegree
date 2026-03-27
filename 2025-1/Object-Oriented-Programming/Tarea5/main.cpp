#include <iostream>
#include <string>
#include <limits>
#include "TablaHash.h"

using namespace std;

// Funciones auxiliares
void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

void mostrarMenu() {
    cout << "\n╔════════════════════════════════════════════════╗\n";
    cout << "║     SISTEMA FINANCIERO BRE-B                  ║\n";
    cout << "║     Gestión de Usuarios con Tabla Hash        ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";
    cout << "\n1. Registrar usuario\n";
    cout << "2. Consultar saldo de usuario\n";
    cout << "3. Transferir saldo entre usuarios\n";
    cout << "4. Retirar usuario del sistema\n";
    cout << "5. Verificar existencia de usuario\n";
    cout << "6. Mostrar estadísticas de la tabla\n";
    cout << "7. Salir\n";
    cout << "\nSeleccione una opción: ";
}

void registrarUsuario(TablaHash& tabla) {
    cout << "\n=== REGISTRAR USUARIO ===\n";

    string llave, nombre, cedula;
    double saldo;

    cout << "Ingrese llave (debe iniciar con @, máx 15 caracteres): ";
    cin >> llave;
    limpiarBuffer();

    // Validar formato de llave
    if (llave.empty() || llave[0] != '@' || llave.length() > 15) {
        cout << "\n[ERROR] Llave inválida. Debe iniciar con @ y tener máximo 15 caracteres.\n";
        pausar();
        return;
    }

    // Verificar que no exista
    if (tabla.existe(llave)) {
        cout << "\n[ERROR] Ya existe un usuario con esa llave.\n";
        pausar();
        return;
    }

    cout << "Ingrese nombre completo: ";
    getline(cin, nombre);

    cout << "Ingrese número de cédula: ";
    cin >> cedula;

    cout << "Ingrese saldo inicial: $";
    cin >> saldo;
    limpiarBuffer();

    if (saldo < 0) {
        cout << "\n[ERROR] El saldo no puede ser negativo.\n";
        pausar();
        return;
    }

    if (tabla.insertar(llave, nombre, cedula, saldo)) {
        cout << "\n[ÉXITO] Usuario registrado correctamente.\n";
    } else {
        cout << "\n[ERROR] No se pudo registrar el usuario.\n";
    }

    pausar();
}

void consultarSaldo(TablaHash& tabla) {
    cout << "\n=== CONSULTAR SALDO ===\n";

    string llave;
    cout << "Ingrese la llave del usuario: ";
    cin >> llave;
    limpiarBuffer();

    Usuario* usuario = tabla.buscar(llave);

    if (usuario != nullptr) {
        cout << "\n" << usuario->toString() << "\n";
    } else {
        cout << "\n[ERROR] Usuario no encontrado.\n";
    }

    pausar();
}

void transferirSaldo(TablaHash& tabla) {
    cout << "\n=== TRANSFERIR SALDO ===\n";

    string llaveOrigen, llaveDestino;
    double monto;

    cout << "Ingrese llave del usuario origen: ";
    cin >> llaveOrigen;

    cout << "Ingrese llave del usuario destino: ";
    cin >> llaveDestino;

    cout << "Ingrese monto a transferir: $";
    cin >> monto;
    limpiarBuffer();

    if (llaveOrigen == llaveDestino) {
        cout << "\n[ERROR] No puede transferir a la misma cuenta.\n";
        pausar();
        return;
    }

    // Mostrar saldos antes
    Usuario* origen = tabla.buscar(llaveOrigen);
    Usuario* destino = tabla.buscar(llaveDestino);

    if (origen == nullptr) {
        cout << "\n[ERROR] Usuario origen no encontrado.\n";
        pausar();
        return;
    }

    if (destino == nullptr) {
        cout << "\n[ERROR] Usuario destino no encontrado.\n";
        pausar();
        return;
    }

    cout << "\nSaldo origen antes: $" << origen->getSaldo() << "\n";
    cout << "Saldo destino antes: $" << destino->getSaldo() << "\n";

    if (tabla.transferir(llaveOrigen, llaveDestino, monto)) {
        cout << "\n[ÉXITO] Transferencia realizada correctamente.\n";
        cout << "\nSaldo origen después: $" << origen->getSaldo() << "\n";
        cout << "Saldo destino después: $" << destino->getSaldo() << "\n";
    } else {
        cout << "\n[ERROR] No se pudo realizar la transferencia. ";
        cout << "Verifique que el saldo sea suficiente.\n";
    }

    pausar();
}

void retirarUsuario(TablaHash& tabla) {
    cout << "\n=== RETIRAR USUARIO ===\n";

    string llave;
    cout << "Ingrese la llave del usuario a eliminar: ";
    cin >> llave;
    limpiarBuffer();

    // Mostrar información antes de eliminar
    Usuario* usuario = tabla.buscar(llave);
    if (usuario != nullptr) {
        cout << "\n" << usuario->toString() << "\n";
        cout << "\n¿Está seguro de eliminar este usuario? (S/N): ";
        char confirmar;
        cin >> confirmar;
        limpiarBuffer();

        if (confirmar == 'S' || confirmar == 's') {
            if (tabla.eliminar(llave)) {
                cout << "\n[ÉXITO] Usuario eliminado correctamente.\n";
            } else {
                cout << "\n[ERROR] No se pudo eliminar el usuario.\n";
            }
        } else {
            cout << "\nOperación cancelada.\n";
        }
    } else {
        cout << "\n[ERROR] Usuario no encontrado.\n";
    }

    pausar();
}

void verificarExistencia(TablaHash& tabla) {
    cout << "\n=== VERIFICAR EXISTENCIA ===\n";

    string llave;
    cout << "Ingrese la llave a verificar: ";
    cin >> llave;
    limpiarBuffer();

    if (tabla.existe(llave)) {
        cout << "\n[INFO] La llave " << llave << " existe en el sistema.\n";
        Usuario* usuario = tabla.buscar(llave);
        if (usuario != nullptr) {
            cout << "\n" << usuario->toString() << "\n";
        }
    } else {
        cout << "\n[INFO] La llave " << llave << " NO existe en el sistema.\n";
    }

    pausar();
}

int main() {
    // Crear tabla hash con tamaño primo (1009 es adecuado para 1000 usuarios)
    TablaHash sistemaFinanciero(1009);

    int opcion;
    bool continuar = true;

    // Agregar algunos usuarios de prueba
    sistemaFinanciero.insertar("@juan123", "Juan Pérez", "1098765432", 100000.0);
    sistemaFinanciero.insertar("@maria9596", "María García", "1097654321", 250000.0);
    sistemaFinanciero.insertar("@pedro2024", "Pedro Martínez", "1096543210", 50000.0);

    cout << "\n[INFO] Sistema inicializado con 3 usuarios de prueba:\n";
    cout << "  - @juan123 (Juan Pérez) - Saldo: $100,000\n";
    cout << "  - @maria9596 (María García) - Saldo: $250,000\n";
    cout << "  - @pedro2024 (Pedro Martínez) - Saldo: $50,000\n";
    pausar();

    while (continuar) {
        mostrarMenu();
        cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                registrarUsuario(sistemaFinanciero);
                break;
            case 2:
                consultarSaldo(sistemaFinanciero);
                break;
            case 3:
                transferirSaldo(sistemaFinanciero);
                break;
            case 4:
                retirarUsuario(sistemaFinanciero);
                break;
            case 5:
                verificarExistencia(sistemaFinanciero);
                break;
            case 6:
                sistemaFinanciero.mostrarEstadisticas();
                pausar();
                break;
            case 7:
                cout << "\n¡Gracias por usar el Sistema Financiero BRE-B!\n";
                continuar = false;
                break;
            default:
                cout << "\n[ERROR] Opción inválida. Intente nuevamente.\n";
                pausar();
        }
    }

    return 0;
}
