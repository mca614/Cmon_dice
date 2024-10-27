#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../nodo.h"

#define MENOR(a, b) ((a) < (b) ? (a) : (b))

typedef t_nodo* t_lista;

void crearLista (t_lista* pl);
void vaciarLista (t_lista* pl);
int siListaVacia (const t_lista* pl);
void mapLista (const t_lista* pl, void* cond, void accion (void* dato, void* dato2));
int ver_primero(t_lista *lista, void *dato, unsigned cant_bytes);

// insertar
int agregarAlFinal (t_lista* pl, const void* dato, unsigned cantBytes);
int agregarOrdenado(t_lista *lista, void *dato, short int duplicado, unsigned cant_bytes, int funComparar(void*, void*));

// eliminar
int sacarPrimero(t_lista *lista, void *dato, unsigned cant_bytes);
void eliminarNnodosLista(t_lista *pl, int cantElim, int cantElem);

// filtrar
void filtrarLista(t_lista* pl, void* dato, int condicion(void*, void*), void accion(void*, void*));

#endif // LISTA_H_INCLUDED
