#include "comienzoJuego.h"

char menuConError(const char *msj, const char *opc)
{
    char opcElegida = '\0';

    do
    {
        printf( !opcElegida ? "%s" : "\nError!!! \nIngrese una opcion valida\n%s" , msj);
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

int mostrarConfDificultad(char *dificultadElegida){
    FILE *archivoConfDificultad;
    char linea[MAX_LINEA], *ptr, *resultadoBusquedaDificultad;
    unsigned tiempoSecuencia, tiempoJugada, cantVidas;

    archivoConfDificultad = fopen("config.txt", "rt");

    if(!archivoConfDificultad){
        printf("\nError al leer el archivo\n"
               "No se pudo obtener configuraciones de dificultad...\n"
        );
        return 0;
    }

    resultadoBusquedaDificultad = NULL;

    while(!resultadoBusquedaDificultad && fgets(linea, MAX_LINEA, archivoConfDificultad)){
        resultadoBusquedaDificultad = strchr(linea, *dificultadElegida);

        if(resultadoBusquedaDificultad){
            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &cantVidas);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &tiempoJugada);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &tiempoSecuencia);

            printf(
               "\nNivel dificultad: %s"
               "\nTiempo en que se muestra secuencia: %u"
               "\nTiempo que tiene el jugador para contestar: %u"
               "\nCantidad de vidas del jugador: %u\n", dificultadElegida, tiempoSecuencia, tiempoJugada, cantVidas
            );
        }
    }

    if(!resultadoBusquedaDificultad)
        printf("\nNo se pudo obtener configuraciones de dificultad...\n");

    fclose(archivoConfDificultad);
    return resultadoBusquedaDificultad ? 1 : 0;
}

int menuDificultad(char *dificultadElegida){
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
                strcpy(dificultadElegida, "Facil");
                break;
            case '2':
                strcpy(dificultadElegida, "Media");
                break;
            case '3':
                strcpy(dificultadElegida, "Dificil");
                break;
            case '4':
                strcpy(dificultadElegida, "\0");
                break;
    }

    return opcion == '4' ? 0 : 1;
}

int menuComenzarJuego(t_lista *listaJugadores, tJugador proximoJugador){
    char opcion = '\0';

    printf("\nEs el turno del jugador: %s\n", proximoJugador.nombre);

    opcion = menuConError("\nDesea comenzar el juego?\n"
                      "1. Si\n"
                      "2. No\n"
                      "Seleccione una opcion: ", "12");

    return opcion == '1' ? 1 : 0;
}
