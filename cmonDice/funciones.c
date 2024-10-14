#include "funciones.h"
int esSecuenciaCorrecta(t_lista *pl,t_lista *pl2,Cmp cmp){

    while(*pl && *pl2 && cmp((*pl)->dato,(*pl2)->dato)==0)
    {
        pl=&(*pl)->sig;
        p2=&(*p2)->sig;
    }

    if(*pl==NULL && *pl2==NULL)
        return 1;

   return 0;
}

}
int compararCaracteres(const void *a,const void *b){

    return *(char*a)- *(char*b);
}

int comenzoElJuego(tJugador *jugador, t_lista *secuencia)
{
    obtenerSecuencia(secuencia);
    mostrarSecuencia(secuencia);
    t_lista respuesta;
    char *cadenaRespuesta;

    crearLista(&respuesta);

    while(jugador->vidas > 0)
    {
        printf("Ingrese secuencia");
        fflush(stdin);
        gets(cadenaRespuesta);

        obtenerSecuencia(secuencia);
        mostrarSecuencia(secuencia);
    }

}

int asignarPuntaje(tJugador *jugador, t_lista *secuencia, t_lista *respuesta,int utilizoVida,Cmp cmp)
{

    int contPuntaje=0;

    if(esSecuenciaCorrecta(secuencia,respuesta,cmp)&& !utilizoVida)
    {
        jugador->puntaje+=3;
    }
    else
    {   if(esSecuenciaCorrecta(secuencia,respuesta,cmp)&& utilizoVida)
            jugador->puntaje+=1;

        else jugador->puntaje+=0;

    }



}
