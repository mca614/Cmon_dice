#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lista/lista.h"

#define MAX_L_JUGADOR 50

typedef struct{
    int id;
    char nombre[MAX_L_JUGADOR];
    int vidas;
    int puntuacion;
}tJugador;

typedef struct{
    unsigned id;
    char secuencia[MAX_L_JUGADOR];
    char respuesta[MAX_L_JUGADOR];
    unsigned vidasUsadas;
    unsigned puntosObtenidos;
}tRonda;


// mostrar
void mostrarPosicionJugador(void *a, void *extra);
void mostrarPuntuacionJugador(void *a, void *extra);

//comparar
int cmpJugadores(void *a, void *b);
int jugadoresNoGanadores(void *dato, void *info);

#endif // JUGADOR_H_INCLUDED
