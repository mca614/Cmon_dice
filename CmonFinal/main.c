#include "cmon.h"

int main()
{
    t_lista listaJugadores;
    tDatosPartida datosPartida;
    int cantidadJugadores = 0;

    crearLista(&listaJugadores);

    menuIngresoJugadores(&listaJugadores, &cantidadJugadores);

    menuDificultad(&datosPartida);

    /// Generar archivo informe
    datosPartida.archInforme = generarArchivoDeInforme("informe.txt");

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
