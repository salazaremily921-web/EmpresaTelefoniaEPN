
#ifndef LINEAS_H
#define LINEAS_H

#include <string>
using namespace std;

const int MAX_LINEAS = 100;
const int CAMPOS = 9;

extern string lineas[MAX_LINEAS][CAMPOS];
extern int totalLineas;

// Funciones principales
string generarIDLinea();
void leerLineas();
void guardarLineas();
void agregarLinea();
void mostrarLineas();
void actualizarLinea();
void eliminarLinea();
void menuLineas();

// Validaciones
bool validarNumeroLinea(const string& num);

// Funciones de búsqueda
void buscarLineaPorID();
void buscarLineaPorCliente();
void buscarLineaPorNumero();
void buscarLineaPorPlan();
void buscarLineaPorEstado();
void buscarLineaPorTipo();
void buscarLineaPorFecha();

// Funciones de ordenamiento
void intercambiarFilasLinea(int a, int b);
void ordenarLineasPorID();
void ordenarLineasPorNumero();
void ordenarLineasPorPlan();
void ordenarLineasPorEstado();
void ordenarLineasPorFecha();

#endif

