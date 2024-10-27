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

int cmpJugadores(void *a, void *b){
    tJugador *j1, *j2;
    j1 = (tJugador*)a;
    j2 = (tJugador*)b;

    return j1->id - j2->id;
}

int obtenerValorAleatorio(int menorValor, int mayorValor) {
    return (rand() % (mayorValor - menorValor + 1)) + menorValor;
}

void ingresarJugador(tJugador *jugador, int cantidadJugadores){
    char *pNombre = jugador->nombre;

    fgets(pNombre, MAX_L_JUGADOR, stdin);
    pNombre = strrchr(pNombre, '\n');
    *pNombre = '\0';

    /// Valor aleatorio generado para id según la cantidad de jugadores. Ej desde -1 hasta 1
    jugador->id = obtenerValorAleatorio(cantidadJugadores * -1, cantidadJugadores);
    system("cls");
}

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

void menuIngresoJugadores(t_lista *listaJugadores, int *cantidadJugadores){
    char opcion;
    tJugador jugador;
    srand(time(NULL));

    do{
        opcion = menuConError("\n==============================================\n"
                              "\tMENU INGRESO DE JUGADORES\n"
                              "==============================================\n"
                              "\n1. Para agregar un jugador"
                              "\n2. Para dejar de ingresar..."
                              "\nElija una opcion: "
                              , "12");

        if(opcion == '1'){

            system("cls");

            do{
                printf("\nIngrese nombre del jugador: ");
                ingresarJugador(&jugador, *cantidadJugadores);
            }while(strcmpi(jugador.nombre, "") == 0);

            agregarOrdenado(listaJugadores, &jugador, 1, sizeof(tJugador), cmpJugadores);
            (*cantidadJugadores)++;
        }

    }while(opcion != '2');
}

int cargarDificultad(tDatosPartida *datosPartida){
    FILE *archivoConfDificultad;
    char linea[MAX_LINEA], *ptr;
    int resultadoBusquedaDificultad = 0;

    archivoConfDificultad = fopen("config.txt", "rt");

    if(!archivoConfDificultad){
        printf("\nError al leer el archivo\n"
               "No se pudo obtener configuraciones de dificultad...\n"
        );
        return 0;
    }

    while(!resultadoBusquedaDificultad && fgets(linea, MAX_LINEA, archivoConfDificultad)){
        /// Se busca en el archivo config línea a línea (F | 20 | 20 | 5) el primer caracter
        resultadoBusquedaDificultad = *linea == datosPartida->dificultad ? 1 : 0;

        if(resultadoBusquedaDificultad){
            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &datosPartida->cantVidas);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &datosPartida->tiempoRespuesta);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &datosPartida->tiempoSecuencia);
        }
    }

    if(!resultadoBusquedaDificultad)
        printf("\nNo se pudo obtener configuraciones de dificultad...\n");

    fclose(archivoConfDificultad);
    return resultadoBusquedaDificultad;
}

int menuDificultad(tDatosPartida *datosPartida){
    char opcion;

    opcion = menuConError("\n==============================================\n"
                      "\tELIJA DIFICULTAD\n"
                      "==============================================\n"
                      "1. FACIL\n"
                      "2. MEDIA\n"
                      "3. DIFICIL\n"
                      "4. Salir\n"
                      "Seleccione una opcion: ", "1234");

    switch(opcion) {
            case '1':
                datosPartida->dificultad = 'F';
                break;
            case '2':
                datosPartida->dificultad = 'M';
                break;
            case '3':
                datosPartida->dificultad = 'D';
                break;
    }

    if(opcion != '4'){
        cargarDificultad(datosPartida);
        return 1;
    }

    return 0;
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
