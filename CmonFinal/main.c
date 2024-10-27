#include "cmon.h"

int main()
{
    tJugador jugadorAux;
    t_lista listaJugadores;
    tDatosPartida datosPartida;
    unsigned cantidadJugadores = 0;

    crearLista(&listaJugadores);

    /// Menú ingreso de jugadores
    menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

    /// Menú dificultad
    menuDificultad(&datosPartida);

    /// Cargar datos de jugadores y mostrar posiciones
    printf("\nPosiciones de los jugadores...\n");
    jugadorAux.id = 1;
    jugadorAux.puntuacion = 0;
    jugadorAux.vidas = datosPartida.cantVidas;
    mapLista(&listaJugadores, &jugadorAux, cargarMostrarDatosJugador);

    /// Muestra las configuraciones del juego
    printf(
       "\nInstrucciones para jugar...\n"
       "\nConfiguraciones de dificultad...\n"
       "\nTiempo en que se muestra secuencia: %u"
       "\nTiempo que tiene el jugador para contestar: %u"
       "\nCantidad de vidas del jugador: %u\n",
       datosPartida.tiempoSecuencia, datosPartida.tiempoRespuesta, datosPartida.cantVidas
    );

    /// Generar archivo informe
    datosPartida.archInforme = generarArchivoDeInforme("informe.txt");

    /// Reproducir Musica (VERIFICAR QUE -lwinmm ESTÉ AGREGADO COMO PARÁMETRO EN BUILD OPTIONS > LINKER SETTINGS > OTHER LINK OPTIONS
    //reproducirMusica(MUSICA1);

    /// Jugar partidas
    mapLista(&listaJugadores, &datosPartida, jugarPartida);

    /// Obtener y mostrar ganadores
    filtrarLista(&listaJugadores, &datosPartida.maximaPuntuacion, jugadoresNoGanadores, NULL);

    system("cls");

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
