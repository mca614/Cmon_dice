#include "secuencia.h"

char seleccionarLetra (char* letras)
{
    char letra;
    int pos;

    obtenerNumerosAleatorios(&pos,1,1,4);
    letra =*( letras + (pos - 1 ));

    return letra;
}

int obtenerSecuencia(t_lista* plSecuencia)
{
    char letras[]="ARVN";
    char letra;
    letra = seleccionarLetra(letras);
    agregarAlFinal(plSecuencia, &letra, sizeof(char));
    return 1;
}

//int mostrarSecuencia_ (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase )
//{
//    unsigned i;
//    int tiempo;
//    for(i=0; i<cantLetras; i++)
//    {
//
//        if(!(obtenerSecuencia(plSecuencia)))
//            return 0;
//
//        // para que vean la secuencia esto en el juego no va a estar
//        printf("\n secuencia numero %d\n",i +1);
//        mapLista(plSecuencia, NULL, mostrarLetra_); // lista completa
//        system("pause");
//        system("cls");
//        //
//
//        tiempo = tiempoBase/(i+1);
//
//        mapLista(plSecuencia, &tiempo, mostrarLetraSecuencia); // letra por letra
//    }
//    return 1;
//}

void mostrarLetraSecuencia ( void * dato, void * cond)
{
    char* letra = (char*) dato;
    int tiempo = *(int*) cond;

    switch(*letra)
    {
        case 'R':
            system("cls");
            printf("\n\n\n\n");
            printf("\x1b[38;5;197m"); // color
            printf("\t\t   ||||||   \n");
            printf("\t\t |||     |||  \n");
            printf("\t\t |||     ||| \n");
            printf("\t\t ||||||||   \n");
            printf("\t\t |||    |||    \n");
            printf("\t\t |||     |||   \n");
//            printf("\x1b[1m\n\n\t\t  %c\t\x1b[22m",*letra);
            printf("\033[0m"); // limita
            break;

        case 'V':
            system("cls");
            printf("\n\n\n\n");
            printf("\x1b[38;5;82m");
            printf("\t\t|||        ||| \n");
            printf("\t\t |||      ||| \n");
            printf("\t\t  |||    |||  \n");
            printf("\t\t   |||  |||  \n");
            printf("\t\t     ||||    \n");
//            printf("\x1b[1m\n\n\t\t  %c\t\x1b[22m",*letra);
            printf("\033[0m");
            break;

        case 'N':
            system("cls");
            printf("\n\n\n\n");
            printf("\x1b[38;5;208m");
            printf("\t\t ||||       |||\n");
            printf("\t\t|||  |||    |||\n");
            printf("\t\t|||   |||   |||\n");
            printf("\t\t|||    |||  |||\n");
            printf("\t\t|||     ||| |||\n");
            printf("\t\t|||       |||| \n");
//            printf("\x1b[1m\n\n\t\t  %c\t\x1b[22m",*letra);
            printf("\033[0m");
            break;

        case 'A':
            system("cls");
            printf("\n\n\n\n");
            printf("\x1b[38;5;226m");
            printf("\t\t     ||||   \n");
            printf("\t\t   |||  |||   \n");
            printf("\t\t  |||____|||  \n");
            printf("\t\t |||      ||| \n");
            printf("\t\t|||        ||| \n");
//            printf("\x1b[1m\n\n\t\t  %c\t\x1b[22m",*letra);
            printf("\033[0m");
            break;
    }


    fflush(stdout); // Asegurar que el mensaje se imprima antes de la pausa
    //sleep(tiempo); // Pausa de 2 segundos
    Sleep(tiempo);
    system("cls");
    printf(" "); // porque no se diferenciaba si habia dos letras iguales seguidas
    //usleep(300000);// Pausa de 0.3 segundos
    Sleep(300);
    system("cls");
    colorFondo(VIOLETA_4, VERDE_MEDIO);
}

void mostrarLetra_ ( void * dato, void * cond)
{
    char* letra = (char*) dato;
    printf("%c\t",*letra);
}


