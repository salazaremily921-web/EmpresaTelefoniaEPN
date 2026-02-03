#ifndef PORTABILIDAD_H
#define PORTABILIDAD_H

#include <string>
using namespace std;

const int MAX_PORTABILIDADES = 100;    
const int CAMPOS_PORTABILIDAD = 7;     


void leerPortabilidad();
void guardarPortabilidad();
void agregarPortabilidad();
void mostrarPortabilidad();
void mostrarPortabilidadCliente(string cedula);
void menuPortabilidad();

#endif

