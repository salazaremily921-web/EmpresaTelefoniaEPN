#include "consumo.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

string consumos[MAX_CONSUMOS][CAMPOS_CONSUMO];
int totalConsumos = 0;

void leerConsumos() {
    ifstream archivo("consumo.csv");
    if(!archivo.is_open()) return;

    totalConsumos = 0;
    string linea;
    while(getline(archivo, linea)) {
        int k = 0;
        string temp = "";
        for(char c : linea) {
            if(c == ',') {
                consumos[totalConsumos][k++] = temp;
                temp = "";
            } else temp += c;
        }
        consumos[totalConsumos][k++] = temp;
        totalConsumos++;
        if(totalConsumos >= MAX_CONSUMOS) break;
    }
    archivo.close();
}

void guardarConsumos() {
    ofstream archivo("consumo.csv");
    for(int i = 0; i < totalConsumos; i++) {
        for(int j = 0; j < CAMPOS_CONSUMO; j++) {
            archivo << consumos[i][j];
            if(j != CAMPOS_CONSUMO - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

void agregarConsumo() {
    if(totalConsumos >= MAX_CONSUMOS) {
        cout << "Limite de registros alcanzado\n";
        return;
    }

    cin.ignore();
    cout << "Cedula del cliente: ";
    getline(cin, consumos[totalConsumos][0]);

    cout << "Mes: ";
    getline(cin, consumos[totalConsumos][1]);

    cout << "Anio: ";
    getline(cin, consumos[totalConsumos][2]);

    cout << "Minutos usados: ";
    getline(cin, consumos[totalConsumos][3]);

    cout << "Datos usados (GB): ";
    getline(cin, consumos[totalConsumos][4]);

    cout << "Mensajes enviados: ";
    getline(cin, consumos[totalConsumos][5]);

    cout << "Observacion: ";
    getline(cin, consumos[totalConsumos][6]);

    totalConsumos++;
    guardarConsumos();
    cout << "Consumo registrado correctamente\n";
}

void mostrarConsumos() {
    if(totalConsumos == 0) {
        cout << "No hay consumos registrados\n";
        return;
    }

    cout << left
         << setw(12) << "Cedula"
         << setw(10) << "Mes"
         << setw(8)  << "Anio"
         << setw(12) << "Minutos"
         << setw(12) << "DatosGB"
         << setw(12) << "Mensajes"
         << setw(20) << "Observacion"
         << "\n";

    cout << string(86, '-') << "\n";

    for(int i = 0; i < totalConsumos; i++) {
        cout << left
             << setw(12) << consumos[i][0]
             << setw(10) << consumos[i][1]
             << setw(8)  << consumos[i][2]
             << setw(12) << consumos[i][3]
             << setw(12) << consumos[i][4]
             << setw(12) << consumos[i][5]
             << setw(20) << consumos[i][6]
             << "\n";
    }
}

void mostrarConsumoCliente(string cedula) {
    bool encontrado = false;

    for(int i = 0; i < totalConsumos; i++) {
        if(consumos[i][0] == cedula) {
            if(!encontrado) {
                cout << "\nHistorial de consumo\n";
                cout << string(40, '-') << "\n";
            }
            cout << "Mes: " << consumos[i][1] << " " << consumos[i][2] << "\n";
            cout << "Minutos: " << consumos[i][3] << "\n";
            cout << "Datos: " << consumos[i][4] << " GB\n";
            cout << "Mensajes: " << consumos[i][5] << "\n";
            cout << "Observacion: " << consumos[i][6] << "\n\n";
            encontrado = true;
        }
    }

    if(!encontrado)
        cout << "No existen registros de consumo\n";
}

void menuConsumo() {
    leerConsumos();
    int opcion;

    do {
        cout << "\nMenu Consumo\n";
        cout << "1. Agregar\n";
        cout << "2. Mostrar\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: agregarConsumo(); break;
            case 2: mostrarConsumos(); break;
        }
    } while(opcion != 0);
}

