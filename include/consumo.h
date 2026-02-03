#ifndef CONSUMO_H
#define CONSUMO_H

#include <string>
using namespace std;

#define MAX_CONSUMOS 500
#define CAMPOS_CONSUMO 7

extern string consumos[MAX_CONSUMOS][CAMPOS_CONSUMO];
extern int totalConsumos;

void leerConsumos();
void guardarConsumos();

void agregarConsumo();
void mostrarConsumos();
void mostrarConsumoCliente(string cedula);

void menuConsumo();

#endif

