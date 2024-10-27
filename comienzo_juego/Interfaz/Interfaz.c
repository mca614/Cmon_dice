#include "interfaz.h"

void centrarVentanaConsola() {
    // Obtiene el manejador de la consola
    HWND ventanaConsola = GetConsoleWindow();

    // Obtiene el tamano de la pantalla
    RECT pantalla;
    GetWindowRect(GetDesktopWindow(), &pantalla);

    // Obtiene el tamano de la consola
    RECT consola;
    GetWindowRect(ventanaConsola, &consola);

    // Calcula el ancho y alto de la ventana de la consola
    int anchoConsola = consola.right - consola.left;
    int altoConsola = consola.bottom - consola.top;

    // Calcula la posicion X e Y para centrar la ventana
    int x = (pantalla.right - anchoConsola) / 2;
    int y = (pantalla.bottom - altoConsola) / 2;

    // Mueve la ventana de la consola
    SetWindowPos(ventanaConsola, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

// Función para cambiar el tamaño de la fuente de la consola
void cambiarTamanoFuente(int ancho, int alto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cf;

    cf.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, 0, &cf);

    cf.dwFontSize.X = ancho; // Ancho de la fuente
    cf.dwFontSize.Y = alto;  // Alto de la fuente
    SetCurrentConsoleFontEx(hConsole, TRUE, &cf);
}

// Función para establecer el tamaño de la consola
void establecerTamanioConsola(int ancho, int alto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT sr;
    COORD coord;

    // Establece el tamaño del buffer de la consola
    coord.X = ancho;
    coord.Y = alto;
    SetConsoleScreenBufferSize(hConsole, coord);

    // Establece el tamaño de la ventana
    sr.Left = 0;
    sr.Top = 0;
    sr.Right = ancho - 1;
    sr.Bottom = alto - 1;

    SetConsoleWindowInfo(hConsole, TRUE, &sr);
}

void deshabilitarRedimension() {
    HWND hWnd = GetConsoleWindow();
    LONG estilo = GetWindowLong(hWnd, GWL_STYLE);
    estilo &= ~WS_SIZEBOX; // Deshabilita el tamaño
    SetWindowLong(hWnd, GWL_STYLE, estilo);
    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}


void colorFondo(int cFondo, int cFuente)
{
    system("cls");
    printf("\x1b[48;5;%dm",cFondo);
    printf("\x1b[38;5;%dm",cFuente);
    printf("\x1b[2J"); // Limpia la pantalla
    printf("\x1b[H"); // Mueve el cursor a la posición (0,0)
}

void ajustarConsola(int fuenteAncho, int fuenteAlto, int consolaAncho, int consolaAlto)
{
    // Cambia el tamaño de la fuente a 18x18 (ajusta según tus necesidades)

    cambiarTamanoFuente(fuenteAncho,fuenteAlto);
    establecerTamanioConsola(consolaAncho, consolaAlto); // Ajusta según tus necesidades

    // Deshabilita la opción de redimensionar
    deshabilitarRedimension();

    centrarVentanaConsola();
}
void mostrarMenu(int opcionSeleccionada, const char opciones[][TAM_OPCION],int cantOpciones)
{
    int i;
    system("cls"); // Limpiar la consola

    for (i = 0; i < cantOpciones; i++) {
        if (i == opcionSeleccionada)
        {
            // Resaltar la opción seleccionada
            printf("\x1b[38;5;207m");
            printf("\t%s\n", opciones[i]);
            printf("\x1b[38;5;183m");
        }
        else
        {
            printf("\t%s\n", opciones[i]);
        }
    }
}

int menu(char* menu, const char opciones[][TAM_OPCION], int cantOpciones)
{
    int opcionSeleccionada = 0;
    int tecla;

    printf("\n%s\n",menu);

    while (1) {
        mostrarMenu(opcionSeleccionada, opciones, cantOpciones);

        // Captura la entrada del teclado
        tecla = _getch(); // usa _getch() para no mostrar el carácter en consola

        if (tecla == 72) { // Flecha arriba
            opcionSeleccionada = (opcionSeleccionada > 0) ? opcionSeleccionada - 1 : cantOpciones - 1;
        } else if (tecla == 80) { // Flecha abajo
            opcionSeleccionada = (opcionSeleccionada + 1) % cantOpciones;
        } else if (tecla == 13) { // Enter
            break; // Sale del bucle después de seleccionar
        }
    }

    return opcionSeleccionada;
}


void fondoRondas (int ronda, int cfuente)
{
    int colores[] = {
    GRIS_23, GRIS_22, GRIS_21, GRIS_20, GRIS_19,
    GRIS_18, GRIS_17, GRIS_16, GRIS_15, GRIS_14,
    GRIS_13, GRIS_12, GRIS_11, GRIS_10, GRIS_9,
    GRIS_8, GRIS_7, GRIS_6, GRIS_5, GRIS_4,
    GRIS_3, GRIS_2, GRIS_1, GRIS_0
    };
    int *color=colores;


    ronda>24 ? colorFondo(*(color + 23), cfuente): colorFondo(*(color + ronda -1), cfuente);

}

void colorFuente (int cFuente)
{
    printf("\x1b[38;5;%dm",cFuente);
}
