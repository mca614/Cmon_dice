#ifndef TDALISTA_SIMPLEMENTEENLAZADA_D_H_INCLUDED
#define TDALISTA_SIMPLEMENTEENLAZADA_D_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ALUM 30
#define CANT_ALUM 5
#define NODUPLICADO 'N'

typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo * sig;
}t_nodo;

typedef int (*comparacion)(const void*a, const void* b);

typedef void (*resumen) (void* dato, void* info);


typedef t_nodo* t_lista;

void crearLista (t_lista* pl);

void vaciarlista (t_lista* pl);

int siListaVacia (t_lista* pl);

int siListaLlena (t_lista* pl, unsigned cantBytes);

void map_TDAlista (t_lista* pl,void* cond, void accion (void* dato, void* cond));

//insertar

int agregarAlFinal (t_lista* pl, const void* dato, unsigned cantBytes);

int ponerEnOrden (t_lista* pl, const void* dato,unsigned cantBytes, float cmp(const void*a, const void* b),char duplicado);

//eliminar

int eliminarListaOrdenada (t_lista* pl, void* dato, unsigned cantBytes,float cmp(const void*a, const void* b));

void eliminarApariciones (t_lista* pl, void* dato, unsigned cantBytes, comparacion cmp, resumen res);


//ordenar

void intercambiarNodos(t_lista *pl,t_nodo **menor);

t_nodo** buscarMenorLista (t_lista* pl, comparacion cmp);

void ordenarListaDes(t_lista *pl,unsigned tamDato, comparacion cmp);


#endif // TDALISTA_SIMPLEMENTEENLAZADA_D_H_INCLUDED
