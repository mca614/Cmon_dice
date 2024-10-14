#include "funcionesJuego.h"
size_t WriteCallback(void *datosRespuesta, size_t tamBloque, size_t bloques, void *info)
{
    size_t tamDatos = tamBloque * bloques;

    tRespuesta *respuesta = (tRespuesta *)info;

    // Reservo memoria para la cadena que uso para almacenar la respuesta
    char *datos = malloc(tamDatos + 1);

    if (datos == NULL)
        return 0;

    // Completo la estructura que guarda la respuesta
    respuesta->cadena = datos;
    memcpy(respuesta->cadena, datosRespuesta, tamDatos);
    respuesta->tam = tamDatos;
    *(respuesta->cadena + respuesta->tam) = '\0';

    return tamDatos;
}

int realizarSolicitud(char *url, char *respuesta)
{
    CURL *curl;
    CURLcode res;

    // Se inicializa variable estructura para almacenar la respuesta
    tRespuesta respSolicitud;
    respSolicitud.cadena = NULL;
    respSolicitud.tam = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Se realizan configuraciones para realizar la URL de la solicitud GET
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&respSolicitud);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);


        // Se ejecuta solicitud GET
        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
            strncpy(respuesta, respSolicitud.cadena, MAX_TAM_RESP - 1);
        else
            fprintf(stderr, "Error en la solicitud: %s\n", curl_easy_strerror(res));

        free(respSolicitud.cadena);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    return curl &&  (res == CURLE_OK) ? 1 : 0;
}

void convertirCadenaNumeros(int *numeros, char *cadena)
{
    char *ptr = cadena;

    while(*ptr){
        while(*ptr == '\n')
            ptr++;

        sscanf(ptr, "%d", numeros);
        numeros++;

        while(*ptr && *ptr != '\n')
            ptr++;
    }
}

int obtenerNumerosAleatorios(int *numeros, int cantidad, int min, int max)
{
    char url[MAX_TAM_URL];
    char respuesta[MAX_TAM_RESP];
    sprintf(url, "https://www.random.org/integers/?num=%d&min=%d&max=%d&col=1&base=10&format=plain&rnd=new", cantidad, min, max);

    if(!realizarSolicitud(url, respuesta)){
        printf("\nNo se logro obtener los numeros\n");
        return 0;
    }

    //printf("\nRESPUESTA de www.random.org:\n%s\n", respuesta);
    convertirCadenaNumeros(numeros, respuesta);
    return 1;
}
int generarInformeDeJuego(tCola* cola)
{
    time_t tiempo;
    struct tm* tiempoActual;
    char nombreArchivo[MAX_TAM_PATH];
    FILE* pf;

    time(&tiempo);
    tiempoActual = localtime(&tiempo);
    sprintf(nombreArchivo,"informe-juego_%d-%02d-%02d-%02d-%02d.txt",
           tiempoActual->tm_year+1900,
           tiempoActual->tm_mon+1,
           tiempoActual->tm_mday,
           tiempoActual->tm_hour,
           tiempoActual->tm_min);

    pf = fopen(nombreArchivo,"wt");

    /////

    //IR DESACOLANDO Y GUARDAR EN ARCHIVO

    ////

    fclose(pf);
    return 1;
}
int cmpCaracter(const void* a, const void* b)
{
    return *(char*)a-*(char*)b;
}
void mostrarCaracter(const void* a,const void* b)
{
    printf("%c",*(char*)a);
}
