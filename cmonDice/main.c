#include "funciones.h"

int main()
{
    srand(time(NULL)); // Inicializar la semilla aleatoria

    tJugador jugador = {1, 1, 0, 5, "Melina"};

    jugarTurno(&jugador, 1, 5, mostrarLetra, cmp_letras); // Ejemplo: tiempo_mostrar = 1 segundo, tiempo_limite = 5 segundos, longitud_secuencia = 5

    printf("Jugador %s, puntuacion: %d, vidas: %d\n", jugador.nombre, jugador.puntuacion, jugador.vidas);

    return 0;
}