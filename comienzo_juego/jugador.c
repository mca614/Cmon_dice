#include "jugador.h"

void mostrarCargarId(void *a, void *extra){
    ((tJugador*)a)->id = (*((int*)extra));
    (*((int*)extra))++;

    printf("%4d%35s\n", ((tJugador*)a)->id , ((tJugador*)a)->nombre);
}

void mostrarJugador(void *a, void *extra){
    printf("Nombre: %s - Puntuacion: %d\n", ((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
}

int cmpJugadores(void *a, void *b){
    tJugador *j1, *j2;
    j1 = (tJugador*)a;
    j2 = (tJugador*)b;

    return j1->id - j2->id;
}

int jugadoresNoGanadores(void *dato, void *info){
    int maximaPuntuacion = ((tJugador*)dato)->puntuacion;
    tJugador *jugador = (tJugador*)info;

    return  (jugador->puntuacion != maximaPuntuacion || jugador->puntuacion == 0) ? 1 : 0;
}

int randomInRange(int menorValor, int mayorValor) {
    return (rand() % (mayorValor - menorValor + 1)) + menorValor;
}

void mostrarPosicionesJugadores(t_lista *listaJugadores){
    int id = 1;

    printf("\n%s%35s\n", "Posicion", "Nombre Jugador");
    mapLista(listaJugadores, &id, mostrarCargarId);
}

void ingresarJugador(tJugador *jugador, int cantidadJugadores){
    char *pNombre = jugador->nombre;

    fgets(pNombre, MAX_L_JUGADOR, stdin);
    pNombre = strrchr(pNombre, '\n');
    *pNombre = '\0';

    jugador->id = randomInRange(cantidadJugadores * -1, cantidadJugadores);
    jugador->puntuacion = 0;
    system("cls");
}


