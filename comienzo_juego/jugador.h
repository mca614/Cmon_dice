#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

#define MAX_L_JUGADOR 100

typedef struct{
    int id;
    char nombre[MAX_L_JUGADOR];
    int puntuacion;
}tJugador;

void ingresarJugador(tJugador *jugador, int cantidadJugadores);
void mostrarPosicionesJugadores(t_lista *listaJugadores);
int cmpJugadores(void *a, void *b);
int jugadoresNoGanadores(void *dato, void *info);

void mostrarJugador(void *a, void *extra);
void agregarJugadorListaGanadores(void* info, void* otraLista);
void almacenarNombreGanadores(void *dato, void *info);

#endif // JUGADOR_H_INCLUDED
