#include "jugador.h"

void mostrarPosicionJugador(void *a, void *extra){
    printf("%3s%-12d%s\n", "", ((tJugador*)a)->id , ((tJugador*)a)->nombre);
}

void mostrarPuntuacionJugador(void *a, void *extra){
    printf("%-25s%d\n",((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
}

int cmpJugadores(void *a, void *b){
    tJugador *j1, *j2;
    j1 = (tJugador*)a;
    j2 = (tJugador*)b;

    return j1->id - j2->id;
}

/// Se usa para filtrar de la lista a los jugadores que no son ganadores (no tienen la máxima puntuación o puntuación == 0)
int jugadoresNoGanadores(void *dato, void *info){
    unsigned *maximaPuntuacion = (unsigned*)dato;
    tJugador *jugador = (tJugador*)info;
    /// Se cumple condicion de filtro, devuelve 1 (quita al nodo de la lista)
    /// No se cumple condicion de filtro, devuelve 0 (mantiene al nodo de la lista)
    return  (jugador->puntuacion != *maximaPuntuacion || jugador->puntuacion == 0) ? 1 : 0;
}
