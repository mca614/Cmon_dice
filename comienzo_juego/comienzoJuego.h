#ifndef COMIENZOJUEGO_H_INCLUDED
#define COMIENZOJUEGO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugarPartida/funciones.h"
#include "lista.h"
#include "jugador.h"

#define MAX_LINEA 1024

typedef struct{
    char dificultad;
    unsigned tiempoSecuencia;
    unsigned tiempoJugada;
    unsigned maximaPuntuacion;
    unsigned cantVidas;
}tDatosPartida;

char menuConError(const char *msj, const char *opc);
int menuDificultad(tDatosPartida *datosPartida);
void menuIngresoJugadores(t_lista *listaJugadores, int *cantidadJugadores);
int menuComenzarJuego(tJugador proximoJugador);

int cargarDificultad(tDatosPartida *datosPartida);
void ingresarJugador(tJugador *jugador, int cantidadJugadores);
void cargarMostrarDatosJugador(void *v, void *extra);

void jugarPartida(void *jugador, void *extra);

#endif // COMIENZOJUEGO_H_INCLUDED
