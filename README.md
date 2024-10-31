# $${\color{green}Bienvenido \space \color{green}a \space \Huge\color{red}C \tiny \color{green}mon \space \color{green}dice}$$🎲

> Cmon Dice es un juego de memoria inspirado en el conocido "Simón Dice", en el que los jugadores deben recordar e ingresar secuencias de colores mostradas en pantalla. Los jugadores tienen un
> tiempo limitado para memorizar y reproducir la secuencia.
> ## Cómo Jugar 🕹️
> **Iniciar el Juego** 🎮
> 
> 1. Ejecuta el programa y selecciona la opción **[A] Jugar**.
> 2. Ingresa los nombres de los jugadores.
> 3. Elige el nivel de dificultad:
>    - Facil
>    - Medio
>    - Difícil
> 4. Se sorteará el orden de los jugadores
> 5. Se mostrarán las configuraciones, incluyendo:
>    - Cantidad de vidas
>    - Tiempo para ver la secuencia de colores
>    - Tiempo para ingresar la secuencia
>      
>  **Objetivo del Juego** :dart:
>
> Memoriza e ingresa correctamente la secuencia de colores que se mostrará (R = Rojo, V = Verde, A = Amarillo, N = Naranja).
>
> La secuencia se muestra letra por letra, y debes ingresarla en el orden correcto antes de que el tiempo se acabe.
>
> **Reglas del Juego** 📖
> - Secuencia Correcta:
>     - Si ingresas la secuencia sin usar vidas, obtienes +3 puntos.
>     - Si usas vidas, obtienes +1 punto por secuencia correcta.
>  - Errores:
>     - Si ingresas incorrectamente la secuencia o se acaba el tiempo, puedes usar tus vidas para deshacer los errores y reintentar.
>  - Fin del Turno:
>    - El turno de un jugador finaliza cuando:
>      - Se queda sin vidas.
>      - Completa la secuencia correctamente sin errores.
>   
>  **Fin del Juego** 🏆
> - Cuando todos los jugadores hayan jugado sus respectivos turnos y gastado todas sus vidas, el juego finalizará, ganando el o los jugadores con más puntos obtenidos.  

> ## Configuración ⚙
> La configuración del juego se realiza automáticamente a partir  de un archivo .txt llamado config.txt, desde el cual se obtienen los diferentes parámetros que afectan a la partida:

Dificultad | Tiempo para ver la secuenca | Tiempo para responder | Cantidad de vidas
------------- | ------------- | ------------- | -------------
Fácil| 10 segundos | 20 segundos | 3
Media| 8 segundos | 15 segundos | 2
Difícil| 5 segundos | 10 segundos | 0

> ## Requisitos del juego 📋
> ### Sistema operativo
>   - Windows
> ### Libreria CURL:
> 1) Instalar Curl en Windows (https://curl.se/windows/)
> 2) Descomprimir el zip y copiar la carpeta a una ubicación que no se modifique en el futuro
> 3) Agregar dentro de PATH (como variable de entorno) la ubicación a la carpeta “bin”
> 4) En el IDE: Settings > Compiler > Linker Settings: agregar ubicación a “lib\libcurl.dll.a”
> 5) En el IDE: Settings > Compiler > Search directories > Compiler y Resource compiler: agregar ubicación a “include”
> 6) En el IDE: Settings > Compiler > Search directories > Linker: agregar ubicación a “lib”

