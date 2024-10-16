#ifndef COMIENZOJUEGO_H_INCLUDED
#define COMIENZOJUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
#include "jugador.h"
#define MAX_LINEA 1024

void mostrarJugador(void *j, void *extra);
char menuConError(const char *msj, const char *opc);
int menuDificultad(char *dificultadElegida);
void menuIngresoJugadores(t_lista *listaJugadores, int *cantidadJugadores);
int mostrarConfDificultad(char *dificultadElegida);
int menuComenzarJuego(tJugador proximoJugador);

int randomInRange(int menorValor, int mayorValor);

#endif // COMIENZOJUEGO_H_INCLUDED
