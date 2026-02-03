#ifndef SERVICIOS_H
#define SERVICIOS_H

#include <string>
using namespace std;

const int MAX_SERVICIOS = 100;
const int CAMPOS_SERVICIO = 6;

extern string servicios[MAX_SERVICIOS][CAMPOS_SERVICIO];
extern int totalServicios;


string generarIDServicio();
void agregarServicio();
void mostrarServicios();
void actualizarServicio();
void eliminarServicio();

void buscarServicio();
void buscarServicioPorID();
void buscarServicioPorNombre();
void buscarServicioPorCosto();
void buscarServicioPorPlan();
void buscarServicioPorEstado();
void buscarServicioPorObservaciones();
void buscarServicioPorCualquierCampo();
void buscarServicioPorRangoCosto();
void buscarServicioPorLetraInicial();
void buscarServicioPorTexto();


void intercambiarServicios(int a,int b);
void ordenarServiciosPorID();
void ordenarServiciosPorNombre();
void ordenarServiciosPorCosto();
void ordenarServiciosPorPlan();
void ordenarServiciosPorEstado();


void leerServicios();
void guardarServicios();


void menuServicios();

#endif

