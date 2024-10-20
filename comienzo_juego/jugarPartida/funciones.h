#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../lista.h"
#include "../jugador.h"

#define MAX_SECUENCIA 10

typedef int (*Cmp)(const void *,const void *);
typedef void (*Accion)( void *, void *);

//void mostrarLetra( void *d,  void *param);
int cmp_letras(const void *,const void *);
int esSecuenciaCorrecta(t_lista *p1,t_lista *p2,Cmp cmp);

/*****  ESTAS FUNCIONES SON SOLO PARA PROBAR LA FUNCION: REEMPLAZAR POR LAS QUE DEPENDEN DEL TIEMPO  *****/
void generarSecuencia(t_lista *secuencia);
void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda, Accion accion);
void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int *cant_letras_resp);
/*********************************************************************************************************/

void jugarTurno(tJugador* jugador, int tiempo_mostrar, int tiempo_limite, Accion accion, Cmp cmp);


#endif // FUNCIONES_H_INCLUDED
