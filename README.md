# Laboratorio-C-GrupoAbuela
Trabajo Final Integrador 
Escenario 1: Ascenso y Propulsión con el SLS (MRUV y Desprendimiento)
Comisión 1.3/C
Arroyo Federico 31790 Arroyo.Federico
Bilunyk Ivan 31247 animation3000
Calabroni Renzo 31692 Renzo
Roman Xiomara 31524 xioroman4554
Valdez Estrella 31369 Estrellavald

Descripcion del escenario:
Durante el despegue desde el Centro Espacial Kennedy, el cohete SLS eleva a la nave Orion partiendo del reposo (v0 = 0 m/s, y0 = 0 m) en un ascenso vertical rectilíneo, sin resistencia del aire. El vuelo tiene dos fases, ambas con aceleración constante:
- Fase 1: a1 = 20,0 m/s^2 durante t1 = 120,0 s, con los motores principales y los dos cohetes de combustible sólido (SRB). Al finalizar, los SRB se desacoplan.
- Fase 2: el motor del núcleo sigue acelerando con a2 = 12,5 m/s^2 hasta la altitud h = 160.000 m, donde los motores se apagan.
Si los motores fallaran en ese punto, la nave quedaría en caída libre con g = 9,80 m/s^2.

Reglas del juego
El usuario actúa como director de misión. En cada misión elige los parámetros de lanzamiento (a1, t1, a2 y h) o usa los valores del enunciado. El programa calcula el vuelo completo y evalúa si la tripulación lo soporta:
- Los parámetros deben estar dentro de estos rangos: a1 y a2 entre 1 y 100 m/s^2, t1 entre 1 y 1000 s, h entre 1.000 y 1.000.000 m.
- Si con los datos elegidos los SRB se desacoplan después de alcanzar la altitud objetivo (y1 >= h), la misión es inválida y se pide al usuario que pruebe otros valores.
- La tripulación siente la aceleración del cohete más la gravedad, es decir (a + g) / g. El límite tolerable es de 4,0 g.
- Si la aceleración sentida supera 4,0 g, la misión es FALLIDA (puntaje 0). Si no, es EXITOSA y el puntaje es 100 · (1 − g_sentida / 4,0), redondeado hacia abajo. Cuanto más suave el ascenso, más puntos.
- Se pueden realizar hasta 20 misiones por ejecución, y todas quedan guardadas en un historial.

Instrucciones de funcionamiento
El programa se ejecuta por consola y arranca con un menú principal de cinco opciones: crear una nueva misión, simular el ascenso paso a paso, ver el análisis de la última misión, ver el reporte final con el historial y salir.
Al crear una misión, el usuario ingresa los parámetros del lanzamiento (a1, t1, a2 y h) o elige usar los valores del enunciado. El programa calcula las dos fases del vuelo con las ecuaciones del MRUV, obtiene las velocidades, la altitud al desacople de los SRB y la altitud máxima en caída libre, y evalúa si la tripulación soporta la aceleración. El límite es de 4 g sentidos: si lo supera, la misión es fallida; si no, es exitosa y recibe un puntaje de 0 a 100 según qué tan suave fue el ascenso.
La simulación paso a paso muestra una tabla con el tiempo, la altitud, la velocidad y la aceleración de la nave, marcando el despegue, el desacople de los SRB y el apagado de motores. El reporte final lista todas las misiones realizadas (hasta 20) con sus resultados.
Los datos se guardan en estructuras (`Parametros`, `Resultados` y `Mision`) que se pasan por puntero a las funciones de cálculo. Todas las entradas del usuario se validan en tipo y rango, por lo que el programa no se cierra ni entra en bucle infinito ante datos erróneos.

Instrucciones claras de compilación y ejecución

Con makefile (linux, mac, github codespace):

make

./artemis

Sin makefile (sistema con gcc):

gcc -Wall -Wextra -std=c99 -o artemis main.c artemis.c validaciones.c -lm

Registro de la Inteligencia Artificial
La IA utilizada fue Claude:
Para mejorar nuestro programa, verificar su exactitud y precision al momento de ejecutarse, cumpliendo con los requisitos necesarios, se realizaron consultas como
°Revision de los archivos. MakeFile, Artemis.c y .h, Main, validación.c y .h y los demás archivos
°Como compilar el trabajo
°verificacion de que el trabajo este completo y cumpla con todas las consignas
