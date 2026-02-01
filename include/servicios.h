#ifndef SERVICIOS_H
#define SERVICIOS_H

#include <string>
const int MAX_SERVICIOS = 100;
extern std::string servicios[MAX_SERVICIOS][10];
extern int totalServicios;

void menuServicios();
void leerServicios();
void guardarServicios();
void agregarServicio();
void mostrarServicios();

#endif

