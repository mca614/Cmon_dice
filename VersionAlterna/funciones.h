#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "secuencia/secuencia.h"
#include <stdlib.h>
#include <conio.h>

#define MAX_L_JUGADOR 50
#define MAX_SECUENCIA 10

#define ES_COLOR(c) (((c)=='A' || (c)=='N' || (c)=='R' || (c)=='V'\
                    ||(c)=='a' || (c)=='n' || (c)=='r' || (c)=='v') ? 1 : 0)


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

int cmp_letras(const void *,const void *);

void mostrarLetraRespuesta(const void *dato, const void *cond);

int esSecuenciaCorrecta(t_lista *p1,t_lista *p2,Cmp cmp);
void leer_cant_retroceso_valido(int *cant_retroceso, int vidas, int cant_letras_resp);

/*****  ESTAS FUNCIONES SON SOLO PARA PROBAR LA FUNCION: REEMPLAZAR POR LAS QUE DEPENDEN DEL TIEMPO  *****/
void generarSecuencia(t_lista *secuencia);
void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda , Accion accion);
void mostrarRespuesta(t_lista *respuesta, Accion accion);
void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int cant_max_ingreso, int *cant_letras_resp);
/*********************************************************************************************************/

void jugarTurno(tJugador* jugador, int tiempo_mostrar, int tiempo_limite, Accion mostrar_sec,
                Accion mostrar_resp, Cmp cmp);
#endif // FUNCIONES_H_INCLUDED
