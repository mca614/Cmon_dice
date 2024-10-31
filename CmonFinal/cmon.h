#ifndef CMON_H_INCLUDED
#define CMON_H_INCLUDED

#define VALOR_MAX 20
#define VALOR_MIN 1
#define VIDAS_MAX 5
#define MAX_L_DIF 10
#define MAX_L_JUGADOR 20
#define MAX_L_SEC 100
#define MAX_L_DIF 10
#define MAX_TAM_PATH 50
#define MAX_LINEA 1024


#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int tiempoSecuencia;
    int tiempoRespuesta;
    int cantVidas;
    char dificultad[MAX_L_DIF];
}tDatosDificultad;

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
    char nombre[MAX_L_JUGADOR+1];
    int vidas;
    int puntuacion;
}tJugador;

typedef struct{
    unsigned id;
    char secuencia[MAX_L_SEC];
    char respuesta[MAX_L_SEC];
    unsigned vidasUsadas;
    unsigned puntosRonda;
    unsigned puntosTotales;
}tRonda;

#include "estructurasDatos/cola/colaDinamica.h"
#include "jugarTurno.h"
#include "estructurasDatos/lista/lista.h"
#include "menu.h"
#include "musica/musica.h"
#include "interfaz/interfaz.h"

void mostrarJugador(void *a, void *extra);
int jugadoresNoGanadores(void *dato, void *info);
int cmpJugadores(void *a, void *b);
void cargarMostrarDatosJugador(void *v, void *extra);

void jugarPartida(void *jugador, void *extra);
int generarArchivoConf();
FILE* generarArchivoDeInforme(const char* nombrePrefijo, char* nomArchGenerado);
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno);
void exportarGanadoresHaciaInforme(FILE* archInforme, t_lista* ganadores);

#endif // CMON_H_INCLUDED
