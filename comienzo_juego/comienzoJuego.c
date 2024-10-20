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


int menuDificultad(tDificultad *dificultadElegida){
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
                strcpy(dificultadElegida->dificultad, "Facil");
                break;
            case '2':
                strcpy(dificultadElegida->dificultad, "Media");
                break;
            case '3':
                strcpy(dificultadElegida->dificultad, "Dificil");
                break;
            case '4':
                strcpy(dificultadElegida->dificultad, "\0");
                break;
    }

    return opcion == '4' ? 0 : 1;
}

int menuComenzarJuego(tJugador proximoJugador){
    char opcion = '\0';

    printf("\nEs el turno del jugador: %s\n", proximoJugador.nombre);

    opcion = menuConError("\nDesea comenzar el juego?\n"
                      "1. Si\n"
                      "2. No\n"
                      "Seleccione una opcion: ", "12");

    return opcion == '1' ? 1 : 0;
}

void cargarDatosJugador(void *v, void *extra){
    tJugador *jugador = (tJugador*)v;
    tJugador *jugadorAux = (tJugador*)extra;

    jugador->id = jugadorAux->id;
    jugadorAux->id++;
    jugador->puntuacion = 0;
    jugador->vidas = jugadorAux->vidas;
}

void cargarDatosJugadores(t_lista *listaJugadores, int cantVidas){
    /// Se usa una variable tJugador auxiliar para realizar el proceso de carga
    /// de los datos al jugador. Esto se hace con función map que recibe como parámetro a la
    /// la función cargarDatosJugador()
    tJugador jugadorAux;
    jugadorAux.id = 1;
    jugadorAux.vidas = cantVidas;

    mapLista(listaJugadores, &jugadorAux, cargarDatosJugador);
}

/// En base al campo "dificultad" de la variable dificultadElegida, se busca
/// en el archivo config.txt la línea que contiene los datos de dificultad
/// (tSecuencia, tJugador, vidas)
int cargarDificultad(tDificultad *dificultadElegida){
    FILE *archivoConfDificultad;
    char linea[MAX_LINEA], *ptr, *resultadoBusquedaDificultad;

    archivoConfDificultad = fopen("config.txt", "rt");

    if(!archivoConfDificultad){
        printf("\nError al leer el archivo\n"
               "No se pudo obtener configuraciones de dificultad...\n"
        );
        return 0;
    }

    resultadoBusquedaDificultad = NULL;

    while(!resultadoBusquedaDificultad && fgets(linea, MAX_LINEA, archivoConfDificultad)){
        /// Se busca en el archivo config línea a línea (F | 20 | 20 | 5) el primer caracter
        /// de la variable dificultadElegida de su campo dificultad (Facil, Media, Dificil)
        resultadoBusquedaDificultad = strchr(linea, *(dificultadElegida->dificultad));

        if(resultadoBusquedaDificultad){
            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &dificultadElegida->cantVidas);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &dificultadElegida->tiempoJugada);
            *ptr = '\0';

            ptr = strrchr(linea, '|');
            sscanf(ptr+1, "%u", &dificultadElegida->tiempoSecuencia);
        }
    }

    if(!resultadoBusquedaDificultad)
        printf("\nNo se pudo obtener configuraciones de dificultad...\n");

    fclose(archivoConfDificultad);
    return resultadoBusquedaDificultad ? 1 : 0;
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
