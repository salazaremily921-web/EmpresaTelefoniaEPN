#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
const int MAX_CLIENTES = 100;

extern std::string clientes[MAX_CLIENTES][10];
extern int totalClientes;

void menuClientes();
void leerClientes();
void guardarClientes();
void insertarCliente();
void listarClientes();
void buscarCliente();
void actualizarCliente();
void eliminarCliente();

#endif

