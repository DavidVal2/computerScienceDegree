#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
private:
    string llave;           // Identificador con @
    string nombreCompleto;
    string cedula;
    double saldo;

public:
    // Constructores
    Usuario();
    Usuario(string llave, string nombre, string cedula, double saldo);

    // Getters
    string getLlave() const;
    string getNombreCompleto() const;
    string getCedula() const;
    double getSaldo() const;

    // Setters
    void setSaldo(double nuevoSaldo);

    // Operaciones
    bool retirar(double monto);
    void depositar(double monto);

    // Para mostrar información
    string toString() const;
};

#endif
