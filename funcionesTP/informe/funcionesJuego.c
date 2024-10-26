#include "funcionesJuego.h"

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

    fclose(pf);
    return pf;
}

void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno)
{
    tRonda registro;
    if(!colaVacia(colaTurno))
    {
        sacarDeCola(colaTurno,sizeof(tRonda), &registro);
        fprintf(archInforme,"Jugador %d\n",registro.id); //Encabezado de cada jugador
    }
    while(!colaVacia(colaTurno))
    {
        fprintf(archInforme,"%s|%s|%d|%d\n",registro.secuencia, registro.respuesta, registro.vidasUsadas, registro.puntosObtenidos);
        sacarDeCola(colaTurno,sizeof(tRonda), &registro);
    }
    fprintf(archInforme,"Puntos obtenidos: %d", registro.puntosObtenidos);
}

void exportarGanadoresHaciaInforme(FILE* archInforme, t_lista* ganadores)
{
    tJugador* jugador;
    //fprintf("================ GANADORES ==============="); ---> Si se incluye haría difícil leer el archivo posteriormente
    //fprintf("ID JUGADOR | NOMBRE JUGADOR | PUNTUACION");
    while(siListaVacia(ganadores))
    {
        //eliminarPrimeroDeLista(ganadores,&jugador,sizeof(tJugador)); --> falta implementar
        fprintf(archInforme,"%d|%s|%d",jugador->id,jugador->nombre,jugador->puntuacion);
    }

}

int cmpCaracter(const void* a, const void* b)
{
    return *(char*)a-*(char*)b;
}
void mostrarCaracter(const void* a,const void* b)
{
    printf("%c",*(char*)a);
}
