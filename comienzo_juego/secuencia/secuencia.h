#ifndef SECUENCIA_H_INCLUDED
#define SECUENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para linux
#include <windows.h> // para windows
#include <time.h>
#include "API.h"
#include "interfazConsola.h"
#include "../lista.h"

char seleccionarLetra (char* letras);

int obtenerSecuencia(t_lista* plSecuencia);

int mostrarSecuencia_ (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase);

int mostrarGenerarSecuencia (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase); // funcion que se va a usa en el juego

void mostrarLetra (void* dato, void* cond);

void mostrarLetra_ (void* dato, void* cond);

void centrarConsola_();

#endif // SECUENCIA_H_INCLUDED
