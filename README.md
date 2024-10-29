# $${\color{green}Bienvenido \space \color{green}a \space \Huge\color{red}C \tiny \color{green}mon \space \color{green}dice}$$🎲

> Juego realizado en C para múltiples jugadores basado en el tradicional Simón dice.

> ## Cómo Jugar 🕹️
> **Iniciar el Juego**
> 
> 1. Ejecuta el programa y selecciona la opción **[1] Jugar**.
> 2. Ingresa los nombres de los jugadores.
> 3. Elige el nivel de dificultad:
>    - Facil
>    - Medio
>    - Difícil
> 4. El juego sorteará el orden de los jugadores y mostrará las configuraciones, incluyendo:
>    - Cantidad de vidas
>    - Tiempo para ver la secuencia de colores
>    - Tiempo para ingresar la secuencia
>      
>  **Objetivo del Juego**
>
> Memoriza e ingresa correctamente la secuencia de colores que se mostrará (R = Rojo, V = Verde, A = Amarillo, N = Naranja).
>
> La secuencia se muestra letra por letra, y debes ingresarla en el orden correcto antes de que el tiempo se acabe.
>
> **Reglas del Juego**
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
>  **Fin del Juego**
> - Cuando todos los jugadores hayan jugado sus respectivos turnos y gastado todas sus vidas, el juego finalizará, ganando el o los jugadores con más puntos obtenidos.  

> ## Configuración ⚙
> La configuración del juego se realiza automáticamentea a partir  de un archivo .txt llamado config.txt, desde el cual se obtienen los diferentes parámetros que afectan a la partida:

Dificultad | Tiempo para ver la secuenca | Tiempo para responder | Cantidad de vidas
------------- | ------------- | ------------- | -------------
Fácil| 10 segundos | 20 segundos | 3
Media| 8 segundos | 15 segundos | 2
Difícil| 5 segundos | 10 segundos | 0

> ## Requisitos del juego 📋
>   ### Sistema operativo
> - Windows
>   ### Librerias
> - Libreria CURL

> ## Testing
> Durante el desarrollo del juego se realizar diferentes pruebas para verificar el correcto funcionamiento del mismo
------------------
Descripción | Salida esperada | Salida obtenida
------------- | ------------- | -------------
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
Content Cell  | Content Cell | Content Cell
