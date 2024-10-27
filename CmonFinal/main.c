#include "cmon.h"

void mostrarJugador(void *a, void *extra){
    //printf("%d, %s, %d\n",((tJugador*)a)->id, ((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
    printf("%-25s%d\n",((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
}

int jugadoresNoGanadores(void *dato, void *info){
    unsigned *maximaPuntuacion = (unsigned*)dato;
    tJugador *jugador = (tJugador*)info;
    return  (jugador->puntuacion != *maximaPuntuacion || jugador->puntuacion == 0) ? 1 : 0;
}

int main()
{
    t_lista listaJugadores;
    tDatosPartida datosPartida;


    /// Aca iría el ingreso de los jugadores
    tJugador jugadores[] = {{1, "abel", 3, 0}, {2, "tomas", 3, 0}, {3, "milagros", 3, 0}};
    //tJugador jugadores[] = {{1, "abel", 3, 0}};

    crearLista(&listaJugadores);

    for(int i=0; i<sizeof(jugadores)/sizeof(jugadores[0]); i++)
        agregarAlFinal(&listaJugadores, &jugadores[i], sizeof(tJugador));

    /// Aca iría la carga de datos de partida desde el archivo config
    datosPartida.dificultad = 'D';
    datosPartida.cantVidas = 3;
    datosPartida.tiempoSecuencia = 5;
    datosPartida.tiempoRespuesta = 5;

    /// Generar archivo informe
    datosPartida.archInforme = generarArchivoDeInforme("informe.txt");

    /// Reproducir Musica
    reproducirMusica(MUSICA1);

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
