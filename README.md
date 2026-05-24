#TP_TOPICOS_2026_1C_LUNES_AURORA - Tetris Aurora
##Guía de inicio
###Descripción
Tetris Aurora es un proyecto desarrollado para la materia Tópicos de Programación de la carrera Ingeniería en Informática de la Universidad Nacional de La Matanza.
El objetivo es implementar un juego estilo Tetris en C, utilizando la biblioteca GBT para gráficos y entrada, brindando un entorno retro y amigable para la práctica de programación estructurada.

###El juego incluye:

Tablero centrado dinámicamente en ventana VGA (640x480).

Simulación de modo CGA con bloques grandes y paleta retro.

Todas las piezas originales de Tetris, con rotación en ambos sentidos.

Sistema de puntuación y estadísticas persistentes.

Velocidad dinámica de caída (aumenta un 3% cada 10 piezas).

Panel lateral con puntaje, nombre del jugador, próxima pieza y velocidad actual.

Bonificación de puntos: a mayor velocidad, mayor puntaje obtenido.

##Cómo utilizar
Instrucciones para el armado del entorno:
En el repositorio podrá encontrar el release correspondiente a cada versión de la biblioteca, con todos los archivos necesarios:


Descomprimir con 7-Zip utilizando la opción Extract Here.


En Code::Blocks, crear un nuevo proyecto Console application para el lenguaje C con el título de su preferencia, en el directorio deseado. Copie el contenido del archivo .zip anteriormente mencionado en la ruta lib\GBT_v202*.*C.**\ dentro del directorio de su proyecto.


Haga clic derecho sobre el nombre del proyecto, pulse Build options, estando sobre el Build target Debug haga click en la solapa Linker settings. En Other linker options agregue -lgbt.


Acceda al tab Search Directories:

En el tab Compiler agregue pulsando el botón add la ruta a la carpeta include/ de la biblioteca.
En el tab Linker agregue pulsando el botón add la ruta a la carpeta lib/ de la biblioteca.

Pulse OK para guardar los cambios.


Para utilizar la biblioteca en los archivos de su proyecto agregue #include "GBT/gbt.h" en los archivos .c o .h que lo requieran.


Una vez realizados todos los pasos anteriores ya puede compilar su programa.


Para poder ejecutar el programa debe copiar el archivo gbt.dll en la ruta donde se generó el resultado de la compilación (la ubicación del archivo .exe)