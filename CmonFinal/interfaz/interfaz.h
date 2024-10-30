
#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "colores.h"

#define TAM_OPCION 30

void centrarVentanaConsola();
void cambiarTamanoFuente(int ancho, int alto);
void establecerTamanioConsola(int ancho, int alto);
void deshabilitarRedimension();
void ajustarConsola(int fuenteAncho, int fuenteAlto, int consolaAncho, int consolaAlto);
void colorFondo(int cFondo, int cFuente);
int menu(char* menu, const char opciones[][TAM_OPCION], int cantOpciones);
void mostrarMenu(int opcionSeleccionada, const char opciones[][TAM_OPCION],int cantOpciones) ;
void fondoRondas (int ronda, int cfuente);
void colorFuente (int cFuente);

#endif // INTERFAZ_H_INCLUDED
