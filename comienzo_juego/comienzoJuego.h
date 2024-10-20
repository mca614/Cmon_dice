#ifndef COMIENZOJUEGO_H_INCLUDED
#define COMIENZOJUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugarPartida/funciones.h"
#include "lista.h"
#include "jugador.h"

#define MAX_L_DIFICULTAD 10
#define MAX_LINEA 1024

typedef struct{
    char dificultad[MAX_L_DIFICULTAD];
    unsigned tiempoSecuencia;
    unsigned tiempoJugada;
    unsigned cantVidas;
}tDificultad;

char menuConError(const char *msj, const char *opc);
int menuDificultad(tDificultad *dificultadElegida);
void menuIngresoJugadores(t_lista *listaJugadores, int *cantidadJugadores);
int menuComenzarJuego(tJugador proximoJugador);

int cargarDificultad(tDificultad *dificultadElegida);
void ingresarJugador(tJugador *jugador, int cantidadJugadores);
void cargarDatosJugadores(t_lista *listaJugadores, int cantVidas);
#endif // COMIENZOJUEGO_H_INCLUDED
