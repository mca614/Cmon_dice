#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../../../../Desktop/algoritmo/biblioteca/Lista/lista.h"

typedef int (*Cmp)(const void *,const void *);

int asignarPuntaje(t_jugador);
int compararListas(t_lista *pl,t_lista *pl2,Cmp cmp);
int compararCaracteres(const void *,const void *);



#endif // FUNCIONES_H_INCLUDED
