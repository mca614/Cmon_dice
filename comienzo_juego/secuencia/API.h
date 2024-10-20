#ifndef API_H_INCLUDED
#define API_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>  // Función que maneja la respuesta de la solicitud HTTP
#define MAX_TAM_RESP 1024
#define MAX_TAM_URL 500

typedef struct {
    char *cadena;
    size_t tam;
}tRespuesta;

size_t WriteCallback(void *datosRespuesta, size_t tamBloque, size_t bloques, void *info);

int realizarSolicitud(char *url, char *respuesta);

int obtenerNumerosAleatorios(int *numeros, int cantidad, int minimo, int maximo);

void convertirCadenaNumeros(int *numeros, char *cadena);

#endif // API_H_INCLUDED
