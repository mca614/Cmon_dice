#include "funciones.h"

void mostrarLetraRespuesta( void *dato,  void *cond)
{
    printf("%c ", *(char*)dato);
}

int esSecuenciaCorrecta(t_lista *s,t_lista *r, Cmp cmp)
{
    while(*s && *r && cmp((*s)->info,(*r)->info)==0)
    {
        s=&(*s)->sig;
        r=&(*r)->sig;
    }

    if(!*s && !*r)
        return 1;

    return 0;
}

int cmp_letras( void *a, void *b)
{
    return tolower(*(char*)a) - tolower(*(char*)b);
}

void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda, Accion accion)
{
    int tiempo;
    float aux = 0;

    printf("\e[?25l"); // Ocultar mouse
    fflush(stdout);

    system("cls");

    printf("Secuencia: ");

    sleep(1);

    aux = tiempo_mostrar/(ronda);
    aux = aux > 1.5 ? 1.5 : aux;
    aux = aux < 0.1 ? 0.1 : aux;

    tiempo = (int)(aux * 1000);
    mapLista(secuencia, &tiempo, accion); /// agregar cadena que guarda la secuencia mostrada
}

void mostrarRespuesta(t_lista *respuesta, Accion accion)
{
    if(*respuesta)
    {
        printf("Respuesta: ");
        mapLista(respuesta, NULL, accion);
    }
}

/// Quito parámetro tecla de la funcion
void ingresarSecuencia(t_lista *respuesta, char **respuestaRonda, int tiempo_limite, int cant_max_ingreso, int *cant_letras_resp, int *es_tecla_esp)
{
    char letra;
    //datos del cronometro
    pthread_t cronometro;
    t_cronometroDatos datos;
    **respuestaRonda = '\0';

    datos.limiteTiempo = tiempo_limite + cant_max_ingreso; /// Se agrega 1 segundo por letra
    datos.tiempoAcabado = 0; //inicializar cronometro
    crearHiloCronometro(&cronometro, &datos); // iniciar hilo, es una tarea paralela

    printf("\e[?25h"); // mostrar mouse
    fflush(stdout);

    while (!datos.tiempoAcabado) // termina si se acabo el tiempo o ingreso
    {
        if (datos.tiempoAcabado) { // se acabo el tiempo
            break;
        }

        letra = getch();
        *es_tecla_esp = ES_TECLA_ESP(letra) && *cant_letras_resp ? 1 : 0;
        if(ES_COLOR(letra))
        {
            printf("%c ", letra);
        }
        while(!ES_COLOR(letra) && !datos.tiempoAcabado && !*es_tecla_esp)
        {
            printf("\nCaracter no valido. Ingrese un color: ");
            letra = getch();
            *es_tecla_esp = ES_TECLA_ESP(letra) && *cant_letras_resp ? 1 : 0;
            if(ES_COLOR(letra))
                printf("%c ", letra);
        }
        if(*es_tecla_esp)
            datos.tiempoAcabado =1;

        if(!datos.tiempoAcabado)
        {
            agregarAlFinal(respuesta, &letra, sizeof(char));
            **respuestaRonda = A_MAYUS(letra);
            (*respuestaRonda)++;
            **respuestaRonda = '\0';

            (*cant_letras_resp)++;
            cant_max_ingreso--;
        }

        if(cant_max_ingreso == 0)
            datos.tiempoAcabado =1; // para el cronometro

    }

    esperarHiloCronometro (&cronometro);

    printf("\e[?25l"); // Ocultar mouse
    fflush(stdout);
    printf("\n");
}

void leer_cant_retroceso_valido(int *cant_retroceso, int vidas, int cant_letras_resp)
{
    printf("\e[?25h"); // mostrar mouse
    fflush(stdout);

    int res = scanf("%d", cant_retroceso);
    while(res == 0 || (res && (*cant_retroceso > vidas
                             || *cant_retroceso > cant_letras_resp+1
                             || *cant_retroceso <= 0)))
    {
        printf("Entrada no valida. Ingrese nuevamente: ");
        fflush(stdin);
        res = scanf("%d", cant_retroceso);
    }

    printf("\e[?25l"); // Ocultar mouse
    fflush(stdout);
}

void jugarTurno(tJugador* jugador, tCola *colaRondas, int tiempo_mostrar, int tiempo_limite, Accion mostrar_sec, Accion mostrar_resp, Cmp cmp)
{
    t_lista secuencia, respuesta;
    crearLista(&secuencia);
    crearLista(&respuesta);
    int turnoTerminado=0, es_tecla_esp = 0;
    int ronda = 1, utilizo_vidas = 0, cant_retroceso, cant_letras_resp = 0;
    unsigned vidasIniciales = jugador->vidas;
    tRonda rondasJugador;

    char *ptrSecuencia = rondasJugador.secuencia;
    char *ptrRespuesta = rondasJugador.respuesta;
    char *inicioRespuesta = ptrRespuesta;

    printf("\e[?25l"); // Ocultar mouse
    fflush(stdout);

    printf("%s, es tu turno! Vidas: %d\n", jugador->nombre, jugador->vidas);

    sleep(1);
    system("cls");

    while(jugador->vidas>=0 && !turnoTerminado)
    {
        utilizo_vidas = 0;
        cant_letras_resp = 0;

        if(!(obtenerSecuencia(&secuencia, &ptrSecuencia)))
            return;

        printf("\n------------------ Ronda: %d ------------------\n", ronda);

        printf("Vidas: %d\n", jugador->vidas);

        sleep(1);

        mostrarSecuencia(&secuencia, tiempo_mostrar, ronda, mostrar_sec);

        system("pause");
        printf("\nIngresa la secuencia: ");

        ptrRespuesta = inicioRespuesta;
        ingresarSecuencia(&respuesta, &ptrRespuesta, tiempo_limite, ronda, &cant_letras_resp, &es_tecla_esp);

        /// ASIGNAR PUNTAJE Y ACTUALIZAR VIDAS

        while(jugador->vidas>0 && !esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
        {
            printf("\nVidas: %d\n", jugador->vidas);
            if(cant_letras_resp == 0) /// NO INGRESÓ NADA
            {
                system("cls");

                jugador->vidas--;
                printf("No ingreso ninguna secuencia.\nSe le restara una vida.\nVidas:%d\nSe mostrara nuevamente la secuencia\n",jugador->vidas);

                //sleep(6);
                sleep(2);

                mostrarSecuencia(&secuencia, tiempo_mostrar, ronda, mostrar_sec);

                system("pause");
                printf("\nIngresa la secuencia: ");

                ptrRespuesta = inicioRespuesta;
                ingresarSecuencia(&respuesta, &ptrRespuesta, tiempo_limite, ronda, &cant_letras_resp, &es_tecla_esp);
                utilizo_vidas = 1;
            }
            else /// LA SECUENCIA ERA INCORRECTA
            {
                if(es_tecla_esp)
                    printf("Presiono la tecla especial!\n"); ///aaaa
                else
                    printf("Secuencia incorrecta\n");
                mostrarRespuesta(&respuesta, mostrar_resp);
                printf("\nSe le restaran las vidas en base a la cantidad de jugadas que desee retroceder"
                       "\nIngrese un entero de 1 a %d para retroceder",MINIMO(cant_letras_resp,jugador->vidas));
                if(jugador->vidas > cant_letras_resp)
                    printf("\nO puede ingresar %d para volver a ver la secuencia "
                           "e ingresar una respuesta nueva (-%d vidas)", cant_letras_resp+1, cant_letras_resp+1);
                printf("\n---->: ");
                leer_cant_retroceso_valido(&cant_retroceso, jugador->vidas, cant_letras_resp);

                if(cant_retroceso>cant_letras_resp)///le tiene que mostrar la sec otra vez e ingresar de nuevo
                {
                    vaciarLista(&respuesta);
                    cant_letras_resp = 0;
                    printf("Le mostraremos nuevamente la secuencia:\n");
                    mostrarSecuencia(&secuencia, tiempo_mostrar, ronda, mostrar_sec);

                    system("pause");
                    printf("\nIngresa la secuencia: ");

                    ptrRespuesta = inicioRespuesta;
                    ingresarSecuencia(&respuesta, &ptrRespuesta, tiempo_limite, ronda, &cant_letras_resp, &es_tecla_esp);
                }
                else
                {
                    eliminarNnodosLista(&respuesta, cant_retroceso, cant_letras_resp);
                    cant_letras_resp -= cant_retroceso;

                    system("cls");
                    system("pause");
                    printf("Ingrese la secuencia faltante:\n");

                    mostrarRespuesta(&respuesta, mostrar_resp);

                    //ptrRespuesta = inicioRespuesta;
                    ingresarSecuencia(&respuesta, &ptrRespuesta, tiempo_limite, ronda-cant_letras_resp, &cant_letras_resp, &es_tecla_esp);
                }

                jugador->vidas-=cant_retroceso;
                utilizo_vidas = 1;
            }

            system("cls");
        }

        /// SI LA RESPUESTA ES CORRECTA
        if (esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
        {
            if(utilizo_vidas)
            {
                printf("Secuencia correcta! +1 puntos por usar vidas\n");
                jugador->puntuacion += 1;

                rondasJugador.puntosObtenidos = 1;
                vaciarLista(&respuesta);
            }
            else
            {
                printf("Secuencia correcta! +3 puntos por no usar vidas\n");
                jugador->puntuacion += 3;

                rondasJugador.puntosObtenidos = 3;
                vaciarLista(&respuesta);
            }

            sleep(2);
            system("cls");
        }
        else
        {

            if(jugador->vidas==0 && !esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
                turnoTerminado=1;

            rondasJugador.puntosObtenidos = 0;
        }

        //rondasJugador.puntosObtenidos = jugador->puntuacion;
        rondasJugador.vidasUsadas = vidasIniciales - jugador->vidas;
        rondasJugador.id = jugador->id;
        ponerEnCola(colaRondas, sizeof(tRonda), &rondasJugador);
        ronda++;
    }

    if(turnoTerminado==1)
        printf("\nSECUENCIA INCORRECTA Y SE QUEDO SIN VIDAS.\nPUNTUACION FINAL: %d\n", jugador->puntuacion);

    fflush(stdin);
}






