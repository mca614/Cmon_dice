#ifndef CMON_H_INCLUDED
#define CMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "estructurasDatos/cola/colaDinamica.h"
#define MAX_L_JUGADOR 50
#define MAX_TAM_PATH 50


typedef struct{
    char dificultad;
    unsigned tiempoSecuencia;
    unsigned tiempoRespuesta;
    unsigned maximaPuntuacion;
    unsigned cantVidas;
    FILE *archInforme;
}tDatosPartida;

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
    unsigned puntosRonda;
    unsigned puntosTotales;
}tRonda;

#include "jugarTurno.h"
#include "estructurasDatos/lista/lista.h"

void jugarPartida(void *jugador, void *extra);
FILE* generarArchivoDeInforme(const char* nombrePrefijo);
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno);
void exportarGanadoresHaciaInforme(FILE* archInforme, t_lista* ganadores);

#endif // CMON_H_INCLUDED
