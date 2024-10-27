#include "interfaz.h"


#include <stdio.h>
#include <windows.h>

#define COLOR_RESET        "\x1b[0m"


int main() {
    const char *texto = "Texto Colorido en Escala de Grises";
    int colores[] = {GRIS_23, GRIS_22, GRIS_21, GRIS_20, GRIS_19, GRIS_18,
                     GRIS_17, GRIS_16, GRIS_15, GRIS_14, GRIS_13, GRIS_12,
                     GRIS_11, GRIS_10, GRIS_9, GRIS_8, GRIS_7, GRIS_6,
                     GRIS_5, GRIS_4, GRIS_3, GRIS_2, GRIS_1, GRIS_0};
    int numColores = 26;

    // Ciclo para cambiar el color del texto
    for (int i = 0; i < numColores; i++) { // Cambiar de color según la cantidad de colores
//        int colorActual = colores[i]; // Seleccionar el color
//
//        // Limpiar la consola (opcional)
//        system("cls"); // Usar "clear" en sistemas UNIX
//
//        // Imprimir el texto con el color actual
//        printf("\x1b[38;5;%dm%s%s\n", colorActual, texto, COLOR_RESET);

    fondoRondas(i+1,COLOR_CIAN);
    printf("hola");

        // Esperar un segundo antes de cambiar de color
        Sleep(1000); // 1000 ms = 1 segundo
    }

    // Restablecer colores

    colorFuente(COLOR_AMARILLO);
    printf("%sFin del ejemplo.%s\n", COLOR_RESET, COLOR_RESET);

    return 0;
}

//
//int main() {
////    int opcionSeleccionada = 0;
////    int tecla;
//
//    const char opciones[][30] = {
//        "Opcion 1: Mostrar mensaje 1",
//        "Opcion 2: Mostrar mensaje 2",
//        "Opcion 3: Mostrar mensaje 3",
//        "Opcion 4: Mostrar mensaje 4",
//        "Opcion 5: Salir"
//    };
//
//    ajustarConsola(30,30,80,25);
//    colorFondo("\x1b[48;5;230m","\x1b[38;5;183m");
//
//
//
//    menu("opciones a elegir", opciones, 5);
//
//////    siste
////
////    while (1) {
////        mostrarMenu(opcionSeleccionada);
////
////        // Captura la entrada del teclado
////        tecla = _getch(); // usa _getch() para no mostrar el carácter en consola
////
////        if (tecla == 72) { // Flecha arriba
////            opcionSeleccionada = (opcionSeleccionada > 0) ? opcionSeleccionada - 1 : NUM_OPCIONES - 1;
////        } else if (tecla == 80) { // Flecha abajo
////            opcionSeleccionada = (opcionSeleccionada + 1) % NUM_OPCIONES;
////        } else if (tecla == 13) { // Enter
////            printf("Seleccionaste: %s\n", (opcionSeleccionada == 0) ? "Opcion 1" :
////                                            (opcionSeleccionada == 1) ? "Opcion 2" : "Opcion 3");
////            break; // Sale del bucle después de seleccionar
////        }
////    }
//
//    return 0;
//}


//#include <windows.h>
//#include <stdio.h>
//
//
//int main() {
//
//    ajustarConsola(30,30,80,25);
//    colorFondo("\x1b[48;5;147m","\x1b[38;5;0m");
//
//    // Imprime un mensaje
//    printf("Texto con tamaño de fuente agrandado sin cambiar el tamaño de la ventana.\n");
//
//    ajustarConsola(15,15,80,25);
//    printf("Texto con tamaño de fuente agrandado sin cambiar el tamaño de la ventana.\n");
//    printf("Texto con tamaño de fuente agrandado sin cambiar el tamaño de la ventana.\n");
//
//    printf("Presiona una tecla para continuar...\n");
//
//    // Espera a que el usuario presione una tecla
//    getchar();
//
//
//
//    return 0;
//}
