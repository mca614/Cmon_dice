#include "secuencia.h"

char seleccionarLetra (char* letras)
{
    char letra;
    int pos;

    obtenerNumerosAleatorios(&pos,1,1,4);

//    printf("\n%d\n", pos);
    letra =*( letras + (pos - 1 ));

    return letra;
}

int obtenerSecuencia(t_lista* plSecuencia)
{
    char letras[]="ARVN";
    char letra;

//    if(siListaLlena(plSecuencia,sizeof(char)))
//    {
//        printf("No hay espacio para agregar otra letra\n");
//        return 0;
//    }

    letra = seleccionarLetra(letras);
    agregarAlFinal(plSecuencia,&letra,sizeof(char));
    return 1;

}

int mostrarSecuencia_ (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase )
{
    unsigned i;
    int tiempo;
    for(i=0; i<cantLetras; i++)
    {

        if(!(obtenerSecuencia(plSecuencia)))
            return 0;

        // para que vean la secuencia esto en el juego no va a estar
        printf("\n secuencia numero %d\n",i +1);
        mapLista(plSecuencia,NULL,mostrarLetra_); // lista completa
        system("pause");
        system("cls");
        //

        tiempo = tiempoBase/(i+1);

        mapLista(plSecuencia,&tiempo,mostrarLetra); // letra por letra
    }
    return 1;
}

//int mostrarSecuencia (t_lista* plSecuencia, unsigned cantLetras, unsigned tiempoBase, void accion (void* a, void* b))
//{
//    int tiempo;
//    if(!(obtenerSecuencia(plSecuencia)))
//            return 0;
//
//    tiempo = tiempoBase/(cantLetras);
//    mapLista(plSecuencia,&tiempo,accion);
//    return 1;
//}

void mostrarLetra (const void * dato,const void * cond)
{
    char* letra = (char*) dato;
    int tiempo = *(int*) cond;

    switch(*letra)
    {
        case 'R':
            system("cls");
            printf("\x1b[38;5;197m"); // color
            printf("\t%c\t",*letra);
            printf("\033[0m"); // limita
            break;

        case 'V':
            system("cls");
            printf("\x1b[38;5;82m");
            printf("\t%c\t",*letra);
            printf("\033[0m");
            break;

        case 'N':
            system("cls");
            printf("\x1b[38;5;208m");
            printf("\t%c\t",*letra);
            printf("\033[0m");
            break;

        case 'A':
            system("cls");
            printf("\x1b[38;5;226m");
            printf("\t%c\t",*letra);
            printf("\033[0m");
            break;
    }

    fflush(stdout); // Asegurar que el mensaje se imprima antes de la pausa
    sleep(tiempo); // Pausa de 2 segundos
    system("cls");
    printf(" "); // porque no se diferenciaba si habia dos letras iguales seguidas
    usleep(300000);// Pausa de 0.3 segundos
    system("cls");
}

void mostrarLetra_ (const void * dato,const void * cond)
{
    char* letra = (char*) dato;
    printf("%c\t",*letra);
}


