#include "funcionesJuego.h"
size_t WriteCallback(void *datosRespuesta, size_t tamBloque, size_t bloques, void *info)
{
    size_t tamDatos = tamBloque * bloques;

    tRespuesta *respuesta = (tRespuesta *)info;

    // Reservo memoria para la cadena que uso para almacenar la respuesta
    char *datos = malloc(tamDatos + 1);

    if (datos == NULL)
        return 0;

    // Completo la estructura que guarda la respuesta
    respuesta->cadena = datos;
    memcpy(respuesta->cadena, datosRespuesta, tamDatos);
    respuesta->tam = tamDatos;
    *(respuesta->cadena + respuesta->tam) = '\0';

    return tamDatos;
}

int realizarSolicitud(char *url, char *respuesta)
{
    CURL *curl;
    CURLcode res;

    // Se inicializa variable estructura para almacenar la respuesta
    tRespuesta respSolicitud;
    respSolicitud.cadena = NULL;
    respSolicitud.tam = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Se realizan configuraciones para realizar la URL de la solicitud GET
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&respSolicitud);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);


        // Se ejecuta solicitud GET
        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
            strncpy(respuesta, respSolicitud.cadena, MAX_TAM_RESP - 1);
        else
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));

        free(respSolicitud.cadena);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    return curl &&  (res == CURLE_OK) ? 1 : 0;
}

void convertirCadenaNumeros(int *numeros, char *cadena)
{
    char *ptr = cadena;

    while(*ptr){
        while(*ptr == '\n')
            ptr++;

        sscanf(ptr, "%d", numeros);
        numeros++;

        while(*ptr && *ptr != '\n')
            ptr++;
    }
}

int obtenerNumerosAleatorios(int *numeros, int cantidad, int min, int max)
{
    char url[MAX_TAM_URL];
    char respuesta[MAX_TAM_RESP];
    sprintf(url, "https://www.random.org/integers/?num=%d&min=%d&max=%d&col=1&base=10&format=plain&rnd=new", cantidad, min, max);

    if(!realizarSolicitud(url, respuesta)){
        printf("\nNo se logro obtener los numeros\n");
        return 0;
    }

    //printf("\nRESPUESTA de www.random.org:\n%s\n", respuesta);
    convertirCadenaNumeros(numeros, respuesta);
    return 1;
}

void buscarJugadorMayorPuntuacion(tLista* jugadores,tJugador* jug,unsigned tam_info)
{
    tJugador* maxJug, *aux;
    if(*jugadores)
        maxJug= (*jugadores)->info;

    while(*jugadores)
    {
        aux= (*jugadores)->info;
        if(aux->puntuacion>maxJug->puntuacion)
            maxJug=aux;
        jugadores=&(*jugadores)->sig;
    }

    *jug= *maxJug;
}

int buscarPuntaje(const tLista *jugadores, int maxPuntaje,tJugador* aux)
{
    tJugador* eqPun;
    while(*jugadores)
    {
        eqPun= (*jugadores)->info;
        if(aux->puntuacion==eqPun->puntuacion && eqPun->id!=aux->id)
        {
            *aux= *eqPun;
            return MISMO_PUNTAJE;
        }
        jugadores=&(*jugadores)->sig;
    }
    return TODO_OK;
}

int cmpPuntaje(const void* a,const void* b)
{
    tJugador* jug1= (tJugador*)a;
    tJugador* jug2= (tJugador*)b;

    return jug1->puntuacion - jug2->puntuacion;
}

void mostrarGanadores(tLista* jugadores)
{
    tJugador* maxJug;
    int maxPuntaje;

    if(*jugadores)
    {
        ordenarListaPorSeleccion(jugadores,cmpPuntaje,DESC);
        maxJug= (*jugadores)->info;
        maxPuntaje= maxJug->puntuacion;

    }

    printf("-----GANADORES-----\n");
    while(*jugadores&& maxPuntaje == maxJug->puntuacion)
    {
        printf("%-20s \t PUNTOS: %d\n", maxJug->nombre,maxJug->puntuacion);
        jugadores = &(*jugadores)->sig;
        if(*jugadores)
            maxJug= (*jugadores)->info;
    }
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

    fclose(pf);
    return pf;
}
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno)
{
    tRonda* registro;
    if(!colaVacia(colaTurno))
    {
        sacarDeCola(colaTurno,sizeof(tRonda),&registro);
        fprintf(archInforme,"Jugador %d\n",registro->id); //Encabezado de cada jugador
    }
    while(!colaVacia(colaTurno))
    {
        fprintf(archInforme,"%s|%s|%d|%d\n",registro->secuencia,registro->respuesta,registro->vidasUsadas,registro->puntosObtenidos);
        sacarDeCola(colaTurno,sizeof(tRonda),registro);
    }
    fprintf(archInforme,"Puntos obtenidos: %d",registro->puntosObtenidos);
}

void exportarGanadoresHaciaInforme(FILE* archInforme, tLista* ganadores)
{
    tJugador* jugador;
    fprintf(archInforme,"================ GANADORES ==============="); // Si se incluye haría difícil leer el archivo posteriormente
    fprintf(archInforme,"-------NOMBRE JUGADOR | PUNTUACION--------");
    while(esListaVacia(ganadores))
    {
        eliminarPrimeroDeLista(ganadores,&jugador,sizeof(tJugador)); //--> falta implementar
        fprintf(archInforme,"%s|%d",jugador->nombre,jugador->puntuacion);
    }
}
//int generarInformeDeJuego(tCola* cola)
//{
//    time_t tiempo;
//    struct tm* tiempoActual;
//    char nombreArchivo[MAX_TAM_PATH];
//    tJugador registro;
//    unsigned idAnt;
//    FILE* pf;
//
//    time(&tiempo);
//    tiempoActual = localtime(&tiempo);
//    sprintf(nombreArchivo,"informe-juego_%d-%02d-%02d-%02d-%02d.txt",
//           tiempoActual->tm_year+1900,
//           tiempoActual->tm_mon+1,
//           tiempoActual->tm_mday,
//           tiempoActual->tm_hour,
//           tiempoActual->tm_min);
//
//    pf = fopen(nombreArchivo,"wt");
//
//    sacarDeCola(cola,sizeof(tJugador),&registro);
//    while(!colaVacia(cola))
//    {
//        idAnt = registro->id;
//        fprintf(pf,"Jugador %d\n",registro->id); //Encabezado de cada jugador
//        while(!colaVacia(cola) && registro->id == idAnt)
//        {
//            fprintf(pf,"%s|%s|%d|%d|%d\n",registro->secuencia,registro->respuesta,registro->vidas,registro->puntajeObtenido,registro->puntajeAcumulado);
//            sacarDeCola(cola,sizeof(tJugador),&registro);
//        }
//    }
//    //// FALTA GRABAR GANADOR////
//    fclose(pf);
//    return 1;
//}
int cmpCaracter(const void* a, const void* b)
{
    return *(char*)a-*(char*)b;
}
void mostrarCaracter(const void* a,const void* b)
{
    printf("%c",*(char*)a);
}
