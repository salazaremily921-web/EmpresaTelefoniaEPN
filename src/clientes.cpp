#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 100;
const int CAMPOS = 9;

string clientes[MAX][CAMPOS];
int totalClientes = 0;

// Función para generar ID de 13 dígitos
string generarId() {
    string id = "";
    for (int i = 0; i < 13; i++)
        id += to_string(rand() % 10);
    return id;
}

// Planes disponibles
string planes[5] = {"Basico", "Intermedio", "Avanzado", "Premium", "Ilimitado"};

// Verificar cedula repetida
bool cedulaRepetida(string cedula) {
    for (int i = 0; i < totalClientes; i++)
        if (clientes[i][3] == cedula)
            return true;
    return false;
}

// Guardar clientes en CSV
void guardarCSV() {
    ofstream archivo("clientes.csv");
    for (int i = 0; i < totalClientes; i++) {
        for (int j = 0; j < CAMPOS; j++) {
            archivo << clientes[i][j];
            if (j != CAMPOS - 1) archivo << ",";
        }
        archivo << "\n";
    }
    archivo.close();
}

// Leer clientes desde CSV
void leerCSV() {
    ifstream archivo("clientes.csv");
    if (!archivo.is_open()) return;

    string linea;
    totalClientes = 0;
    while (getline(archivo, linea)) {
        int pos = 0, k = 0;
        string temp;
        for (char c : linea) {
            if (c == ',') {
                clientes[totalClientes][k++] = temp;
                temp = "";
            } else {
                temp += c;
            }
        }
        clientes[totalClientes][k++] = temp;
        totalClientes++;
        if (totalClientes >= MAX) break;
    }
    archivo.close();
}

// Agregar cliente
void agregarCliente() {
    if (totalClientes >= MAX) {
        cout << "Limite de clientes alcanzado\n";
        return;
    }

    string cedula;
    cout << "Cedula (10 digitos): ";
    cin >> cedula;
    if (cedula.length() != 10) {
        cout << "Cedula invalida\n";
        return;
    }
    if (cedulaRepetida(cedula)) {
        cout << "Cliente ya existe\n";
        return;
    }

    clientes[totalClientes][0] = generarId();
    clientes[totalClientes][3] = cedula;

    cin.ignore();
    cout << "Nombre (puede ser doble nombre): ";
    getline(cin, clientes[totalClientes][1]);
    cout << "Apellidos (puede ser doble apellido): ";
    getline(cin, clientes[totalClientes][2]);

    string telefono;
    cout << "Telefono (10 digitos): ";
    cin >> telefono;
    if (telefono.length() != 10) {
        cout << "Telefono invalido\n";
        return;
    }
    clientes[totalClientes][4] = telefono;

    cin.ignore();
    cout << "Correo (@gmail.com): ";
    getline(cin, clientes[totalClientes][5]);

    cout << "Direccion: ";
    getline(cin, clientes[totalClientes][6]);

    cout << "Selecciona un plan:\n";
    for (int i = 0; i < 5; i++)
        cout << i+1 << ". " << planes[i] << endl;
    int opcionPlan;
    do {
        cout << "Opcion (1-5): ";
        cin >> opcionPlan;
    } while (opcionPlan < 1 || opcionPlan > 5);
    clientes[totalClientes][7] = planes[opcionPlan - 1];
    clientes[totalClientes][8] = "Activo";

    totalClientes++;
    guardarCSV();
    cout << "Cliente agregado correctamente\n";
}

// Mostrar clientes
void mostrarClientes() {
    if (totalClientes == 0) {
        cout << "No hay clientes\n";
        return;
    }
    for (int i = 0; i < totalClientes; i++) {
        cout << "\nId: " << clientes[i][0];
        cout << "\nNombre: " << clientes[i][1];
        cout << "\nApellidos: " << clientes[i][2];
        cout << "\nCedula: " << clientes[i][3];
        cout << "\nTelefono: " << clientes[i][4];
        cout << "\nCorreo: " << clientes[i][5];
        cout << "\nDireccion: " << clientes[i][6];
        cout << "\nPlan: " << clientes[i][7];
        cout << "\nEstado: " << clientes[i][8];
        cout << "\n------------------------\n";
    }
}

// Buscar cliente por cedula
void buscarCliente() {
    string cedula;
    cout << "Cedula a buscar: ";
    cin >> cedula;

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i][3] == cedula) {
            cout << "Cliente encontrado\n";
            cout << "Id: " << clientes[i][0] << endl;
            cout << "Nombre: " << clientes[i][1] << " " << clientes[i][2] << endl;
            cout << "Correo: " << clientes[i][5] << endl;
            cout << "Plan: " << clientes[i][7] << endl;
            cout << "Estado: " << clientes[i][8] << endl;
            return;
        }
    }
    cout << "Cliente no encontrado\n";
}

// Actualizar cliente
void actualizarCliente() {
    string cedula;
    cout << "Cedula a actualizar: ";
    cin >> cedula;

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i][3] == cedula) {
            int opcion;
            do {
                cout << "\n=== Actualizar Cliente ===\n";
                cout << "1. Nombre\n";
                cout << "2. Apellidos\n";
                cout << "3. Correo\n";
                cout << "4. Telefono\n";
                cout << "5. Estado\n";
                cout << "6. Plan\n";
                cout << "0. Terminar actualizacion\n";
                cout << "Opcion: ";
                cin >> opcion;
                cin.ignore();

                switch (opcion) {
                    case 1:
                        cout << "Nuevo nombre: ";
                        getline(cin, clientes[i][1]);
                        break;
                    case 2:
                        cout << "Nuevos apellidos: ";
                        getline(cin, clientes[i][2]);
                        break;
                    case 3:
                        cout << "Nuevo correo: ";
                        getline(cin, clientes[i][5]);
                        break;
                    case 4: {
                        string telefono;
                        cout << "Nuevo telefono (10 digitos): ";
                        cin >> telefono;
                        if (telefono.length() == 10)
                            clientes[i][4] = telefono;
                        else
                            cout << "Telefono invalido\n";
                        cin.ignore();
                        break;
                    }
                    case 5: {
                        string estado;
                        cout << "Nuevo estado (Activo/Inactivo): ";
                        getline(cin, estado);
                        clientes[i][8] = estado;
                        break;
                    }
                    case 6: {
                        cout << "Selecciona un plan:\n";
                        for (int j = 0; j < 5; j++)
                            cout << j+1 << ". " << planes[j] << endl;
                        int opcionPlan;
                        do {
                            cout << "Opcion (1-5): ";
                            cin >> opcionPlan;
                        } while (opcionPlan < 1 || opcionPlan > 5);
                        clientes[i][7] = planes[opcionPlan - 1];
                        cin.ignore();
                        break;
                    }
                    case 0:
                        cout << "Actualizacion finalizada\n";
                        break;
                    default:
                        cout << "Opcion invalida\n";
                }

            } while (opcion != 0);

            guardarCSV();
            return;
        }
    }
    cout << "Cliente no encontrado\n";
}

// Eliminar cliente
void eliminarCliente() {
    string cedula;
    cout << "Cedula a eliminar: ";
    cin >> cedula;

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i][3] == cedula) {
            for (int j = i; j < totalClientes - 1; j++)
                for (int k = 0; k < CAMPOS; k++)
                    clientes[j][k] = clientes[j + 1][k];

            totalClientes--;
            guardarCSV();
            cout << "Cliente eliminado\n";
            return;
        }
    }
    cout << "Cliente no encontrado\n";
}

// Intercambiar filas
void intercambiarFilas(int a, int b) {
    for (int k = 0; k < CAMPOS; k++) {
        string temp = clientes[a][k];
        clientes[a][k] = clientes[b][k];
        clientes[b][k] = temp;
    }
}

// Ordenar clientes por nombre
void ordenarPorNombre() {
    for (int i = 0; i < totalClientes - 1; i++)
        for (int j = i + 1; j < totalClientes; j++)
            if (clientes[i][1] > clientes[j][1])
                intercambiarFilas(i, j);

    cout << "Clientes ordenados\n";
    guardarCSV();
}

// Menu clientes
void menuClientes() {
    leerCSV(); // Leer datos al iniciar

    int opcion;
    do {
        cout << "\n=== Lista de Clientes ===\n";
        cout << "1. Agregar\n";
        cout << "2. Mostrar\n";
        cout << "3. Buscar\n";
        cout << "4. Actualizar\n";
        cout << "5. Eliminar\n";
        cout << "6. Ordenar\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarCliente(); break;
            case 2: mostrarClientes(); break;
            case 3: buscarCliente(); break;
            case 4: actualizarCliente(); break;
            case 5: eliminarCliente(); break;
            case 6: ordenarPorNombre(); break;
            case 0: break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 0);
}

