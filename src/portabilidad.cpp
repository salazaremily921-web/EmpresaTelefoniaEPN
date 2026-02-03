#include "portabilidad.h"
#include "clientes.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

string portabilidades[MAX_PORTABILIDADES][CAMPOS_PORTABILIDAD];
int totalPortabilidades = 0;

string fechaActual() {
    time_t t = time(0);
    tm *now = localtime(&t);
    return to_string(now->tm_mday) + "/" +
           to_string(now->tm_mon + 1) + "/" +
           to_string(now->tm_year + 1900);
}

string generarIdPortabilidad() {
    return "P" + to_string(1000 + totalPortabilidades + 1);
}

void leerPortabilidad() {
    ifstream archivo("portabilidad.csv");
    if(!archivo.is_open()) return;

    totalPortabilidades = 0;
    string linea;
    while(getline(archivo, linea)) {
        int k = 0;
        string temp = "";
        for(char c : linea) {
            if(c == ',') {
                portabilidades[totalPortabilidades][k++] = temp;
                temp = "";
            } else {
                temp += c;
            }
        }
        portabilidades[totalPortabilidades][k] = temp;
        totalPortabilidades++;
        if(totalPortabilidades >= MAX_PORTABILIDADES) break;
    }
    archivo.close();
}

void guardarPortabilidad() {
    ofstream archivo("portabilidad.csv");
    for(int i = 0; i < totalPortabilidades; i++) {
        for(int j = 0; j < CAMPOS_PORTABILIDAD; j++) {
            archivo << portabilidades[i][j];
            if(j < CAMPOS_PORTABILIDAD - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

void agregarPortabilidad() {
    leerClientes();

    string cedula;
    cout << "Cedula del cliente: ";
    cin >> cedula;
    cin.ignore();

    int pos = buscarClientePorCedula(cedula);
    if(pos == -1) {
        cout << "Cliente no encontrado\n";
        return;
    }

    string nuevoPlan;
    cout << "Plan nuevo: ";
    getline(cin, nuevoPlan);

    portabilidades[totalPortabilidades][0] = generarIdPortabilidad();
    portabilidades[totalPortabilidades][1] = cedula;
    portabilidades[totalPortabilidades][2] = clientes[pos][4]; // telefono
    portabilidades[totalPortabilidades][3] = clientes[pos][7]; // plan anterior
    portabilidades[totalPortabilidades][4] = nuevoPlan;
    portabilidades[totalPortabilidades][5] = fechaActual();
    portabilidades[totalPortabilidades][6] = "Completado";

    clientes[pos][7] = nuevoPlan;
    guardarClientes();

    totalPortabilidades++;
    guardarPortabilidad();

    cout << "Portabilidad realizada correctamente\n";
}

void mostrarPortabilidad() {
    if(totalPortabilidades == 0) {
        cout << "No hay portabilidades registradas\n";
        return;
    }

    cout << left
         << setw(8)  << "Id"
         << setw(12) << "Cedula"
         << setw(12) << "Numero"
         << setw(15) << "Plan ant."
         << setw(15) << "Plan nuevo"
         << setw(12) << "Fecha"
         << setw(12) << "Estado" << "\n";

    cout << string(86, '-') << "\n";

    for(int i = 0; i < totalPortabilidades; i++) {
        cout << left
             << setw(8)  << portabilidades[i][0]
             << setw(12) << portabilidades[i][1]
             << setw(12) << portabilidades[i][2]
             << setw(15) << portabilidades[i][3]
             << setw(15) << portabilidades[i][4]
             << setw(12) << portabilidades[i][5]
             << setw(12) << portabilidades[i][6] << "\n";
    }
}

void mostrarPortabilidadCliente(string cedula) {
    bool encontrado = false;
    for(int i = 0; i < totalPortabilidades; i++) {
        if(portabilidades[i][1] == cedula) {
            cout << "\nPortabilidad\n";
            cout << "Plan anterior: " << portabilidades[i][3] << "\n";
            cout << "Plan nuevo    : " << portabilidades[i][4] << "\n";
            cout << "Fecha         : " << portabilidades[i][5] << "\n";
            encontrado = true;
        }
    }
    if(!encontrado)
        cout << "No registra portabilidades\n";
}

void menuPortabilidad() {
    leerPortabilidad();
    int op;
    do {
        cout << "\nMenu Portabilidad\n";
        cout << "1. Agregar\n";
        cout << "2. Mostrar\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1: agregarPortabilidad(); break;
            case 2: mostrarPortabilidad(); break;
        }
    } while(op != 0);
}

