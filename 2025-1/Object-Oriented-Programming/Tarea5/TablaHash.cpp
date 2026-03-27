#include "TablaHash.h"
#include <iostream>
#include <cmath>
#include <iomanip>

TablaHash::TablaHash(int tam) : tamanio(tam), numElementos(0) {
    tabla.resize(tamanio);
}

// Función hash que combina varios métodos para mejor distribución
int TablaHash::funcionHash(const string& llave) const {
    if (llave.empty() || llave[0] != '@') {
        return 0;
    }

    unsigned long hash = 0;
    const int PRIMO = 31; // Número primo para multiplicación

    // Procesar cada carácter después del @
    for (size_t i = 1; i < llave.length(); i++) {
        // Método de multiplicación con número primo
        hash = hash * PRIMO + static_cast<unsigned char>(llave[i]);
    }

    // Aplicar método de división con el tamaño de la tabla
    return hash % tamanio;
}

bool TablaHash::insertar(const string& llave, const string& nombre, 
                         const string& cedula, double saldo) {
    // Validar que la llave comience con @
    if (llave.empty() || llave[0] != '@' || llave.length() > 15) {
        return false;
    }

    // Verificar que no exista
    if (existe(llave)) {
        return false;
    }

    // Calcular índice
    int indice = funcionHash(llave);

    // Crear usuario e insertar en la lista correspondiente
    Usuario nuevoUsuario(llave, nombre, cedula, saldo);
    tabla[indice].push_back(nuevoUsuario);
    numElementos++;

    return true;
}

Usuario* TablaHash::buscar(const string& llave) {
    int indice = funcionHash(llave);

    // Buscar en la lista encadenada
    for (auto& usuario : tabla[indice]) {
        if (usuario.getLlave() == llave) {
            return &usuario;
        }
    }

    return nullptr;
}

bool TablaHash::eliminar(const string& llave) {
    int indice = funcionHash(llave);

    // Buscar y eliminar de la lista
    for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
        if (it->getLlave() == llave) {
            tabla[indice].erase(it);
            numElementos--;
            return true;
        }
    }

    return false;
}

bool TablaHash::existe(const string& llave) const {
    int indice = funcionHash(llave);

    // Buscar en la lista
    for (const auto& usuario : tabla[indice]) {
        if (usuario.getLlave() == llave) {
            return true;
        }
    }

    return false;
}

bool TablaHash::consultarSaldo(const string& llave, double& saldo) {
    Usuario* usuario = buscar(llave);
    if (usuario != nullptr) {
        saldo = usuario->getSaldo();
        return true;
    }
    return false;
}

bool TablaHash::transferir(const string& llaveOrigen, const string& llaveDestino, 
                           double monto) {
    if (monto <= 0) {
        return false;
    }

    Usuario* origen = buscar(llaveOrigen);
    Usuario* destino = buscar(llaveDestino);

    if (origen == nullptr || destino == nullptr) {
        return false;
    }

    if (origen->getSaldo() < monto) {
        return false;
    }

    // Realizar la transferencia
    origen->retirar(monto);
    destino->depositar(monto);

    return true;
}

int TablaHash::getTamanio() const {
    return tamanio;
}

int TablaHash::getNumElementos() const {
    return numElementos;
}

double TablaHash::getFactorCarga() const {
    return static_cast<double>(numElementos) / tamanio;
}

void TablaHash::mostrarEstadisticas() const {
    cout << "\n=== ESTADÍSTICAS DE LA TABLA HASH ===\n";
    cout << "Tamaño de la tabla: " << tamanio << "\n";
    cout << "Número de elementos: " << numElementos << "\n";
    cout << "Factor de carga: " << fixed << setprecision(4) 
         << getFactorCarga() << "\n";

    // Calcular colisiones
    int posicionesUsadas = 0;
    int maxColisiones = 0;

    for (int i = 0; i < tamanio; i++) {
        int tamLista = tabla[i].size();
        if (tamLista > 0) {
            posicionesUsadas++;
            if (tamLista > maxColisiones) {
                maxColisiones = tamLista;
            }
        }
    }

    cout << "Posiciones utilizadas: " << posicionesUsadas << " de " 
         << tamanio << " (" << fixed << setprecision(2) 
         << (100.0 * posicionesUsadas / tamanio) << "%)\n";
    cout << "Máxima colisión en una posición: " << maxColisiones << "\n";
    cout << "=====================================\n";
}
