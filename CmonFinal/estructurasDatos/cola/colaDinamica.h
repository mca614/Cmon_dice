#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../nodo.h"

typedef struct{
    t_nodo* pri;
    t_nodo* ult;
}tCola;

//PRIMITIVAS
void crearCola(tCola* cola);
int colaVacia(const tCola* cola);
int colaLlena(const tCola* cola, unsigned tam);
int ponerEnCola(tCola* cola, unsigned tam, const void* info);
int sacarDeCola(tCola* cola, unsigned tamBuffer, void* buffer);
int verPrimero(const tCola* cola, unsigned tamBuffer, void* buffer);
void vaciarCola(tCola* cola);

//AVANZADAS
int cargarArchivoBinarioEnCola(tCola* cola, const char* path, unsigned tam);
int recorrerYMostrarColaUniforme(tCola* cola,void accion(const void* a),unsigned tam);

#endif // COLADINAMICA_H_INCLUDED
