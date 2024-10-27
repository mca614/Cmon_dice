#include "cmon.h"

char menuConError(const char *msj, const char *opc)
{
    char opcElegida = '\0';

    do
    {
        if(!opcElegida)
            printf("%s", msj);
        else
           printf("\nError!!!\nIngrese una opcion valida\n%s", msj);

        scanf("%c", &opcElegida);
        fflush(stdin);
    }
    while(strchr(opc, opcElegida)==NULL);
    return opcElegida;
}

int menuComenzarJuego(){
    char opcion = '\0';

    printf("\nEs el turno del siguiente jugador...\n");

    printf("\e[?25h"); // mostrar mouse
    fflush(stdout);

    opcion = menuConError("\nDesea comenzar el juego?\n"
                      "1. Si\n"
                      "2. No\n"
                      "Seleccione una opcion: ", "12");

    return opcion == '1' ? 1 : 0;
}

void jugarPartida(void *jugador, void *extra){
    tDatosPartida *datos = (tDatosPartida*)extra;

    if(menuComenzarJuego(*((tJugador*)jugador))){
        system("cls");
        jugarTurno(((tJugador*)jugador), datos, mostrarLetraSecuencia, mostrarLetraRespuesta, cmp_letras);

        if(((tJugador*)jugador)->puntuacion > datos->maximaPuntuacion)
            datos->maximaPuntuacion = ((tJugador*)jugador)->puntuacion;
    }else{
        fprintf(datos->archInforme,"Jugador %d\n", ((tJugador*)jugador)->id);
        fprintf(datos->archInforme, "%s|%s|%d|%d\n", "-", "-", 0, 0); // Para los jugadores que eligieron no jugar
        fprintf(datos->archInforme,"Puntos obtenidos: %d\n\n", 0);
    }
}

FILE* generarArchivoDeInforme(const char* nombrePrefijo)
{
    time_t tiempo;
    struct tm* tiempoActual;
    char nombreArchivo[MAX_TAM_PATH];
    FILE* pf;

    time(&tiempo);
    tiempoActual = localtime(&tiempo);
    sprintf(nombreArchivo,"%s_%d-%02d-%02d-%02d-%02d.txt",nombrePrefijo,tiempoActual->tm_year+1900,tiempoActual->tm_mon+1,tiempoActual->tm_mday,tiempoActual->tm_hour,tiempoActual->tm_min);
    pf = fopen(nombreArchivo,"wt");

    //fclose(pf);
    return pf;
}
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno)
{
    tRonda registro;
    if(!colaVacia(colaTurno))
    {
        sacarDeCola(colaTurno, sizeof(tRonda), &registro);
        fprintf(archInforme,"Jugador %d\n", registro.id); //Encabezado de cada jugador
    }
    while(!colaVacia(colaTurno))
    {
        fprintf(archInforme, "%s|%s|%d|%d\n", registro.secuencia, registro.respuesta, registro.vidasUsadas, registro.puntosRonda);
        sacarDeCola(colaTurno, sizeof(tRonda), &registro);
    }

    fprintf(archInforme, "%s|%s|%d|%d\n", registro.secuencia, registro.respuesta, registro.vidasUsadas, registro.puntosRonda);
    fprintf(archInforme,"Puntos obtenidos: %d\n\n", registro.puntosTotales);
}

void exportarGanadoresHaciaInforme(FILE* archInforme, t_lista* ganadores)
{
    tJugador jugador;
    fprintf(archInforme,"================ GANADORES ===============\n"); // Si se incluye haría difícil leer el archivo posteriormente
    fprintf(archInforme,"-------NOMBRE JUGADOR | PUNTUACION--------\n");
    while(!siListaVacia(ganadores))
    {
        sacarPrimero(ganadores, &jugador, sizeof(tJugador)); //--> falta implementar
        fprintf(archInforme, "%s|%d\n", jugador.nombre, jugador.puntuacion);
    }
}
