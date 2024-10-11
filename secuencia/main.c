#include "secuencia.h"

int main()
{

    t_lista pl;
    unsigned cantLetras = 6;

    crearLista(&pl);

    mostrarSecuencia(&pl,cantLetras);

    vaciarlista(&pl); // lista para ser reutilizada para otro jugador

    return 0;
}
