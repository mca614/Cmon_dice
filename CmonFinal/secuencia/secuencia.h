#ifndef SECUENCIA_H_INCLUDED
#define SECUENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "API.h"
#include "../estructurasDatos/lista/lista.h"
#include "../interfaz/interfaz.h"

char seleccionarLetra (char* letras);
int obtenerSecuencia(t_lista* plSecuencia);
int mostrarSecuencia_ (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase);
void mostrarLetraSecuencia ( void * dato, void * cond);
void mostrarLetra_ ( void * dato, void * cond);

#endif // SECUENCIA_H_INCLUDED
