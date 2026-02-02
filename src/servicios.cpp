#include "servicios.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

string servicios[MAX_SERVICIOS][CAMPOS_SERVICIO];
int totalServicios = 0;

// csv
void leerServicios() {
    ifstream archivo("servicios.csv");
    if (!archivo.is_open()) return;

    totalServicios = 0;
    string linea;
    while (getline(archivo, linea)) {
        int k = 0; string temp = "";
        for (char c : linea) {
            if (c == ',') { servicios[totalServicios][k++] = temp; temp = ""; }
            else temp += c;
        }
        servicios[totalServicios][k++] = temp;
        totalServicios++;
        if (totalServicios >= MAX_SERVICIOS) break;
    }
    archivo.close();
}

void guardarServicios() {
    ofstream archivo("servicios.csv");
    for (int i = 0; i < totalServicios; i++) {
        for (int j = 0; j < CAMPOS_SERVICIO; j++) {
            archivo << servicios[i][j];
            if (j != CAMPOS_SERVICIO - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

// crud
string generarIDServicio() {
    string id = "";
    for (int i = 0; i < 8; i++) id += to_string(rand() % 10);
    return id;
}

bool validarCosto(const string &c) {
    for (char ch : c) if (!isdigit(ch) && ch != '.') return false;
    return !c.empty();
}

bool validarEstado(const string &e) {
    return e == "Activo" || e == "Inactivo";
}

void agregarServicio() {
    if (totalServicios >= MAX_SERVICIOS) { cout << "Limite de servicios alcanzado\n"; return; }

    servicios[totalServicios][0] = generarIDServicio();
    cin.ignore();

    cout << "Nombre del servicio: "; getline(cin, servicios[totalServicios][1]);

    string costo;
    do {
        cout << "Costo: "; getline(cin, costo);
        if (!validarCosto(costo)) cout << "Costo invalido, solo numeros.\n";
    } while (!validarCosto(costo));
    servicios[totalServicios][2] = costo;

    cout << "Plan asociado: "; getline(cin, servicios[totalServicios][3]);

    string estado;
    do {
        cout << "Estado (Activo/Inactivo): "; getline(cin, estado);
        if (!validarEstado(estado)) cout << "Estado invalido\n";
    } while (!validarEstado(estado));
    servicios[totalServicios][4] = estado;

    cout << "Observaciones: "; getline(cin, servicios[totalServicios][5]);

    totalServicios++;
    guardarServicios();
    cout << "Servicio agregado correctamente\n";
}

void mostrarServicios() {
    if (totalServicios == 0) { cout << "No hay servicios\n"; return; }

    cout << "\nID\tNombre\tCosto\tPlan\tEstado\tObservaciones\n";
    for (int i = 0; i < totalServicios; i++) {
        for (int j = 0; j < CAMPOS_SERVICIO; j++)
            cout << servicios[i][j] << "\t";
        cout << "\n";
    }
}

void actualizarServicio() {
    string id; cout << "ID del servicio a actualizar: "; cin.ignore(); getline(cin, id);
    for (int i = 0; i < totalServicios; i++) {
        if (servicios[i][0] == id) {
            int opcion;
            do {
                cout << "\n Actualizar Servicio \n";
                cout << "1.Nombre 2.Costo 3.Plan 4.Estado 5.Observaciones 0.Salir\nOpcion: ";
                cin >> opcion; cin.ignore();
                switch (opcion) {
                    case 1: cout << "Nuevo nombre: "; getline(cin, servicios[i][1]); break;
                    case 2: {
                        string costo;
                        do { cout << "Nuevo costo: "; getline(cin, costo);
                            if (!validarCosto(costo)) cout << "Costo invalido\n";
                        } while (!validarCosto(costo));
                        servicios[i][2] = costo;
                        break;
                    }
                    case 3: cout << "Nuevo plan: "; getline(cin, servicios[i][3]); break;
                    case 4: {
                        string estado;
                        do { cout << "Nuevo estado (Activo/Inactivo): "; getline(cin, estado);
                            if (!validarEstado(estado)) cout << "Estado invalido\n";
                        } while (!validarEstado(estado));
                        servicios[i][4] = estado;
                        break;
                    }
                    case 5: cout << "Nueva observacion: "; getline(cin, servicios[i][5]); break;
                }
            } while (opcion != 0);
            guardarServicios();
            cout << "Servicio actualizado\n"; return;
        }
    }
    cout << "Servicio no encontrado\n";
}

void eliminarServicio() {
    string id; cout << "ID del servicio a eliminar: "; cin.ignore(); getline(cin, id);
    for (int i = 0; i < totalServicios; i++) {
        if (servicios[i][0] == id) {
            for (int j = i; j < totalServicios - 1; j++)
                for (int k = 0; k < CAMPOS_SERVICIO; k++)
                    servicios[j][k] = servicios[j + 1][k];
            totalServicios--;
            guardarServicios();
            cout << "Servicio eliminado\n"; return;
        }
    }
    cout << "Servicio no encontrado\n";
}

// busquedas
void buscarServicioPorID() { string id; cout << "ID: "; getline(cin, id); for (int i = 0; i < totalServicios; i++) if (servicios[i][0] == id) cout << servicios[i][1] << " | " << servicios[i][2] << "\n"; }
void buscarServicioPorNombre() { string n; cout << "Nombre: "; getline(cin, n); for (int i = 0; i < totalServicios; i++) if (servicios[i][1] == n) cout << servicios[i][0] << " | " << servicios[i][2] << "\n"; }
void buscarServicioPorCosto() { string c; cout << "Costo: "; getline(cin, c); for (int i = 0; i < totalServicios; i++) if (servicios[i][2] == c) cout << servicios[i][0] << " | " << servicios[i][1] << "\n"; }
void buscarServicioPorPlan() { string p; cout << "Plan: "; getline(cin, p); for (int i = 0; i < totalServicios; i++) if (servicios[i][3] == p) cout << servicios[i][0] << " | " << servicios[i][1] << "\n"; }
void buscarServicioPorEstado() { string e; cout << "Estado: "; getline(cin, e); for (int i = 0; i < totalServicios; i++) if (servicios[i][4] == e) cout << servicios[i][0] << " | " << servicios[i][1] << "\n"; }
void buscarServicioPorObservaciones() { string o; cout << "Obs: "; getline(cin, o); for (int i = 0; i < totalServicios; i++) if (servicios[i][5] == o) cout << servicios[i][0] << " | " << servicios[i][1] << "\n"; }
void buscarServicioPorCualquierCampo() { string b; cout << "Buscar: "; getline(cin, b); for (int i = 0; i < totalServicios; i++) for (int j = 0; j < CAMPOS_SERVICIO; j++) if (servicios[i][j] == b) cout << servicios[i][0] << " | " << servicios[i][1] << "\n"; }
void buscarServicioPorRangoCosto() { cout << "Busqueda por rango de costo ejemplo: 10-50 (opcional, no implementada)\n"; }
void buscarServicioPorLetraInicial() { cout << "Busqueda por letra inicial (opcional)\n"; }
void buscarServicioPorTexto() { cout << "Busqueda por texto libre (opcional)\n"; }

void buscarServicio() {
    int opcion;
    do {
        cout << "\n Menu Busqueda Servicios \n1.ID 2.Nombre 3.Costo 4.Plan 5.Estado 6.Observaciones 7.CualquierCampo 8.RangoCosto 9.LetraInicial 10.Texto 0.Salir\nOpcion: ";
        cin >> opcion; cin.ignore();
        switch (opcion) {
            case 1: buscarServicioPorID(); break;
            case 2: buscarServicioPorNombre(); break;
            case 3: buscarServicioPorCosto(); break;
            case 4: buscarServicioPorPlan(); break;
            case 5: buscarServicioPorEstado(); break;
            case 6: buscarServicioPorObservaciones(); break;
            case 7: buscarServicioPorCualquierCampo(); break;
            case 8: buscarServicioPorRangoCosto(); break;
            case 9: buscarServicioPorLetraInicial(); break;
            case 10: buscarServicioPorTexto(); break;
        }
    } while (opcion != 0);
}

// ordenamientos
void intercambiarServicios(int a, int b) { for (int k = 0; k < CAMPOS_SERVICIO; k++) { string tmp = servicios[a][k]; servicios[a][k] = servicios[b][k]; servicios[b][k] = tmp; } }
void ordenarServiciosPorID() { for (int i = 0; i < totalServicios - 1; i++) for (int j = i + 1; j < totalServicios; j++) if (servicios[i][0] > servicios[j][0]) intercambiarServicios(i, j); }
void ordenarServiciosPorNombre() { for (int i = 0; i < totalServicios - 1; i++) for (int j = i + 1; j < totalServicios; j++) if (servicios[i][1] > servicios[j][1]) intercambiarServicios(i, j); }
void ordenarServiciosPorCosto() { for (int i = 0; i < totalServicios - 1; i++) for (int j = i + 1; j < totalServicios; j++) if (servicios[i][2] > servicios[j][2]) intercambiarServicios(i, j); }
void ordenarServiciosPorPlan() { for (int i = 0; i < totalServicios - 1; i++) for (int j = i + 1; j < totalServicios; j++) if (servicios[i][3] > servicios[j][3]) intercambiarServicios(i, j); }
void ordenarServiciosPorEstado() { for (int i = 0; i < totalServicios - 1; i++) for (int j = i + 1; j < totalServicios; j++) if (servicios[i][4] > servicios[j][4]) intercambiarServicios(i, j); }

// menu
void menuServicios() {
    leerServicios();
    int opcion;
    do {
        cout << "\n Menu Servicios \n1.Agregar 2.Mostrar 3.Buscar 4.Actualizar 5.Eliminar 6.Ordenar 0.Salir\nOpcion: ";
        cin >> opcion; cin.ignore();
        switch (opcion) {
            case 1: agregarServicio(); break;
            case 2: mostrarServicios(); break;
            case 3: buscarServicio(); break;
            case 4: actualizarServicio(); break;
            case 5: eliminarServicio(); break;
            case 6: {
                int ord;
                cout << "Ordenar por: 1.ID 2.Nombre 3.Costo 4.Plan 5.Estado\nOpcion: "; cin >> ord; cin.ignore();
                switch (ord) {
                    case 1: ordenarServiciosPorID(); break;
                    case 2: ordenarServiciosPorNombre(); break;
                    case 3: ordenarServiciosPorCosto(); break;
                    case 4: ordenarServiciosPorPlan(); break;
                    case 5: ordenarServiciosPorEstado(); break;
                }
                break;
            }
        }
    } while (opcion != 0);
}

