#include "lista.h"

void crearLista(t_lista *pl)
{
    *pl = NULL;
}
int insertarAlFinal(t_lista *pl, const void *dato, unsigned tam)
{
    t_nodo *nue = (t_nodo *)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, sizeof(tam));
    nue->tam = tam;

    nue->sig = NULL;

    while(*pl)
    {
        pl = &(*pl)->sig;
    }

    *pl = nue;

    return 1;
}

void recorrerLista(t_lista *pl, void (*accion)(const void *, const void *param), const void * param)
{
    while(*pl)
    {
        accion((*pl)->dato, param);
        pl = &(*pl)->sig;
    }
}

int insertarOrdLista(t_lista *pl, const void *dato, unsigned tam, int (*cmp)(const void *, const void*), int conDup)
{
    t_nodo *nue;

    while(*pl && cmp(dato, (*pl)->dato)>0) /// ORDENA DE MENOR A MAYOR
    {
        pl = &(*pl)->sig; /// AVANZO
    }

    if(*pl && cmp(dato, (*pl)->dato)==0 && conDup == 0)
        return 1;

    nue = (t_nodo *)malloc(sizeof(t_nodo));
    if(!nue)
        return 0;
    nue->dato = malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->dato, dato, sizeof(tam));
    nue->tam = tam;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}

void vaciarLista(t_lista *pl)
{
    t_nodo *elim;
    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->dato);
        free(elim);
    }
}

int OrdenarLista(t_lista *pl, unsigned tam, int (*cmp)(const void *, const void*))
{
    t_nodo **menor;

    if(!*pl)
        return 0;/// LISTA VACIA

    while(*pl)
    {
        menor = buscarMenorNodo(pl, cmp);
        if(menor!=pl)
            intercambiarNodos(pl, menor);
        pl = &(*pl)->sig;
    }
    return 1;
}

t_nodo **buscarMenorNodo(t_lista *pl, int (*cmp)(const void *, const void*))
{
    t_nodo **menor = pl;

    pl = &(*pl)->sig;

    while(*pl)
    {
        if(cmp((*pl)->dato, (*menor)->dato)<0)
            menor = pl;
        pl = &(*pl)->sig;
    }

    return menor;
}

void intercambiarNodos(t_lista *pl, t_nodo **menor)
{
    t_nodo *aux;

    aux = *menor;
    *menor = *pl;
    *pl = aux;

    aux = (*pl)->sig;
    (*pl)->sig = (*menor)->sig;
    (*menor)->sig = aux;
}
