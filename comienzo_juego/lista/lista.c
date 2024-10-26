#include "lista.h"

void eliminarNnodosLista(t_lista *pl, int cantElim, int cantElem)
{
    t_nodo *elim;
    int pos = cantElem - cantElim;

    while(*pl && pos)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}


void crearLista (t_lista* pl)
{
    *pl = NULL;
}

void vaciarLista (t_lista* pl)
{
    t_nodo*elim;


    while(*pl != NULL)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int siListaVacia (const t_lista* pl)
{
    return *pl == NULL;
}

int agregarAlFinal (t_lista* pl, const void* dato, unsigned cantBytes)
{
    t_nodo* nue;

    while(*pl!=NULL)
    {
        pl = &(*pl)->sig;
    }

    if(!(nue = (t_nodo*)malloc(sizeof(t_nodo))))
        return 0;

    if(!(nue->info = malloc (cantBytes)))
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->sig = NULL;
    nue->tamInfo = cantBytes;
    *pl=nue;

    return 1;
}

void mapLista (const t_lista* pl, void* cond, void accion (void* dato, void* dato2))
{
    while(*pl!= NULL)
    {
        accion((*pl)->info,cond);
        pl = &(*pl)->sig;
    }
}

int buscarPorValor(const t_lista *p_lista, void *objetivo, unsigned cantBytes, int comparar(const void *a, const void *b)){
    while(*p_lista){
        if(comparar((*p_lista)->info, objetivo) == 0){
            memcpy(objetivo, (*p_lista)->info, MENOR((*p_lista)->tamInfo, cantBytes));
            return 1;
        }

        p_lista = &(*p_lista)->sig;
    }

    return 0;
}

int agregarOrdenado(t_lista *lista, void *dato, short int duplicado, unsigned cant_bytes, int funComparar(void*, void*)){
    while(*lista && funComparar(dato, (*lista)->info) > 0){
        lista = &(*lista)->sig;
    }

    if(*lista && !duplicado && funComparar(dato, (*lista)->info) == 0)
        return 0; //Error al intentar ingresar un dato duplicado

    t_nodo *nuevo = malloc(sizeof(t_nodo));

    if(!nuevo){
        return 0; //Error en reserva de memoria
    }

    nuevo->info = malloc(cant_bytes);

    if(!nuevo->info){
        return 0; //Error en reserva de memoria
    }

    memcpy(nuevo->info, dato, cant_bytes);
    nuevo->tamInfo = cant_bytes;
    nuevo->sig = *lista;
    *lista = nuevo;
    return 1; //Todo bien
}

int sacarPrimero(t_lista *lista, void *dato, unsigned cant_bytes){
    t_nodo *elim = *lista;

    if(*lista == NULL){
        return 0;
    }

    *lista = elim->sig;
    memcpy(dato, elim->info, MENOR(cant_bytes, elim->tamInfo));
    free(elim->info);
    free(elim);
    return 1;
}

/// El parámetro condicion, es la funcion que determina si se elimina el nodo
/// en este caso es la funcion jugadoresNoGanadores, que retorna un 1 en cuando el jugador tiene una puntacion
/// distinta a la maxima o cuando esta es 0
/// el parámetro accion no se usa
void filtrarLista(t_lista* pl, void* dato, int condicion(void*, void*), void accion(void*, void*)){
    t_nodo *elim;

     while(*pl)
     {
         if(condicion(dato,(*pl)->info))
         {
            elim = *pl;
            if(accion)
                accion(dato, elim->info);
            *pl = (elim)->sig;
            free(elim->info);
            free(elim);
         }else
            pl = &(*pl)->sig;
     }
}
