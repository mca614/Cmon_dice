#include "comienzoJuego.h"

int main()
{
    int cantidadJugadores = 0, eligeDificultad = 0;
    char opcion;
    t_lista listaJugadores;
    tDatosPartida datosPartida;
    tJugador jugadorAux;

    srand(time(NULL));
    crearLista(&listaJugadores);

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
        /// Se guarda en variable datosPartida (estructura) en su campo dificultad
        /// un caracter que representa la dificultad elegida por el usuario
        /// (facil F, media M y difícil D)
        eligeDificultad = menuDificultad(&datosPartida);

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

    /// Se carga los datos de dificultad en variable datosPartida (tSecuencia, tJugador, vidas)
    /// desde el archivo config. Si este proceso falla, se términa el juego
    if(cargarDificultad(&datosPartida) == 0){
        vaciarLista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    /// Se cargan datos de los jugadores (id, puntuacion, cantVidas) y se los muestra con sus posiciones (se usa un funcion map)
    /// el campo id se usa ahora para identificar la posicion del jugador dentro de la lista
    printf("\nPosiciones de los jugadores...\n");

    /// Se usa un jugador auxiliar para hacer todo esto
    jugadorAux.id = 1;
    /// Las vidas del jugador se obtienen de la variable datosPartida
    jugadorAux.vidas = datosPartida.cantVidas;
    /// Inicializo puntuacion en 0 para luego hacerlo con todos los jugadores
    jugadorAux.puntuacion = 0;

    mapLista(&listaJugadores, &jugadorAux, cargarMostrarDatosJugador);

    printf(
       "\nInstrucciones para jugar...\n"
       "\nConfiguraciones de dificultad...\n"
       "\nTiempo en que se muestra secuencia: %u"
       "\nTiempo que tiene el jugador para contestar: %u"
       "\nCantidad de vidas del jugador: %u\n",
       datosPartida.tiempoSecuencia, datosPartida.tiempoJugada, datosPartida.cantVidas
    );


    /// Se juega cada partidad de cada jugar a traves de una función map, con jugarPartida como argumento
    /// Se pone el campo maximaPuntuacion de la variable datosPartida en 0 para usarla dentro de la función map
    datosPartida.maximaPuntuacion = 0;
    mapLista(&listaJugadores, &datosPartida, jugarPartida);

    system("cls");
    printf("\nJuego terminado...\n");

    /// Este map se puede eliminar, porque muestra a los jugadores con sus puntajes para comprobar los puntajes
    printf("\n%-21s%s\n", "Nombre", "Puntuacion");
    mapLista(&listaJugadores, NULL, mostrarPuntuacionJugador);

    /// Se realiza filtrado de la lista listaJugadores, pasando como parámetro la lista,
    /// datosPartida.maximaPuntuacion (donde se almacenó la máxima puntuación anteriormente) y
    /// la función jugadoresNoGanadores, que es la función de comparación usada para filtrar a los jugadores
    /// que no tienen la maxima puntuación
    filtrarLista(&listaJugadores, &datosPartida.maximaPuntuacion, jugadoresNoGanadores, NULL);

    /// Se usa función map para mostrar a los ganadores (si existen)
    if(!siListaVacia(&listaJugadores)){
        printf("\nGanadores\n");
        printf("\n%-21s%s\n", "Nombre", "Puntuacion");
        mapLista(&listaJugadores, NULL, mostrarPuntuacionJugador);
    }else
        printf("\nNo hubo ganadores\n");

    vaciarLista(&listaJugadores);
    return 0;
}
