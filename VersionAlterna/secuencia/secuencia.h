#ifndef SECUENCIA_H_INCLUDED
#define SECUENCIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para linux
#include <windows.h> // para windows
#include <time.h>
#include "API.h"
//#include "interfazConsola.h"
//#include "lista_d.h"
#include "../lista.h"

char seleccionarLetra (char* letras);

int obtenerSecuencia(t_lista* plSecuencia);

int mostrarSecuencia_ (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase);

//int mostrarSecuencia (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase, void accion (void* a, void* b)); // funcion que se va a usa en el juego

void mostrarLetra (const void * dato,const void * cond);

void mostrarLetra_ (const void * dato,const void * cond);

void centrarConsola_();

#endif // SECUENCIA_H_INCLUDED
