#include "cmon.h"

int main()
{
    tJugador jugadorAux;
    t_lista listaJugadores;
    tDatosPartida datosPartida;
    char nombreArchivo[MAX_TAM_PATH];
    char opcion = '0';
    unsigned eligeDificultad = 0;
    unsigned cantidadJugadores = 0;

    ///Generar archivo config.txt
    if(!generarArchivoConf()){
        printf("\nSaliendo...");
        return 0;
    }

    crearLista(&listaJugadores);
    centrarVentanaConsola();
    ajustarConsola(80,38,45,25);

    bienvenidoSimonDice();
    colorFondo(VIOLETA_4, VIOLETA_0);

    opcion = menuConError(
        "\n==============================================\n"
        "\t\tCMON DICE\n"
        "==============================================\n"
        "[A] Jugar\n"
        "[B] Salir\n"
        "Seleccione una opcion: ", "ABab"
    );

    if(opcion == 'B' || opcion == 'b'){
        printf("\nSaliendo...\n");
        return 0;
    }

    do{
        /// Menu ingreso de jugadores
        menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

        if(siListaVacia(&listaJugadores)){
            opcion = menuConError("\nNo ha ingresado jugadores, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(siListaVacia(&listaJugadores) && opcion == '1');

    if(siListaVacia(&listaJugadores)){
        printf("\nSaliendo...");
        return 0;
    }

    /// Menu dificultad
    do{
        eligeDificultad = menuDificultad(&datosPartida);

        if(eligeDificultad == 0){
            system("cls");

            opcion = menuConError("\nNo ha ingresado dificultad, desea salir?\n"
                              "1. No\n"
                              "2. Si\n"
                              "Seleccione una opcion: ", "12");
        }

    }while(eligeDificultad == 0 && opcion == '1');

    if(eligeDificultad == 0){
        vaciarLista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    /// Cargar datos dificultad de archivo config
    if(cargarDificultad(&datosPartida) == 0){
        vaciarLista(&listaJugadores);
        printf("\nSaliendo...\n");
        return 0;
    }

    colorFondo(VIOLETA_4, VERDE_MUYCLARO);

    /// Cargar datos de jugadores y mostrar posiciones
    printf("\nPosiciones de los jugadores...\n");
    jugadorAux.id = 1;
    jugadorAux.puntuacion = 0;
    jugadorAux.vidas = datosPartida.cantVidas;
    mapLista(&listaJugadores, &jugadorAux, cargarMostrarDatosJugador);

    puts("\n");
    system("pause");
    colorFondo(VIOLETA_4, COLOR_ROJO_5);

    /// Muestra las configuraciones del juego
    printf(
        "\nInstrucciones para jugar...\n"
        "\nEscriba la secuencia mostrada usando las teclas A, R, V, N.\n"
        "Para volver n letras durante el ingreso apriete la tecla retroceso o backspace.\n"
        "\nConfiguraciones de dificultad...\n"
        "\nTiempo en que se muestra secuencia: %u"
        "\nTiempo que tiene el jugador para contestar: %u"
        "\nCantidad de vidas del jugador: %u\n",
        datosPartida.tiempoSecuencia, datosPartida.tiempoRespuesta, datosPartida.cantVidas
    );

    puts("\n");
    system("pause");

    /// Generar archivo informe
    /// Debe estar creada la carpeta historial
    datosPartida.archInforme = generarArchivoDeInforme("historialPartidas/informe-juego", nombreArchivo);

    /// Reproducir Musica (VERIFICAR QUE -lwinmm EST� AGREGADO COMO PAR�METRO EN BUILD OPTIONS > LINKER SETTINGS > OTHER LINK OPTIONS
    reproducirMusica(MUSICA3);

    colorFondo(VIOLETA_4, VERDE_CLARO);
    /// Jugar partidas
    datosPartida.maximaPuntuacion = 0;
    mapLista(&listaJugadores, &datosPartida, jugarPartida);///juego

    /// Obtener y mostrar ganadores
    filtrarLista(&listaJugadores, &datosPartida.maximaPuntuacion, jugadoresNoGanadores, NULL);

    system("cls");
    colorFondo(VIOLETA_4, COLOR_AMARILLO);

    if(!siListaVacia(&listaJugadores))
    {
        printf("\nGanadores\n");
        printf("\n%-21s%s\n", "Nombre", "Puntuacion");
        mapLista(&listaJugadores, NULL, mostrarJugador);

        puts("\t\t _____________");
        puts("\t\t '._==_==_=_.'");
        puts("\t\t .-\\:      /-.");
        puts("\t\t| (|:.     |) |");
        puts("\t\t '-|:.     |-'");
        puts("\t\t   \\::.    /");
        puts("\t\t    '::. .'");
        puts("\t\t      ) (");
        puts("\t\t    _.' '._");
        puts("\t\t   \"\"\"\"\"\"\"\"\"");

        /// Agregar ganadores al informe
        exportarGanadoresHaciaInforme(datosPartida.archInforme, &listaJugadores);
    }
    else
        printf("\nNo hubo ganadores\n");

    sleep(3);

    /// Cerrar archivo informe y Liberar recursos de archivo mp3
    fclose(datosPartida.archInforme);
    cerrarMusica();

    return 0;
}
