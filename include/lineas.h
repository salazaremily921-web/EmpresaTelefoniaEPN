
#ifndef LINEAS_H
#define LINEAS_H

#include <string>
using namespace std;

const int MAX_LINEAS = 100;
const int CAMPOS = 9;

extern string lineas[MAX_LINEAS][CAMPOS];
extern int totalLineas;


string generarIDLinea();
void leerLineas();
void guardarLineas();
void agregarLinea();
void mostrarLineas();
void actualizarLinea();
void eliminarLinea();
void menuLineas();


bool validarNumeroLinea(const string& num);


void buscarLineaPorID();
void buscarLineaPorCliente();
void buscarLineaPorNumero();
void buscarLineaPorPlan();
void buscarLineaPorEstado();
void buscarLineaPorTipo();
void buscarLineaPorFecha();


void intercambiarFilasLinea(int a, int b);
void ordenarLineasPorID();
void ordenarLineasPorNumero();
void ordenarLineasPorPlan();
void ordenarLineasPorEstado();
void ordenarLineasPorFecha();

#endif

