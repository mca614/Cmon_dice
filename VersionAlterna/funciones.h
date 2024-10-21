#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"

#define MAX_L_JUGADOR 50
#define MAX_SECUENCIA 10
#define ES_NUMERO(x) ((x)>= '0' && (x)<='9')?

typedef struct
{
    int orden,
        posicion,
        puntuacion,
        vidas;
    char nombre[MAX_L_JUGADOR];
}tJugador;

typedef int (*Cmp)(const void *,const void *);
typedef void (*Accion)(const void *,const void *);

void mostrarLetra(const void *d, const void *param);
int cmp_letras(const void *,const void *);
int esSecuenciaCorrecta(t_lista *p1,t_lista *p2,Cmp cmp);

/*****  ESTAS FUNCIONES SON SOLO PARA PROBAR LA FUNCION: REEMPLAZAR POR LAS QUE DEPENDEN DEL TIEMPO  *****/
void generarSecuencia(t_lista *secuencia);
void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda , Accion accion);
void mostrarRespuesta(t_lista *respuesta, Accion accion);
void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int *cant_letras_resp);
/*********************************************************************************************************/

void jugarTurno(tJugador* jugador, int tiempo_mostrar, int tiempo_limite, Accion accion, Cmp cmp);

#endif // FUNCIONES_H_INCLUDED
