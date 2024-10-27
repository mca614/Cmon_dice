#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "../jugador/jugador.h"
#include "../secuencia/secuencia.h"
#include "../cronometro/hiloCronometro.h"
#include "../cola/colaDinamica.h"

#define MAX_L_JUGADOR 50
#define MAX_SECUENCIA 10
#define MINIMO(x,y)((x)<(y)? (x):(y))

#define ES_COLOR(c) (((c)=='A' || (c)=='N' || (c)=='R' || (c)=='V'\
                    ||(c)=='a' || (c)=='n' || (c)=='r' || (c)=='v') ? 1 : 0)
#define A_MAYUS(l) ((l) >= 'a' && (l) <= 'z' ? (l) - 32 : (l))


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
void ingresarSecuencia(t_lista *respuesta, char **respuestaRonda, int tiempo_limite, int cant_max_ingreso, int *cant_letras_resp); // actualizado con cronometro
/*********************************************************************************************************/

void jugarTurno(tJugador* jugador, tCola *colaRondas, int tiempo_mostrar, int tiempo_limite, Accion mostrar_sec, Accion mostrar_resp, Cmp cmp);
#endif // FUNCIONES_H_INCLUDED
