#include "funciones.h"

void mostrarLetraRespuesta(const void *dato, const void *cond)
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

int cmp_letras(const void *a,const void *b)
{
    return tolower(*(char*)a) - tolower(*(char*)b);
}

void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, int ronda, Accion accion)
{
    int tiempo;

    system("cls");

    printf("Secuencia: ");

    sleep(2);

    tiempo = tiempo_mostrar/(ronda);

    tiempo = tiempo>2 ? 3 : tiempo;
    tiempo = tiempo<1 ? 1 : tiempo;

    mapLista(secuencia,&tiempo,accion);
}

void mostrarRespuesta(t_lista *respuesta, Accion accion)
{
    if(*respuesta)
    {
        printf("Respuesta: ");
        mapLista(respuesta, NULL, accion);
    }
}

void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int cant_max_ingreso, int *cant_letras_resp, int *tecla)
{
    char letra;
    //datos del cronometro
    pthread_t cronometro;
    t_cronometroDatos datos;

    datos.limiteTiempo = tiempo_limite; // Puedes cambiar esto para probar otros límites de tiempo
    datos.tiempoAcabado = 0; //inicializar cronometro

    crearHiloCronometro(&cronometro, &datos); // iniciar hilo, es una tarea paralela

     while (!datos.tiempoAcabado) // termina si se acabo el tiempo o ingreso
    {
        if (datos.tiempoAcabado) { // se acabo el tiempo
            break;
        }

        letra = getch(); // getch te trae el caracter de la pantalla
        if(ES_COLOR(letra)) // si es un enter o escape no quiero que le muestre (valor ascii de enter es 13 y esc 27)
            printf("%c ", letra);// para imprimir el caracter que leyó

        while(!ES_COLOR(letra) && !datos.tiempoAcabado)
        {
            printf("\nCaracter no valido. Ingrese un color: ");
            letra = getch();
            if(ES_COLOR(letra))
                printf("%c ", letra);
        }
        if(!datos.tiempoAcabado)
        {
            agregarAlFinal(respuesta, &letra, sizeof(char));
            (*cant_letras_resp)++;
            cant_max_ingreso--;
        }

//        if(letra == /* tecla que elegimos*/)
//        {
//            datos.tiempoAcabado =1;
//            *tecla = 1;
//        }

        if(cant_max_ingreso == 0)
            datos.tiempoAcabado =1; // para el cronometro

    }
    esperarHiloCronometro (&cronometro);

    printf("\n");
}

void leer_cant_retroceso_valido(int *cant_retroceso, int vidas, int cant_letras_resp)
{
    int res = scanf("%d", cant_retroceso);
    while(res == 0 || (res && (*cant_retroceso > vidas
                             || *cant_retroceso > cant_letras_resp+1
                             || *cant_retroceso <= 0)))
    {
        printf("Entrada no valida. Ingrese nuevamente: ");
        fflush(stdin);
        res = scanf("%d", cant_retroceso);
    }
}

void jugarTurno(tJugador* jugador, int tiempo_mostrar, int tiempo_limite, Accion mostrar_sec,
                Accion mostrar_resp, Cmp cmp)
{
    t_lista secuencia, respuesta;
    crearLista(&secuencia);
    crearLista(&respuesta);
    int turnoTerminado=0;

    int tecla=0; // para saber si se apreto esa tecla

    int ronda = 1, utilizo_vidas = 0, cant_retroceso, cant_letras_resp = 0;

    printf("%s, es tu turno! Vidas: %d\n", jugador->nombre, jugador->vidas);

    sleep (2);
    system("cls");

    while(jugador->vidas>=0 && !turnoTerminado)
    {
        utilizo_vidas = 0;
        cant_letras_resp = 0;

        if(!(obtenerSecuencia(&secuencia)))
            return ;

        printf("\n------------------ Ronda: %d ------------------\n", ronda);

        printf("Vidas: %d\n", jugador->vidas);

        sleep(5);

        mostrarSecuencia(&secuencia, tiempo_mostrar, ronda, mostrar_sec);

        printf("\nIngresa la secuencia: ");
        ingresarSecuencia(&respuesta, tiempo_limite, ronda, &cant_letras_resp, &tecla);

        /// ASIGNAR PUNTAJE Y ACTUALIZAR VIDAS

        while(jugador->vidas>0 && !esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
        {
            printf("\nVidas: %d\n", jugador->vidas);
            if(cant_letras_resp == 0) /// NO INGRESÓ NADA
            {
                system("cls");

                jugador->vidas--;
                printf("No ingreso ninguna secuencia.\nSe le restara una vida.\nVidas:%d\nSe mostrara nuevamente la secuencia\n",jugador->vidas);

                sleep(6);

                mostrarSecuencia(&secuencia, tiempo_mostrar, ronda, mostrar_sec);
                printf("\nIngresa la secuencia: ");

                ingresarSecuencia(&respuesta, tiempo_limite, ronda, &cant_letras_resp, &tecla);
                utilizo_vidas = 1;
            }
            else /// LA SECUENCIA ERA INCORRECTA
            {
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
                    printf("\nIngresa la secuencia: ");
                    ingresarSecuencia(&respuesta, tiempo_limite, ronda, &cant_letras_resp, &tecla);
                }
                else
                {
                    eliminarNnodosLista(&respuesta, cant_retroceso, cant_letras_resp);
                    cant_letras_resp -= cant_retroceso;
                    printf("Ingrese la secuencia faltante:\n");
                    mostrarRespuesta(&respuesta, mostrar_resp);
                    ingresarSecuencia(&respuesta, tiempo_limite, cant_retroceso, &cant_letras_resp, &tecla);
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
                vaciarLista(&respuesta);
            }
            else
            {
                printf("Secuencia correcta! +3 puntos por no usar vidas\n");
                jugador->puntuacion += 3;
                vaciarLista(&respuesta);
            }

            sleep (4);
            system("cls");
        }
        else
        {

            if(jugador->vidas==0 && !esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
                turnoTerminado=1;

        }
        ronda++;
    }

    if(turnoTerminado==1)
        printf("\nSECUENCIA INCORRECTA Y SE QUEDO SIN VIDAS.\nPUNTUACION FINAL: %d\n", jugador->puntuacion);


}






