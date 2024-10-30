#include "cmon.h"

void mostrarJugador(void *a, void *extra){
    printf("%-25s%d\n",((tJugador*)a)->nombre, ((tJugador*)a)->puntuacion);
}

int jugadoresNoGanadores(void *dato, void *info){
    unsigned *maximaPuntuacion = (unsigned*)dato;
    tJugador *jugador = (tJugador*)info;
    return  (jugador->puntuacion != *maximaPuntuacion || jugador->puntuacion == 0) ? 1 : 0;
}

int cmpJugadores(void *a, void *b){
    tJugador *j1, *j2;
    j1 = (tJugador*)a;
    j2 = (tJugador*)b;

    return j1->id - j2->id;
}

void cargarMostrarDatosJugador(void *v, void *extra){
    tJugador *jugador = (tJugador*)v;
    tJugador *jugadorAux = (tJugador*)extra;

    jugador->id = jugadorAux->id;
    jugadorAux->id++;
    jugador->puntuacion = jugadorAux->puntuacion;
    jugador->vidas = jugadorAux->vidas;

    printf("%3s%-12d%s\n", "", jugador->id , jugador->nombre);
}

void jugarPartida(void *jugador, void *extra){
    tDatosPartida *datos = (tDatosPartida*)extra;

    if(menuComenzarJuego(*((tJugador*)jugador))){
        system("cls");
        system("pause");
        jugarTurno(((tJugador*)jugador), datos, mostrarLetraSecuencia, mostrarLetraRespuesta, cmp_letras);

        if(((tJugador*)jugador)->puntuacion > datos->maximaPuntuacion)
            datos->maximaPuntuacion = ((tJugador*)jugador)->puntuacion;
    }else{
        fprintf(datos->archInforme,"Jugador %d\n", ((tJugador*)jugador)->id);
        fprintf(datos->archInforme, "%s|%s|%d|%d\n", "-", "-", 0, 0); // Para los jugadores que eligieron no jugar
        fprintf(datos->archInforme,"Puntos obtenidos: %d\n\n", 0);
    }
}

FILE* generarArchivoDeInforme(const char* nombrePrefijo, char* nomArchGenerado)
{
    time_t tiempo;
    struct tm* tiempoActual;
    char nombreArchivo[MAX_TAM_PATH];
    FILE* pf;

    time(&tiempo);
    tiempoActual = localtime(&tiempo);
    sprintf(nombreArchivo,"%s_%d-%02d-%02d-%02d-%02d.txt",nombrePrefijo,tiempoActual->tm_year+1900,tiempoActual->tm_mon+1,tiempoActual->tm_mday,tiempoActual->tm_hour,tiempoActual->tm_min);
    pf = fopen(nombreArchivo,"wt");
    strcpy(nomArchGenerado,nombreArchivo);
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
