#include "comienzoJuego.h"

int main()
{
    t_lista listaJugadores, listaGanadores;
    int cantidadJugadores = 0, comienzaJuego = 0, eligeDificultad = 0, maximaPuntuacion = 0;
    tDificultad dificultadElegida;
    char opcion;
    tJugador jugador;

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
        /// Ingresa de forma ordenada a listaJugadores un jugador según su valor del campo id,
        /// que es generado de forma aleatoria
        menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

        if(siListaVacia(&listaJugadores)){
            opcion = menuConError("\nNo ha ingresado jugadores, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(siListaVacia(&listaJugadores) && opcion == '1');

    system("cls");

    /// Si no se ha ingresado ningún jugador, se términa el juego
    if(siListaVacia(&listaJugadores)){
        printf("\nSaliendo...\n");
        return 0;
    }

    do{
        /// Se guarda en variable dificultadElegida (estructura) en su campo dificultad
        /// una cadena de caracteres que representa la dificultad elegida por el usuario
        /// (facil, media o difícil)
        eligeDificultad = menuDificultad(&dificultadElegida);

        if(eligeDificultad == 0){
            system("cls");

            opcion = menuConError("\nNo ha ingresado dificultad, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(eligeDificultad == 0 && opcion == '1');


    /// Si el usuario no ha elegido dificultad, se términa el juego
    if(eligeDificultad == 0){
        vaciarLista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    system("cls");

    /// Se carga los datos de dificultad en variable dificultadElegida (tSecuencia, tJugador, vidas)
    /// desde el archivo config. Si este proceso falla, se términa el juego
    if(cargarDificultad(&dificultadElegida) == 0){
        vaciarLista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    printf("\nPosiciones de los jugadores...\n");

    /// Se cargan los datos de cada jugador antes de comenzar el juego
    /// el campo id ahora es usado para identificar posición del jugador en la lista
    /// Se pone puntuacion en 0. Se completa el campo vidas según la dificultad elegida (variable dificultadElegida)
    cargarDatosJugadores(&listaJugadores, dificultadElegida.cantVidas);

    /// Se muestran las posiciones de los jugadores
    printf("\n%-15s%s\n", "Posicion", "Nombre Jugador");
    mapLista(&listaJugadores, NULL, mostrarPosicionJugador);

    /// Recorre lista listaJugadores usando función sacarPrimero()
    /// Luego se muestra configuración de dificultad e instrucciones para jugar
    /// Se le pregunta al jugador si desea comenzar. Luego, empieza el turno del jugador
    while(!siListaVacia(&listaJugadores)){
        /// Se guarda info del nodo de la lista en variable jugador (estructura tJugador)
        sacarPrimero(&listaJugadores, &jugador, sizeof(tJugador));

        do{
            printf("\nConfiguraciones de dificultad...\n");

            printf(
               "\nNivel dificultad: %s"
               "\nTiempo en que se muestra secuencia: %u"
               "\nTiempo que tiene el jugador para contestar: %u"
               "\nCantidad de vidas del jugador: %u\n", dificultadElegida.dificultad, dificultadElegida.tiempoSecuencia,
                dificultadElegida.tiempoJugada, dificultadElegida.cantVidas
            );

            printf("\nInstrucciones para jugar...\n");

            comienzaJuego = menuComenzarJuego(jugador);

            if(comienzaJuego == 0){
                opcion = menuConError("\nDesea no jugar?\n"
                          "1. No\n"
                          "2. Si\n"
                          "Seleccione una opcion: ", "12");
            }

            system("cls");

        }while(comienzaJuego == 0 && opcion == '1');

        /// Si el jugador a decidido comenzar se ejecuta la funcion jugarTurno
        /// que es donde se desarrolla la partida del jugador
        /// Si ha decidido no jugar, continua el siguiente jugador

        if(comienzaJuego){
            jugarTurno(&jugador, dificultadElegida.tiempoSecuencia, dificultadElegida.tiempoJugada, mostrarLetra, cmp_letras);

            if(jugador.puntuacion > maximaPuntuacion)
                maximaPuntuacion = jugador.puntuacion;
        }

        /// Agrega a todos los jugadores a la lista listaJugadores
        agregarAlFinal(&listaGanadores, &jugador, sizeof(tJugador));
    }

    system("cls");
    printf("\nJuego terminado...\n");

    /// Muestra todos los jugadores con sus puntajes
    /// Lo dejo solo para comprobar si se hace bien la parte de hallar a los ganadores
    /// que viene a continuación
    printf("\n%-21s%s\n", "Nombre", "Puntuacion");
    mapLista(&listaGanadores, NULL, mostrarPuntuacionJugador);

    /// Uso la variable jugador (guardo la máxima puntuación en su campo puntuación),
    /// que ya no se usa para agregar jugadores, como paramétro en la funcion filtrarLista
    /// puntuación para filtrar a los jugadores que no tienen la máxima puntuación
    jugador.puntuacion = maximaPuntuacion;
    filtrarLista(&listaGanadores, &jugador, sizeof(tJugador), jugadoresNoGanadores, NULL);

    /// Si hay ganadores (listaGanadores no es vacia) muestra a los ganadores con sus puntuaciones
    if(!siListaVacia(&listaGanadores)){
        printf("\nGanadores\n");
        printf("\n%-21s%s\n", "Nombre", "Puntuacion");
        mapLista(&listaGanadores, NULL, mostrarPuntuacionJugador);
    }else
        printf("\nNo hubo ganadores\n");

    vaciarLista(&listaGanadores);
    return 0;
}
