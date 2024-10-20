#include "cronometro.h"


void* hiloCronometro(void* arg) {
    t_cronometroDatos* datos = (t_cronometroDatos*)arg;
    time_t tiempoInicio;
    time(&tiempoInicio);

    while (!datos->tiempoAcabado) {
        time_t tiempoActual;
        time(&tiempoActual);
        double tiempoTranscurrido = difftime(tiempoActual, tiempoInicio);

        if (tiempoTranscurrido >= datos->limiteTiempo) {
            datos->tiempoAcabado = 1;
            printf("\nSe acabo el tiempo! ingrese cualquier tecla para continuar\n");
//            system("cls");
//            system("pause");
            break;
        }
    }
    return NULL;
}

void crearHiloCronometro(pthread_t* cronometro, t_cronometroDatos* datos) {
    datos->tiempoAcabado = 0;
    pthread_create(cronometro, NULL, hiloCronometro, (void*) datos);
}

//void crearHiloCronometro(pthread_t* cronometro, int* tiempoAcabado) {
//    pthread_create(cronometro, NULL, hiloCronometro, (void*) tiempoAcabado);
//}

void esperarHiloCronometro(pthread_t* cronometro) {
    pthread_join(*cronometro, NULL);
    printf("El hilo del cronometro ha terminado.\n");
    system("cls");
//    system("pause");
}

