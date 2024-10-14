#include "secuencia.h"

int main()
{

    t_lista pl;
    unsigned cantLetras = 6;
    unsigned tiempoBase = 12;

    crearLista(&pl);

    mostrarSecuencia_ (&pl,cantLetras,tiempoBase);

    printf("\nEn el juego se va a ver asi: \n");
    system("pause");
    system("cls");
    mostrarSecuencia(&pl,cantLetras,tiempoBase); // funcion que se va a usar en la funcion

    vaciarlista(&pl); // lista para ser reutilizada para otro jugador

    return 0;
}
