#ifndef PROMOCIONES_H
#define PROMOCIONES_H

#include <string>
extern std::string promociones[100][10];
extern int totalPromociones;

void menuPromociones();
void leerPromociones();
void guardarPromociones();
void agregarPromocion();
void mostrarPromociones();
void buscarPromocionPlan();

#endif

