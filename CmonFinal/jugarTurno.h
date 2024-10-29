#ifndef JUGARTURNO_H_INCLUDED
#define JUGARTURNO_H_INCLUDED

#define MINIMO(x,y)((x)<(y)? (x):(y))
#define ES_COLOR(c) (((c)=='A' || (c)=='N' || (c)=='R' || (c)=='V'\
                    ||(c)=='a' || (c)=='n' || (c)=='r' || (c)=='v') ? 1 : 0)
#define A_MAYUS(l) ((l) >= 'a' && (l) <= 'z' ? (l) - 32 : (l))

#define TECLA_ESP TECLA_RETRO
#define ES_TECLA_ESP(c) ((c) == TECLA_RETRO ? 1 : 0)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "cmon.h"
#include "estructurasDatos/lista/lista.h"
#include "secuencia/secuencia.h"
#include "secuencia/hiloCronometro.h"


typedef int (*Cmp)( void *, void *);
typedef void (*Accion)( void *, void *);

int cmp_letras( void *, void *);

void mostrarLetraRespuesta( void *dato,  void *cond);

int esSecuenciaCorrecta(t_lista *p1,t_lista *p2,Cmp cmp);
void leer_cant_retroceso_valido(int *cant_retroceso, int vidas, int cant_letras_resp);

/*****  ESTAS FUNCIONES SON SOLO PARA PROBAR LA FUNCION: REEMPLAZAR POR LAS QUE DEPENDEN DEL TIEMPO  *****/
void generarSecuencia(t_lista *secuencia);
void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda , Accion accion);
void mostrarRespuesta(t_lista *respuesta, Accion accion);
void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int cant_max_ingreso, int *cant_letras_resp, int *es_tecla_esp); // actualizado con cronometro
/*********************************************************************************************************/

void jugarTurno(tJugador *jugador, tDatosPartida *datos, Accion mostrar_sec, Accion mostrar_resp, Cmp cmp);

#endif // JUGARTURNO_H_INCLUDED
