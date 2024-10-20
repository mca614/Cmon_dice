#include "funciones.h"

void mostrarLetra( void *d,  void *param)
{
    printf("%c ", *(char *)d);
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
    return *(char*)a - *(char*)b;
}

void generarSecuencia(t_lista *secuencia)
{
    const char colores[] = {'R', 'V', 'A', 'N'};
    char color = colores[rand() % 4];
    agregarAlFinal(secuencia, &color, sizeof(char));
}

void mostrarSecuencia(t_lista *secuencia, int tiempo_mostrar, Accion accion)
{
    printf("Secuencia: ");
    mapLista(secuencia, NULL, accion);
    printf("\n");
}

void ingresarSecuencia(t_lista *respuesta, int tiempo_limite, int *cant_letras_resp)
{
    char cad_resp[100], *aux;/// tendr�a que ser dinamica
    printf("Ingresa la secuencia: ");
    fflush(stdin);
    gets(cad_resp);
    *cant_letras_resp = strlen(cad_resp);
    aux = cad_resp;
    while(*aux)
    {
        agregarAlFinal(respuesta, aux, sizeof(char));
        aux++;
    }
}

void jugarTurno(tJugador* jugador, int tiempo_mostrar, int tiempo_limite, Accion accion, Cmp cmp)
{
    t_lista secuencia, respuesta;
    crearLista(&secuencia);
    crearLista(&respuesta);

    int ronda = 1, utilizo_vidas = 0, cant_retroceso, cant_letras_resp = 0;

    printf("%s, es tu turno! Vidas: %d\n", jugador->nombre, jugador->vidas);

    while(jugador->vidas>0)
    {
        utilizo_vidas = 0;
        cant_letras_resp = 0;
        generarSecuencia(&secuencia);

        printf("\n------------------ Ronda: %d ------------------\n", ronda);

        mostrarSecuencia(&secuencia, tiempo_mostrar, accion);

        ingresarSecuencia(&respuesta, tiempo_limite, &cant_letras_resp);

        /// ASIGNAR PUNTAJE Y ACTUALIZAR VIDAS

        while(jugador->vidas>0 && !esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
        {
            printf("Vidas: %d\n", jugador->vidas);
            if(cant_letras_resp == 0) /// NO INGRES� NADA
            {
                jugador->vidas--;
                printf("No ingreso ninguna secuencia.\nSe le restara una vida\n");
                ingresarSecuencia(&respuesta, tiempo_limite, &cant_letras_resp);
                utilizo_vidas = 1;
            }
            else /// LA SECUENCIA ERA INCORRECTA
            {
                printf("Secuencia incorrecta"
                       "\nSe le restaran las vidas en base a la cantidad de jugadas que desee retroceder\n"
                       "\nIngrese la cantidad: ");
                scanf("%d", &cant_retroceso);

                while(cant_retroceso > jugador->vidas || cant_retroceso > cant_letras_resp || cant_retroceso <= 0)
                {
                    printf("Cantidad no valida. Ingrese nuevamente: ");
                    scanf("%d", &cant_retroceso);
                }

                if(cant_retroceso==cant_letras_resp)///le tiene que mostrar la sec otra vez e ingresar de nuevo
                {
                    vaciarLista(&respuesta);
                    printf("Le mostraremos nuevamente la secuencia:\n");
                    mostrarSecuencia(&secuencia, tiempo_mostrar, accion);
                    ingresarSecuencia(&respuesta, tiempo_limite, &cant_letras_resp);
                }
                else
                {
                    /// eliminarNnodosLista
                    printf("Ingrese la secuencia faltante:\n");
                    ingresarSecuencia(&respuesta, tiempo_limite, &cant_letras_resp);
                }

                jugador->vidas-=cant_retroceso;
                utilizo_vidas = 1;
            }
        }

        /// SI LA RESPUESTA ES CORRECTA SE SUMAN LOS 3 PUNTOS
        if (jugador->vidas && esSecuenciaCorrecta(&secuencia, &respuesta, cmp))
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
        }
        ronda++;
    }

    if(jugador->vidas==0)
        printf("SE QUEDO SIN VIDAS. jUEGO TERMINADO, PUNTUACION: %d\n", jugador->puntuacion);
}





