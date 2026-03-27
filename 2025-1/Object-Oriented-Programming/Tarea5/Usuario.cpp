#include "Usuario.h"
#include <sstream>
#include <iomanip>

Usuario::Usuario() : llave(""), nombreCompleto(""), cedula(""), saldo(0.0) {}

Usuario::Usuario(string llave, string nombre, string cedula, double saldo) 
    : llave(llave), nombreCompleto(nombre), cedula(cedula), saldo(saldo) {}

string Usuario::getLlave() const {
    return llave;
}

string Usuario::getNombreCompleto() const {
    return nombreCompleto;
}

string Usuario::getCedula() const {
    return cedula;
}

double Usuario::getSaldo() const {
    return saldo;
}

void Usuario::setSaldo(double nuevoSaldo) {
    saldo = nuevoSaldo;
}

bool Usuario::retirar(double monto) {
    if (monto > 0 && monto <= saldo) {
        saldo -= monto;
        return true;
    }
    return false;
}

void Usuario::depositar(double monto) {
    if (monto > 0) {
        saldo += monto;
    }
}

string Usuario::toString() const {
    ostringstream oss;
    oss << fixed << setprecision(2);
    oss << "Usuario: " << llave << "\n"
        << "Nombre: " << nombreCompleto << "\n"
        << "Cédula: " << cedula << "\n"
        << "Saldo: $" << saldo;
    return oss.str();
}
