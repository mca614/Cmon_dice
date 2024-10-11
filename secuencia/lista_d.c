#include "lista_d.h"


void crearLista (t_lista* pl)
{
    *pl = NULL;
}

void vaciarlista (t_lista* pl)
{
    t_nodo*elim;


    while(*pl == NULL)
    {
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int siListaVacia (t_lista* pl)
{
    return *pl == NULL;
}

int siListaLlena (t_lista* pl, unsigned cantBytes)
{
    return 0;
}

int agregarAlFinal (t_lista* pl, const void* dato, unsigned cantBytes)
{
    t_nodo* nue;

    if(!(nue = (t_nodo*)malloc(sizeof(t_nodo))))
        return 0;

    if(!(nue->info = malloc (cantBytes)))
    {
        free(nue);
        return 0;
    }

    while(*pl!= NULL)
    {
        pl = &(*pl)->sig;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->sig = NULL;
    nue->tamInfo = cantBytes;

    *pl=nue;

    return 1;
}

void map_TDAlista (t_lista* pl,void* cond, void accion (void* dato, void* dato2))
{
    while(*pl!= NULL)
    {
        accion((*pl)->info,cond);
        pl = &(*pl)->sig;
    }
}

int ponerEnOrden (t_lista* pl, const void* dato,unsigned cantBytes, float cmp(const void*a, const void* b), char duplicado)
{
    t_nodo * nue;

    while(*pl !=NULL && cmp((*pl)->info, dato) <0)
    {
        pl = &(*pl)->sig;
    }

    if(duplicado == NODUPLICADO && *pl !=NULL && cmp((*pl)->info, dato) == 0)
        return 0;

    if(!(nue= (t_nodo*)malloc (sizeof(t_nodo))))
        return 0;
    if(!(nue->info = malloc (cantBytes)))
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, dato, cantBytes);
    nue->tamInfo = cantBytes;

    nue->sig = *pl;
    *pl = nue;

    return 1;
}

int eliminarListaOrdenada (t_lista* pl, void* dato, unsigned cantBytes,float cmp(const void*a, const void* b))
{
    t_nodo* elim;

    while(*pl && cmp(dato,(*pl)->info)>0)
    {
        pl = &(*pl)->sig;
    }
    if(!pl || cmp(dato,(*pl)->info)!=0 )
        return 0;

    elim = *pl;

    memcpy(dato, elim->info, cantBytes);

    *pl = (elim)->sig;

    free(elim->info);
    free(elim);

    return 1;
}

void eliminarApariciones (t_lista* pl, void* dato, unsigned cantBytes, comparacion cmp, resumen res)
{
    t_nodo*elim;

     while(*pl)
     {
         if(cmp(dato,(*pl)->info)==0)
         {
            elim = *pl;
            res(dato,elim->info);
            *pl = (elim)->sig;
            free(elim->info);
            free(elim);
         }
         pl = &(*pl)->sig;
     }
}

void ordenarListaDes(t_lista *pl,unsigned tamDato, comparacion cmp)
{

    t_nodo**menor;

    while(*pl!=NULL)
    {
        menor = buscarMenorLista(pl,cmp);
        if(menor!=pl)
            intercambiarNodos(pl,menor);

        pl=&(*pl)->sig;
    }
}

t_nodo** buscarMenorLista (t_lista* pl, comparacion cmp)
{
    t_nodo** menor = pl;
    pl=&(*pl)->sig;

    while(*pl)
    {

        if(cmp((*pl)->info,(*menor)->info) < 0)
            menor = pl;
        pl= &((*pl)->sig);
    }

    return menor;
}

void intercambiarNodos(t_lista *pl,t_nodo **menor)
{
    //puntero que ve el nodo
   t_nodo *aux = *menor;
   *menor = *pl;
   *pl=aux;

    //cambiar los punteros de siguiente
   aux = (*pl)->sig;
   (*pl)->sig = (*menor)->sig;
   (*menor)->sig =aux;

}
