#include "cmon.h"

int main()
{
    tJugador jugadorAux;
    t_lista listaJugadores;
    tDatosPartida datosPartida;
    unsigned cantidadJugadores = 0;

    crearLista(&listaJugadores);
    centrarVentanaConsola();
    ajustarConsola(80,38,45,25);
    colorFondo(VIOLETA_4, COLOR_NARANJA_2);


    /// Men� ingreso de jugadores
    menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

    colorFondo(VIOLETA_4, VIOLETA_0);
    /// Men� dificultad
    menuDificultad(&datosPartida);

    colorFondo(VIOLETA_4, VERDE_MUYCLARO);
    /// Cargar datos de jugadores y mostrar posiciones
    printf("\nPosiciones de los jugadores...\n");
    jugadorAux.id = 1;
    jugadorAux.puntuacion = 0;
    jugadorAux.vidas = datosPartida.cantVidas;
    mapLista(&listaJugadores, &jugadorAux, cargarMostrarDatosJugador);

    system("pause");
    colorFondo(VIOLETA_4, COLOR_ROJO_5);

    /// Muestra las configuraciones del juego
    printf(
       "\nInstrucciones para jugar...\n"
       "\nConfiguraciones de dificultad...\n"
       "\nTiempo en que se muestra secuencia: %u"
       "\nTiempo que tiene el jugador para contestar: %u"
       "\nCantidad de vidas del jugador: %u\n",
       datosPartida.tiempoSecuencia, datosPartida.tiempoRespuesta, datosPartida.cantVidas
    );
    system("pause");

    /// Generar archivo informe
    datosPartida.archInforme = generarArchivoDeInforme("informe.txt");

    /// Reproducir Musica (VERIFICAR QUE -lwinmm EST� AGREGADO COMO PAR�METRO EN BUILD OPTIONS > LINKER SETTINGS > OTHER LINK OPTIONS
    reproducirMusica(MUSICA1);


    colorFondo(VIOLETA_4, VERDE_CLARO);
    /// Jugar partidas
    datosPartida.maximaPuntuacion = 0;
    mapLista(&listaJugadores, &datosPartida, jugarPartida);

    /// Obtener y mostrar ganadores
    filtrarLista(&listaJugadores, &datosPartida.maximaPuntuacion, jugadoresNoGanadores, NULL);

    system("cls");
    colorFondo(VIOLETA_4, COLOR_AMARILLO);

    if(!siListaVacia(&listaJugadores)){
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
    }else
        printf("\nNo hubo ganadores\n");

    /// Cerrar archivo informe
    fclose(datosPartida.archInforme);
    return 0;
}
