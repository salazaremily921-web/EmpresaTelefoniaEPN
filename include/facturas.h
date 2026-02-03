#ifndef FACTURAS_H
#define FACTURAS_H

#include <string>
using namespace std;

#define MAX_FACTURAS 200
#define CAMPOS_FACTURA 8

extern string facturas[MAX_FACTURAS][CAMPOS_FACTURA];
extern int totalFacturas;

void leerFacturas();
void guardarFacturas();
void generarFacturaMensual();
void mostrarFacturas();
void eliminarFactura();
void menuFacturas();

void mostrarFacturasCliente(string cedula);

#endif

