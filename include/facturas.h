#ifndef FACTURAS_H
#define FACTURAS_H

#include <string>
using namespace std;

const int MAX_FACTURAS = 100;
const int CAMPOS_FACTURA = 8; // ID, Cliente, Linea, Mes, Año, Monto, Estado, Observaciones

extern string facturas[MAX_FACTURAS][CAMPOS_FACTURA];
extern int totalFacturas;

// CRUD
void agregarFactura();
void mostrarFacturas();
void actualizarFactura();
void eliminarFactura();
void facturarMes(const string& mes, const string& anio);

// Búsquedas
void buscarFactura();
void buscarFacturaPorID();
void buscarFacturaPorCliente();
void buscarFacturaPorLinea();
void buscarFacturaPorMes();
void buscarFacturaPorAnio();
void buscarFacturaPorMonto();
void buscarFacturaPorEstado();
void buscarFacturaPorObservaciones();
void buscarFacturaPorCualquierCampo();

// Ordenamientos
void ordenarFacturasPorID();
void ordenarFacturasPorCliente();
void ordenarFacturasPorLinea();
void ordenarFacturasPorMes();
void ordenarFacturasPorMonto();

// Archivos
void leerFacturas();
void guardarFacturas();

// Menú
void menuFacturas();

#endif

