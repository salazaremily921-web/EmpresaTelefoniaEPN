#include "suspension.h"
#include "clientes.h"
#include "facturas.h"
#include <iostream>

using namespace std;

void verificarSuspensionAutomatica() {
    leerClientes();
    leerFacturas();

    bool cambios = false;

    for(int i = 0; i < totalClientes; i++) {
        bool tienePendiente = false;

        for(int j = 0; j < totalFacturas; j++) {
            if(facturas[j][1] == clientes[i][3] && facturas[j][7] == "Pendiente") {
                tienePendiente = true;
                break;
            }
        }

        if(tienePendiente && clientes[i][8] == "Activo") {
            clientes[i][8] = "Suspendido";
            cambios = true;
        }

        if(!tienePendiente && clientes[i][8] == "Suspendido") {
            clientes[i][8] = "Activo";
            cambios = true;
        }
    }

    if(cambios) {
        guardarClientes();
        cout << "Estados de lineas actualizados correctamente\n";
    } else {
        cout << "No se realizaron cambios\n";
    }
}

void menuSuspension() {
    int opcion;
    do {
        cout << "\nMenu Suspension de lineas\n";
        cout << "1. Ejecutar suspension automatica\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: verificarSuspensionAutomatica(); break;
        }
    } while(opcion != 0);
}

