#ifndef FUNCIONESJUEGO_H_INCLUDED
#define FUNCIONESJUEGO_H_INCLUDED

#include <curl/curl.h>
#include <time.h>
#include "colaDinamica.h"
#include "listaDinamica.h"

#define MAX_TAM_RESP 1024
#define MAX_TAM_URL 500
#define MAX_TAM_PATH 50

typedef struct {
    char *cadena;
    size_t tam;
}tRespuesta;

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

FILE* generarArchivoDeInforme(const char* nombrePrefijo);
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno);
int exportarGanadoresHaciaInforme(FILE* archInforme, tLista* ganadores);

int generarInformeDeJuego(tCola* cola);

void mostrarCaracter(const void* a,const void* b);
int cmpCaracter(const void* a, const void* b);

#endif // FUNCIONESJUEGO_H_INCLUDED
