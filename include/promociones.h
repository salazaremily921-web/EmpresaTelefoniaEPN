#ifndef PROMOCIONES_H
#define PROMOCIONES_H

#include <string>
using namespace std;

const int MAX_PROMOCIONES = 100;
const int CAMPOS_PROMOCION = 6; // ID, Nombre, Descuento, Fecha Inicio, Fecha Fin, Estado

extern string promociones[MAX_PROMOCIONES][CAMPOS_PROMOCION];
extern int totalPromociones;

void leerPromociones();
void guardarPromociones();

void agregarPromocion();
void mostrarPromociones();
void actualizarPromocion();
void eliminarPromocion();

void buscarPromocion();
void menuPromociones();

void ordenarPromocionesPorID();
void ordenarPromocionesPorNombre();

#endif

