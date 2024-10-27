#ifndef FUNCIONESJUEGO_H_INCLUDED
#define FUNCIONESJUEGO_H_INCLUDED

#define MAX_TAM_PATH 50

#include <time.h>
#include "../cola/colaDinamica.h"
#include "../lista/lista.h"
#include "../jugador/jugador.h"

//typedef struct{
//    int id;
//    char* secuencia;
//    char* respuesta;
//    unsigned vidasUsadas;
//    unsigned puntosObtenidos;
//}tRonda;

FILE* generarArchivoDeInforme(const char* nombrePrefijo);
void exportarRondasJugadorHaciaInforme(FILE* archInforme, tCola* colaTurno);
void exportarGanadoresHaciaInforme(FILE* archInforme, t_lista* ganadores);

void mostrarCaracter(const void* a,const void* b);
int cmpCaracter(const void* a, const void* b);

#endif // FUNCIONESJUEGO_H_INCLUDED
