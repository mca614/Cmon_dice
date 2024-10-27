#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cmon.h"

char menuConError(const char *msj, const char *opc);
void ingresarJugador(tJugador *jugador, unsigned *cantidadJugadores);
void menuIngresoJugadores(t_lista *listaJugadores, unsigned *cantidadJugadores);
int menuDificultad(tDatosPartida *datosPartida);
int menuComenzarJuego();

#endif // MENU_H_INCLUDED
