#include <iostream>
#include <cstdlib>
#include <ctime>

#include "clientes.h"
#include "lineas.h"
#include "servicios.h"
#include "facturas.h"
#include "promociones.h"
#include "portabilidad.h"

using namespace std;

void menuCliente() {
    leerClientes();
    leerFacturas();
    leerPortabilidad();

    string cedula;
    cin.ignore();
    cout << "Ingrese su cedula: ";
    getline(cin, cedula);

    int pos = buscarClientePorCedula(cedula);
    if(pos == -1) {
        cout << "Cliente no registrado en la empresa\n";
        return;
    }

    int op;
    do {
        cout << "\nMenu Cliente\n";
        cout << "1.Ver datos personales\n";
        cout << "2.Ver facturas\n";
        cout << "3.Ver portabilidad\n";
        cout << "0.Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1:
                mostrarDatosCliente(pos);
                break;
            case 2:
                mostrarFacturasCliente(cedula);
                break;
            case 3:
                mostrarPortabilidadCliente(cedula);
                break;
        }
    } while(op != 0);
}

void menuTrabajador() {
    string clave;
    cin.ignore();
    cout << "Ingrese clave de trabajador: ";
    getline(cin, clave);

    if(clave != "1234") {
        cout << "Clave incorrecta\n";
        return;
    }

    int op;
    do {
        cout << "\nMenu Trabajador\n";
        cout << "1.Clientes\n";
        cout << "2.Lineas\n";
        cout << "3.Servicios\n";
        cout << "4.Facturas\n";
        cout << "5.Promociones\n";
        cout << "6.Portabilidad\n";
        cout << "0.Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1: menuClientes(); break;
            case 2: menuLineas(); break;
            case 3: menuServicios(); break;
            case 4: menuFacturas(); break;
            case 5: menuPromociones(); break;
            case 6: menuPortabilidad(); break;
        }
    } while(op != 0);
}

int main() {
    srand(time(0));
    int opcion;

    do {
        cout << "\nSistema Empresa De Telefonia Movil\n";
        cout << "1.Cliente\n";
        cout << "2.Trabajador\n";
        cout << "0.Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: menuCliente(); break;
            case 2: menuTrabajador(); break;
            case 0: cout << "Saliendo del sistema\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while(opcion != 0);

    return 0;
}

