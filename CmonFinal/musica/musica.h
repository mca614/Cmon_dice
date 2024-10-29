#ifndef MUSICA_H_INCLUDED
#define MUSICA_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <MMsystem.h>

#define MUSICA1 "musica/halloween.mp3"
#define MUSICA2 "musica/sinisterPuzzle.mp3"
#define MUSICA3 "musica/spookyToyland.mp3"
#define MUSICA4 "musica/underCorruption.mp3"
#define MUSICA5 "musica/corruption.mp3"
void reproducirMusica(const char* musica);
void cerrarMusica(); /// ASEGURA QUE SE LIBEREN LOS RECURSOS UTILIZADOS POR MCI
#endif // MUSICA_H_INCLUDED
