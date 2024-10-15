#include "jugador.h"

void mostrarCargarPosicion(void *a, void *extra){
    int *posicion = (int*)extra;
    ((tJugador*)a)->posicion = *posicion;
    (*posicion)++;

    printf("%4d%35s\n", ((tJugador*)a)->posicion , ((tJugador*)a)->nombre);
}

void mostrarJugador(void *a, void *extra){
    printf("Nombre: %s - Puntuacion: %d\n", ((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
}

int cmpJugadores(void *a, void *b){
    tJugador *j1, *j2;
    j1 = (tJugador*)a;
    j2 = (tJugador*)b;

    return j1->orden - j2->orden;
}

int filtrarNoMaximaPuntuacion(void *a, void *extra){
    return ((tJugador*)a)->puntuacion == *((int*)extra) ? 0 : 1;
}

int randomInRange(int menorValor, int mayorValor) {
    return (rand() % (mayorValor - menorValor + 1)) + menorValor;
}

void mostrarPosicionesJugadores(t_lista *listaJugadores){
    int posicion = 1;

    printf("\n%s%35s\n", "Posicion", "Nombre Jugador");
    mapLista(listaJugadores, &posicion, mostrarCargarPosicion);
}

void ingresarJugador(tJugador *jugador, int cantidadJugadores){
    char *pNombre = jugador->nombre;

    fgets(pNombre, MAX_L_JUGADOR, stdin);
    pNombre = strrchr(pNombre, '\n');
    *pNombre = '\0';

    jugador->orden = randomInRange(cantidadJugadores * -1, cantidadJugadores);
    jugador->puntuacion = 0;
    system("cls");
}


