#ifndef SECUENCIA_H_INCLUDED
#define SECUENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para linux
#include <windows.h> // para windows
#include <time.h>
#include "API.h"
#include "lista_d.h"

char seleccionarLetra (char* letras);

int obtenerSecuencia(t_lista* plSecuencia);

int mostrarSecuencia (t_lista* plSecuencia, unsigned cantLetras);

void mostrarLetra (void* dato, void* cond);

void mostrarLetra_ (void* dato, void* cond);

#endif // SECUENCIA_H_INCLUDED