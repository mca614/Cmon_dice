#include "lista.h"

void crearLista (t_lista* pl)
{
    *pl = NULL;
}

void vaciarlista (t_lista* pl)
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

int sacar_primero(t_lista *lista, void *dato, unsigned cant_bytes){
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

void eliminarApariciones (t_lista* pl, unsigned cantBytes, void *extra, int funFiltrar(void*, void*))
{
    t_nodo*elim;

     while(*pl)
     {
         if(funFiltrar((*pl)->info, extra))
         {
            elim = *pl;
            //res(dato,elim->info);
            *pl = (elim)->sig;
            free(elim->info);
            free(elim);
         }
         pl = &(*pl)->sig;
     }
}
