#ifndef LISTADINAMICA_H_INCLUDED
#define LISTADINAMICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TODO_OK 0
#define SIN_MEM 1
#define MIN(x,y) ((x)<=(y)? (x) : (y))
#define ASC 1
#define DESC -1

typedef struct s_nodo
{
    unsigned tam;
    void* info;
    struct s_nodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
void vaciarLista(tLista* lista);
int esListaVacia(const tLista* lista);
int compararListas(const tLista* lista1, const tLista* lista2, int cmp (const void* a, const void* b));
void cargarListaConEnteros(tLista* lista);
void cargarListaConSecuencia(tLista* lista, const char* secuencia);

int agregarAlInicioDeLista(tLista* lista, void* dato, unsigned tam);
int agregarAlFinalDeLista(tLista* lista, void* dato, unsigned tam);
int insertarEnListaOrdenada(tLista* lista, const void* dato, unsigned tamDato, int duplicado, int cmp(const void* a,const void* b));

void recorrerLista(tLista* lista, void accion(const void*a,const void*b));

int eliminarDeListaOrdenadaPorClave(tLista* lista, void* buffer, unsigned tamDato, int cmp(const void* a,const void* b));

void ordenarListaPorSeleccion(tLista* lista, int cmp(const void* a,const void* b),int sentido);
tNodo* buscarMenor(const tNodo* nodoInicial, int cmp(const void*, const void*),int sentido);
void intercambiarInfoDeNodos(void** a, void** b);

void accion(void*a, void*b);

#endif // LISTADINAMICA_H_INCLUDED
