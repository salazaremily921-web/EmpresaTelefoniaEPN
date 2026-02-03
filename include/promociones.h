#ifndef PROMOCIONES_H
#define PROMOCIONES_H

#include <string>
using namespace std;


const int MAX_PROMOCIONES = 100;     
const int CAMPOS_PROMOCION = 6;      


extern string promociones[MAX_PROMOCIONES][CAMPOS_PROMOCION];
extern int totalPromociones;


string generarIDPromocion();
void leerPromociones();
void guardarPromociones();
void agregarPromocion();
void mostrarPromociones();
void actualizarPromocion();
void eliminarPromocion();
void buscarPromocion();
void intercambiarPromociones(int a,int b);
void ordenarPromocionesPorID();
void ordenarPromocionesPorNombre();
void menuPromociones();

#endif

