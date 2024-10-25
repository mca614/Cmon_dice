#include "listaDinamica.h"

void crearLista(tLista* lista)
{
    *lista = NULL;
}
void vaciarLista(tLista* lista)
{
    tNodo* auxElim;
    while(*lista)
    {
        auxElim = *lista;
        *lista = auxElim->sig;
        free(auxElim->info);
        free(auxElim);
    }
}
int agregarAlInicioDeLista(tLista* lista, void* dato, unsigned tam)
{
    tNodo* nodo = (tNodo*)malloc(sizeof(tNodo));
    if(nodo == NULL)
    {
        return SIN_MEM;
    }
    nodo->info=malloc(tam);
    if(nodo->info == NULL)
    {
        free(nodo);
        return SIN_MEM;
    }

    memcpy(nodo->info,dato,tam);
    nodo->tam = tam;
    nodo->sig = *lista;
    *lista = nodo;
    return 1;
}

int agregarAlFinalDeLista(tLista* lista, void* dato, unsigned tam)
{
    tNodo* nodo = (tNodo*)malloc(sizeof(tNodo));
    if(nodo == NULL)
    {
        return SIN_MEM;
    }
    nodo->info=malloc(tam);
    if(nodo->info == NULL)
    {
        free(nodo);
        return SIN_MEM;
    }

    memcpy(nodo->info,dato,tam);
    nodo->tam = tam;
    nodo->sig = NULL;

    while(*lista)
    {
        lista = &(*lista)->sig;
    }
    *lista = nodo;

    return TODO_OK;
}
int esListaVacia(const tLista* lista)
{
    return *lista == NULL;
}
int compararListas(const tLista* lista1, const tLista* lista2, int cmp (const void* a, const void* b))
{
    tNodo *act1 = *lista1;
    tNodo *act2 = *lista2;
    while(act1 != NULL && act2 != NULL)
    {
        if(cmp(act1->info,act2->info)!=0)
            return 0;

        act1 = act1->sig;
        act2 = act2->sig;
    }
    //LLEGARON AL FINAL SIN SALIR POR ALGUNA DISPARIDAD
    if(act1 == NULL && act2 == NULL)
        return 1;
    //LLEGÓ AL FINAL SOLO UNA LISTA
    return 0;
}
void cargarListaConEnteros(tLista* lista)
{
    int i;
    int vec[]={7,6,5,7,2,3,24,0,11,7,7,7,5,6,7};
    for(i=0;i<sizeof(vec)/sizeof(int);i++)
    {
        agregarAlFinalDeLista(lista,&vec[i],sizeof(int));
    }
}
void cargarListaConSecuencia(tLista* lista, const char* secuencia)
{
    char letra, *act = (char*)secuencia;
    while(*act)
    {
        letra = *act;
        agregarAlFinalDeLista(lista,&letra,sizeof(char));
        act++;
    }
}

void recorrerLista(tLista* lista, void accion(const void*a,const void* b))
{
    while(*lista)
    {
        accion((*lista)->info, NULL);
        lista = &(*lista)->sig;
    }
}

int insertarEnListaOrdenada(tLista* lista, const void* dato, unsigned tamDato, int duplicado, int cmp(const void* a,const void* b))
{
    tNodo* nuevo;

    while((*lista) && (cmp((*lista)->info,(void*)dato)<0))
    {
        lista = &(*lista)->sig;
    }

    if(!duplicado && cmp((*lista)->info,(void*)dato)==0) // *lista != NULL && ... ?
    {
        return 0;
    }

    nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(nuevo == NULL)
    {
        return 0;
    }

    nuevo->info = malloc(tamDato);
    if(nuevo->info == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info,dato,tamDato);
    nuevo->tam = tamDato;

    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}
int eliminarDeListaOrdenadaPorClave(tLista* lista, void* buffer, unsigned tamDato, int cmp(const void* a,const void* b))
{
    tNodo* elim;
    while(*lista && (cmp((*lista)->info,buffer)<0))
    {
        lista = &(*lista)->sig;
    }
    if(*lista && (cmp(buffer,(*lista)->info))==0)
    {
        memcpy(buffer,(*lista)->info,MIN(tamDato,(*lista)->tam));

        elim = *lista;
        *lista = elim->sig;
        free(elim->info);
        free(elim);
        return 1;
    }
    return 0;
}

int eliminarPrimeroDeLista(tLista* l, void* info, unsigned tam_info)
{
    tNodo* elim;
    if(*l==NULL)
        return SIN_INFO;
    else
        {
            elim=*l;
            memcpy(info,(*l)->info,tam_info);
            *l=(*l)->sig;
            free(elim->info);
            free(elim);
        }
    return TODO_OK;
}

void ordenarListaPorSeleccion(tLista* lista, int cmp(const void* a,const void* b),int sentido)
{
    tNodo* minimo = *lista;
    tNodo* actual = *lista;
    while(actual)
    {
        minimo = buscarMenor((tNodo*)actual,cmp,sentido);
        if(minimo != actual)
        {
            intercambiarInfoDeNodos(&minimo->info,&actual->info);
        }
        actual = actual->sig;
    }

}
void intercambiarInfoDeNodos(void** a, void** b)
{
    void* aux = *a;
    *a = *b;
    *b = aux;
}
tNodo* buscarMenor(const tNodo* nodoInicial,int cmp(const void*, const void*),int sentido)
{
    tNodo* minimo = (tNodo*)nodoInicial;
    tNodo* actual = (tNodo*)nodoInicial;
    while(actual)
    {
        if(cmp(minimo->info,actual->info)*sentido>0)
        {
            minimo = actual;
        }
        actual = actual->sig;
    }
    return minimo;
}


