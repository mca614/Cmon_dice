#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cmon.h"
#include  "interfaz/interfaz.h"

#define ES_DIGITO_VALIDO(l) ((l) >= '1' && (l) <= '9') || ((l) >= 'a' && (l) <= 'z')

void bienvenidoSimonDice();
int menuPrincipal(t_lista* listaJugadores,unsigned* cantidadJugadores);
char menuConError(const char *msj, const char *opc);
void ingresarJugador(tJugador *jugador, unsigned *cantidadJugadores);
void menuIngresoJugadores(t_lista *listaJugadores, unsigned *cantidadJugadores);
int menuDificultad(tDatosPartida *datosPartida);
int cargarDificultad(tDatosPartida *datosPartida);
int menuComenzarJuego();

#endif // MENU_H_INCLUDED
