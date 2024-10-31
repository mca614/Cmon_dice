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

int generarArchivoConf(){
    tDatosDificultad datos[3];

    FILE *arch;
    char opcion, dificultad[][MAX_L_DIF] = {"Facil", "Media", "Dificil"};
    int i = 0;

    opcion = menuConError("\n1. Generar archivo configuracion"
                          "\n2. Salir"
                          "\nIngrese una opcion: ", "12");

    if(opcion == '1'){
        arch = fopen("config.txt", "wt");

        if(!arch){
            printf("\nError al abrir el archivo");
            return 0;
        }

        for(i=0; i<3; i++){
            strcpy(datos[i].dificultad, dificultad[i]);

            do{
                system("cls");
                printf("\nDificultad: %s", datos[i].dificultad);
                printf("\nIngrese un tiempo de secuencia entre %d y %d: ", VALOR_MIN, VALOR_MAX);
                scanf("%d", &datos[i].tiempoSecuencia);
                fflush(stdin);

                if(datos[i].tiempoSecuencia < VALOR_MIN || datos[i].tiempoSecuencia > VALOR_MAX){
                    printf("\nValor erroneo. Ingrese un valor entre %d y %d", VALOR_MIN, VALOR_MAX);
                    sleep(1);
                }
            }while(datos[i].tiempoSecuencia < VALOR_MIN || datos[i].tiempoSecuencia > VALOR_MAX);

            do{
                system("cls");
                printf("\nDificultad: %s", datos[i].dificultad);
                printf("\nIngrese un tiempo de respuesta entre %d y %d: ", VALOR_MIN, VALOR_MAX);
                scanf("%d", &datos[i].tiempoRespuesta);
                fflush(stdin);

                if(datos[i].tiempoRespuesta < VALOR_MIN || datos[i].tiempoRespuesta > VALOR_MAX){
                    printf("\nValor erroneo. Ingrese un valor entre %d y %d", VALOR_MIN, VALOR_MAX);
                    sleep(1);
                }
            }while(datos[i].tiempoRespuesta < VALOR_MIN || datos[i].tiempoRespuesta > VALOR_MAX);

            do{
                system("cls");
                printf("\nDificultad: %s", datos[i].dificultad);
                printf("\nIngrese una cantidad de vidas entre %d y %d: ", 0, VIDAS_MAX);
                scanf("%d", &datos[i].cantVidas);
                fflush(stdin);

                if(datos[i].cantVidas < 0 || datos[i].cantVidas > VIDAS_MAX){
                    printf("\nValor erroneo. Ingrese un valor entre %d y %d", 0, VIDAS_MAX);
                    sleep(1);
                }
            }while(datos[i].cantVidas < 0 || datos[i].cantVidas > VIDAS_MAX);

            system("cls");

            fprintf(arch, "%c | %d | %d | %d\n", *(datos[i].dificultad), datos[i].tiempoSecuencia, datos[i].tiempoRespuesta, datos[i].cantVidas);
        }

        for(i=0; i<3; i++){
            printf("Dificultad: %s\nTiempo secuencia: %d\nTiempo respuesta: %d\nCantidad de vidas: %d\n",
                   datos[i].dificultad ,datos[i].tiempoSecuencia, datos[i].tiempoRespuesta, datos[i].cantVidas);
            puts("");
        }

        printf("Se genero el archivo config.txt...");
    }

    fflush(stdin);
    sleep(3);
    fclose(arch);
    return 1;
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
