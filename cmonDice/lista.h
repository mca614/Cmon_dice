#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <string.h>
#include <stdlib.h>

typedef struct s_nodo
{
    void *dato;
    unsigned tam;
    struct s_nodo *sig;
}t_nodo;

typedef t_nodo* t_lista;

void crearLista(t_lista *pl);

int insertarAlFinal(t_lista *pl, const void *dato, unsigned tam);
int insertarOrdLista(t_lista *pl, const void *dato, unsigned tam, int (*cmp)(const void *, const void*), int conDu);
void eliminarNnodosLista(t_lista *pl, int cant);

void recorrerLista(t_lista *pl, void (*accion)(const void *, const void *), const void *param);
void vaciarLista(t_lista *pl);
/***************************************  ORDENAR LISTA   ***************************************/
int OrdenarLista(t_lista *pl, unsigned tam, int (*cmp)(const void *, const void*));
t_nodo **buscarMenorNodo(t_lista *pl, int (*cmp)(const void *, const void*));
void intercambiarNodos(t_lista *pl, t_nodo **menor);
/************************************************************************************************/

#endif // LISTA_H_INCLUDED
