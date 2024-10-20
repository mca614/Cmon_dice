#ifndef CRONOMETRO_H_INCLUDED
#define CRONOMETRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <time.h>
#include <string.h>

#define LIMITE_TIEMPO 10 // tiempo límite en segundos


typedef struct {
    int tiempoAcabado;
    int limiteTiempo;
} t_cronometroDatos;

void* hiloCronometro(void* argumento);

void crearHiloCronometro(pthread_t* cronometro, t_cronometroDatos* datos);

void esperarHiloCronometro(pthread_t* cronometro);

void detenerCronometro(int* stopTimer);

#endif // CRONOMETRO_H_INCLUDED
