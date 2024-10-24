#include "funcionesJuego.h"
#include "musica.h"

int main()
{
    char comando[256];
    const char* archivo = "Music/musica.mp3";

    // TRUE -> Reproduce archivo WAV usando PlaySound
    if(strstr(archivo,".wav") != NULL)
    {
        PlaySound(archivo,NULL,SND_FILENAME | SND_ASYNC);
        printf("Reproduciendo WAV:\n");

        printf("Presiona Enter para detener la musica...\n");
        getchar();
    }
    // FALSE -> Comando para reproducir MP3 con MCI (Media Control Interface)
    else
    {
        sprintf(comando, "open \"%s\" type mpegvideo alias mp3", archivo);
        mciSendString(comando, NULL, 0, NULL);

        mciSendString("play mp3", NULL, 0, NULL);
        printf("Reproduciendo MP3:\n");

        printf("Presiona Enter para detener la musica...\n");
        getchar();
    }

    return 0;
}

