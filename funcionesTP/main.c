#include "listaDinamica.h"
#include "funcionesJuego.h"


int main()
{
    int numeros[10];
    int ce = 5;
    tLista listaSec1, listaSec2;
    tCola cola;
    char secuencia1[15];
    char secuencia2[15];

    crearCola(&cola);
    crearLista(&listaSec1);
    crearLista(&listaSec2);

    obtenerNumerosAleatorios(numeros, ce, 1, 10);
    puts("");
    for(int i=0; i<ce; i++)
        printf("%d ", numeros[i]);
    puts("");

    generarInformeDeJuego(&cola);
//    puts("Ingrese secuencia 1: ");
//    gets(secuencia1);
//    fflush(stdin);
//    puts("Ingrese secuencia 2: ");
//    gets(secuencia2);
//
//    cargarListaConSecuencia(&listaSec1,secuencia1);
//    cargarListaConSecuencia(&listaSec2,secuencia2);
//
//    if(compararListas(&listaSec1,&listaSec2,cmpCaracter) == 1)
//        puts("Las secuencias son iguales.");
//    else
//        puts("Las secuencias son distintas.");

    return 0;
}

