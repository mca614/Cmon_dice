#ifndef FUNCIONESJUEGO_H_INCLUDED
#define FUNCIONESJUEGO_H_INCLUDED

#include <curl/curl.h>
#include <time.h>
#include "colaDinamica.h"
#include "listaDinamica.h"

#define MISMO_PUNTAJE 0
#define MAX_TAM_RESP 1024
#define MAX_TAM_URL 500
#define MAX_TAM_PATH 50
#define MAX_L_JUGADOR 25

typedef struct {
    char *cadena;
    size_t tam;
}tRespuesta;

typedef struct{
    int id;
    char nombre[MAX_L_JUGADOR];
    int vidas;
    int puntuacion;
}tJugador;

typedef struct{
    int id;
    char* secuencia;
    char* respuesta;
    unsigned vidasUsadas;
    unsigned puntosObtenidos;
}tRonda;

size_t WriteCallback(void *datosRespuesta, size_t tamBloque, size_t bloques, void *info);
int realizarSolicitud(char *url, char *respuesta);
void convertirCadenaNumeros(int *numeros, char *cadena);
int obtenerNumerosAleatorios(int *numeros, int cantidad, int min, int max);

//GANADORES
void buscarJugadorMayorPuntuacion(tLista* jugadores,tJugador* jug,unsigned tam_info);
int buscarPuntaje(const tLista *jugadores, int maxPuntaje,tJugador* aux);
void mostrarGanadores(tLista* jugadores);
//ARCHIVOS

FILE* generarArchivoDeInforme(const char* nombrePrefijo);
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno);
void exportarGanadoresHaciaInforme(FILE* archInforme, tLista* ganadores);

int generarInformeDeJuego(tCola* cola);

void mostrarCaracter(const void* a,const void* b);
int cmpCaracter(const void* a, const void* b);

#endif // FUNCIONESJUEGO_H_INCLUDED