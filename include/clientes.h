#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
using namespace std;

const int MAX_CLIENTES = 100;
const int CAMPOS_CLIENTE = 9;

extern string clientes[MAX_CLIENTES][CAMPOS_CLIENTE];
extern int totalClientes;

// Funciones principales
string generarID();
void leerClientes();
void guardarClientes();
void agregarCliente();
void mostrarClientes();
void actualizarCliente();
void eliminarCliente();
void menuClientes();

// Funciones de ordenamiento
void intercambiarClientes(int a, int b);
void ordenarClientesPorID();
void ordenarClientesPorNombre();
void ordenarClientesPorApellido();
void ordenarClientesPorPlan();
void ordenarClientesPorEstado();

// Funciones de búsqueda
void buscarCliente();
void buscarClientePorID();
void buscarClientePorNombre();
void buscarClientePorApellido();
void buscarClientePorCedula();
void buscarClientePorTelefono();
void buscarClientePorCorreo();
void buscarClientePorDireccion();
void buscarClientePorPlan();
void buscarClientePorEstado();

void menuClientes();
void agregarCliente();
void mostrarClientes();
void actualizarCliente();
void eliminarCliente();
void buscarCliente();
void ordenarClientesPorID();
void ordenarClientesPorNombre();
void ordenarClientesPorApellido();
void ordenarClientesPorPlan();
void ordenarClientesPorEstado();

#endif



