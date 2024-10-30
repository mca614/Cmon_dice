#include "musica.h"

void reproducirMusica(const char* musica)
{
    /// verificacion TRUE -> Reproduce archivo WAV usando PlaySound
    /// verificacion FALSE -> Comando para reproducir MP3 con MCI (Media Control Interface)
    char comando[256];
    if(strstr(musica,".wav") != NULL)
    {
        PlaySound(musica,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else
    {
        sprintf(comando, "open \"%s\" type mpegvideo alias mp3", musica);
        mciSendString(comando, NULL, 0, NULL);

        mciSendString("play mp3 repeat", NULL, 0, NULL);
    }
}
void cerrarMusica()
{
    mciSendString("close mp3", NULL, 0, NULL);
}
