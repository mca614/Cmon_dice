#include "menu.h"

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

int obtenerValorAleatorio(int menorValor, int mayorValor) {
    return (rand() % (mayorValor - menorValor + 1)) + menorValor;
}

void ingresarJugador(tJugador *jugador, unsigned *cantidadJugadores){
    char *pNombre = jugador->nombre;

    fgets(pNombre, MAX_L_JUGADOR, stdin);
    pNombre = strrchr(pNombre, '\n');
    *pNombre = '\0';

    jugador->id = obtenerValorAleatorio(*cantidadJugadores * -1, *cantidadJugadores);
    system("cls");
}

void menuIngresoJugadores(t_lista *listaJugadores, unsigned *cantidadJugadores){
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
                ingresarJugador(&jugador, cantidadJugadores);
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
        /// Se busca en el archivo config l�nea a l�nea (F | 20 | 20 | 5) el primer caracter
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
