#ifndef TABLAHASH_H
#define TABLAHASH_H

#include "Usuario.h"
#include <vector>
#include <list>
using namespace std;

class TablaHash {
private:
    // Vector de listas (Chaining para manejo de colisiones)
    vector<list<Usuario>> tabla;
    int tamanio;
    int numElementos;

    // Función hash privada
    int funcionHash(const string& llave) const;

public:
    // Constructor
    TablaHash(int tamanio = 1009); // Número primo para mejor distribución

    // Operaciones básicas
    bool insertar(const string& llave, const string& nombre, 
                  const string& cedula, double saldo);
    Usuario* buscar(const string& llave);
    bool eliminar(const string& llave);
    bool existe(const string& llave) const;

    // Operaciones del sistema financiero
    bool consultarSaldo(const string& llave, double& saldo);
    bool transferir(const string& llaveOrigen, const string& llaveDestino, 
                    double monto);

    // Información de la tabla
    int getTamanio() const;
    int getNumElementos() const;
    double getFactorCarga() const;
    void mostrarEstadisticas() const;
};

#endif
