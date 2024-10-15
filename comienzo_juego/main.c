#include "comienzoJuego.h"

int main()
{
    t_lista listaJugadores, listaGanadores;
    int cantidadJugadores = 0, comienzaJuego = 0, eligeDificultad = 0, maximaPuntuacion = 0;
    char dificultadElegida[10], opcion = '0';
    tJugador proximoJugador;
    srand(time(NULL));

    crearLista(&listaJugadores);
    crearLista(&listaGanadores);

    opcion = menuConError(
        "[A] Jugar\n"
        "[B] Salir\n"
        "Seleccione una opcion: ", "ABab"
    );

    if(opcion == 'B' || opcion == 'b'){
        printf("\nSaliendo...\n");
        return 0;
    }

    system("cls");

    do{
        menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

        if(siListaVacia(&listaJugadores)){
            opcion = menuConError("\nNo ha ingresado jugadores, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(siListaVacia(&listaJugadores) && opcion == '1');

    system("cls");

    if(siListaVacia(&listaJugadores)){
        printf("\nSaliendo...\n");
        return 0;
    }

    do{
        eligeDificultad = menuDificultad(dificultadElegida);

        if(eligeDificultad == 0){
            system("cls");

            opcion = menuConError("\nNo ha ingresado dificultad, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(eligeDificultad == 0 && opcion == '1');

    if(eligeDificultad == 0){
        vaciarlista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    system("cls");

    printf("\nPosiciones de los jugadores...\n");
    mostrarPosicionesJugadores(&listaJugadores);
    printf("\nConfiguraciones de dificultad...\n");

    if(mostrarConfDificultad(dificultadElegida) == 0){
        vaciarlista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    printf("\nInstrucciones para jugar...\n");

    while(!siListaVacia(&listaJugadores)){
        sacar_primero(&listaJugadores, &proximoJugador, sizeof(tJugador));

        do{
            comienzaJuego = menuComenzarJuego(&listaJugadores, proximoJugador);

            if(comienzaJuego == 0){
                opcion = menuConError("\nDesea no jugar?\n"
                          "1. No\n"
                          "2. Si\n"
                          "Seleccione una opcion: ", "12");
            }

        }while(comienzaJuego == 0 && opcion == '1');

        //jugarPartida(&proximoJugador, &colaRoundsJugador)

        proximoJugador.puntuacion = randomInRange(0, 10);

        if(proximoJugador.puntuacion > maximaPuntuacion)
            maximaPuntuacion = proximoJugador.puntuacion;

        agregarAlFinal(&listaGanadores, &proximoJugador, sizeof(tJugador));
    }

    printf("\nJuego terminado...\n");


    printf("\nPuntuaciones\n");
    mapLista(&listaGanadores, NULL, mostrarJugador);

    eliminarApariciones(&listaGanadores, sizeof(tJugador), &maximaPuntuacion, filtrarNoMaximaPuntuacion);

    printf("\nGanadores\n");
    mapLista(&listaGanadores, NULL, mostrarJugador);

    vaciarlista(&listaGanadores);
    return 0;
}
