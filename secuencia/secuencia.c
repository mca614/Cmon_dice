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

    if(siListaLlena(plSecuencia,sizeof(char)))
    {
        printf("No hay espacio para agregar otra letra\n");
        return 0;
    }

    letra = seleccionarLetra(letras);
    agregarAlFinal(plSecuencia,&letra,sizeof(char));
    return 1;

}

int mostrarSecuencia (t_lista* plSecuencia, unsigned cantLetras)
{
    unsigned i;
    for(i=0; i<cantLetras; i++)
    {

        if(!(obtenerSecuencia(plSecuencia)))
            return 0;

        // para que vean la secuencia esto en el juego no va a estar
        printf("\n secuencia numero %d\n",i +1);
        map_TDAlista(plSecuencia,NULL,mostrarLetra_);
        system("pause");
        system("cls");

        //

        map_TDAlista(plSecuencia,NULL,mostrarLetra);
    }
    return 1;
}

void mostrarLetra (void* dato, void* cond)
{
    char* letra = (char*) dato;
    printf("\t%c\t",*letra);

    fflush(stdout); // Asegurar que el mensaje se imprima antes de la pausa
    sleep(2); // Pausa de 2 segundos
    system("cls");
    printf(" "); // porque no se diferenciaba si habia dos letras iguales seguidas
    usleep(300000);// Pausa de 0.3 segundos
    system("cls");
}

void mostrarLetra_ (void* dato, void* cond)
{
    char* letra = (char*) dato;
    printf("%c\t",*letra);
}

