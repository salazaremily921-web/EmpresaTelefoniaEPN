#include <iostream>
#include "clientes.h"
#include "lineas.h"
#include "servicios.h"
#include "facturas.h"
#include "promociones.h"

using namespace std;

int main() {
    int opcion;

    do {
        cout << "\n=== Empresa de Telefonia ===\n";
        cout << "1. Clientes\n";
        cout << "2. Lineas Celular\n";
        cout << "3. Servicios\n";
        cout << "4. Facturas\n";
        cout << "5. Promociones\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: menuClientes(); break;
            case 2: menuLineas(); break;
            case 3: menuServicios(); break;
            case 4: menuFacturas(); break;
            case 5: menuPromociones(); break;
            case 0: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    } while(opcion != 0);

    return 0;
}

