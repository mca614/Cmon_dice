#include "colaDinamica.h"

#define MIN(x,y) (((x)<(y))? (x) : (y))

void crearCola(tCola* cola)
{
    cola->pri = NULL;
    cola->ult = NULL;
}
int colaVacia(const tCola* cola)
{
    return cola->pri == NULL;
}
int colaLlena(const tCola* cola, unsigned tam)
{
    t_nodo* nodoAux = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nodoAux)
    {
        return 1;
    }
    nodoAux->info = malloc(tam);
    if(!nodoAux->info)
    {
        free(nodoAux);
        return 1;
    }
    free(nodoAux->info);
    free(nodoAux);
    return 0;
}

int ponerEnCola(tCola* cola, unsigned tam, const void* info)
{
    t_nodo* nue = (t_nodo*)malloc(sizeof(t_nodo)); //Nodo nuevo
    if(!nue)
    {
        return 0;
    }
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info,info,tam);
    nue->tamInfo = tam;
    nue->sig = NULL;

    if(cola->pri == NULL)
    {
        cola->pri = nue;
    }
    else
    {
        cola->ult->sig = nue;
    }
    cola->ult = nue;

    return 1;
}
int sacarDeCola(tCola* cola, unsigned tamBuffer, void* buffer)
{
    t_nodo* auxElim;
    if(cola->pri==NULL)
    {
        return 0;
    }

    auxElim = cola->pri;
    memcpy(buffer,auxElim->info,MIN(tamBuffer,auxElim->tamInfo));
    cola->pri = auxElim->sig;

    free(auxElim->info);
    free(auxElim);

    if(cola->pri==NULL)
    {
        cola->ult = NULL;
    }
    return 1;
}
int verPrimero(const tCola* cola, unsigned tamBuffer, void* buffer)
{
    if(cola->pri == NULL)
    {
        buffer = NULL;
        return 0;
    }
    memcpy(buffer,cola->pri,MIN(tamBuffer,cola->pri->tamInfo));
    return 1;
}
void vaciarCola(tCola* cola)
{
    t_nodo* auxElim;
    while(cola->pri)
    {
        auxElim = cola->pri;
        cola->pri = auxElim->sig;
        free(auxElim->info);
        free(auxElim);
    }
    cola->ult = NULL;
}
int cargarArchivoBinarioEnCola(tCola* cola, const char* path, unsigned tam)
{
    void* buffer;
    FILE* pf = fopen(path,"rb");
    if(pf == NULL)
    {
        return 0;
    }
    buffer = malloc(tam);
    if(buffer == NULL)
    {
        fclose(pf);
        return 0;
    }
    fread(buffer,tam,1,pf);
    while(!feof(pf))
    {
        ponerEnCola(cola,tam,buffer);
        fread(buffer,tam,1,pf);
    }
    fclose(pf);
    return 1;
}
int recorrerYMostrarColaUniforme(tCola* cola,void accion(const void* a),unsigned tam)
{
    void* buffer = malloc(tam);
    if(buffer == NULL)
    {
        return 0;
    }
    while(!colaVacia(cola))
    {
        sacarDeCola(cola,tam,buffer);
        accion(buffer);
    }
    return 1;
}

