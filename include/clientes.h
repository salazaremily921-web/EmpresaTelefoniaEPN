#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
using namespace std;

#define MAX_CLIENTES 100
#define CAMPOS_CLIENTE 9

extern string clientes[MAX_CLIENTES][CAMPOS_CLIENTE];
extern int totalClientes;

void leerClientes();
void guardarClientes();
void agregarCliente();
void mostrarClientes();
void actualizarCliente();
void eliminarCliente();
void menuClientes();

int buscarClientePorCedula(string cedula);
void mostrarDatosCliente(int pos);

#endif

