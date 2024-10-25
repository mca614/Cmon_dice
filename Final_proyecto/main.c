#include "listaDinamica.h"
#include "funcionesJuego.h"

void mostrarJugador(const void*a,const void*b);

int main()
{
//    FILE* archivo;
//    archivo = generarArchivoDeInforme("informe-juego");
    tLista lista;
    tJugador aux;
    tJugador jug[]= {{2,"Tomas Modestti",2,120},
                    {3,"Abel",2,50},
                    {9,"Noelia",3,90},
                    {5,"Miguel",1,20},
                    {6,"Juan",0,120},
                    {9,"Noelia Legrant",3,120}};
    crearLista(&lista);
     FILE* arch= fopen("lote.dat","wb");
     if(!arch)
        return 1;
     fwrite(jug,sizeof(jug),1,arch);
     fclose(arch);

     FILE* cargaArch= fopen("lote.dat","rb");
     if(!cargaArch)
        return 1;
     fread(&aux,sizeof(tJugador),1,cargaArch);
     while(!feof(cargaArch))
     {
        agregarAlFinalDeLista(&lista,&aux,sizeof(tJugador));
        fread(&aux,sizeof(tJugador),1,cargaArch);
     }
     fclose(cargaArch);

     puts("RECORRER LISTA");
     recorrerLista(&lista,mostrarJugador);
     mostrarGanadores(&lista);
    return 0;
}

void mostrarJugador(const void*a,const void*b)
{
    tJugador* aux= (tJugador*) a;
    printf("%d|%s|%d|%d\n", aux->id,aux->nombre,aux->vidas,aux->puntuacion);
}

