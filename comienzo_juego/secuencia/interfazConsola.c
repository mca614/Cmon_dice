#include "interfazConsola.h"


void cambiarTamanioFuente(int ancho, int alto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Cambiar el tamaño de la fuente
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

    cfi.dwFontSize.X = ancho; // Ancho de la fuente
    cfi.dwFontSize.Y = alto;  // Alto de la fuente
    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void centrarLetra (char texto) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int anchoConsola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//    int largoTexto = strlen(texto);

    int espacios = (anchoConsola - 1) / 2;

    for (int i = 0; i < espacios; i++) {
        printf(" ");
    }
    printf("%c\n", texto);
}


void centrarConsola_() {
    // Obtener el handle de la consola
    HWND consola = GetConsoleWindow();

    // Obtener el tamaño de la pantalla
    RECT pantalla;
    GetWindowRect(GetDesktopWindow(), &pantalla);

    // Obtener el tamaño de la ventana de la consola
    RECT consolaRect;
    GetWindowRect(consola, &consolaRect);

    // Calcular la posición centrada
    int anchoPantalla = pantalla.right - pantalla.left;
    int altoPantalla = pantalla.bottom - pantalla.top;

    int anchoConsola = consolaRect.right - consolaRect.left;
    int altoConsola = consolaRect.bottom - consolaRect.top;

    int x = (anchoPantalla - anchoConsola) / 2;
    int y = (altoPantalla - altoConsola) / 2;

    // Mover la ventana de la consola
    SetWindowPos(consola, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
