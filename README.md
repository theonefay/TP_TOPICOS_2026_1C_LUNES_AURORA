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
## Cómo utilizar

### 1. Preparación inicial
- Descargue el archivo `TP_TOPICOS_2026_1C_LUNES_{GRUPO}.zip`.
- Descomprima el `.zip` utilizando **7-Zip** con la opción **Extract Here**.
- El `.zip` contiene únicamente:
  - Archivos `.c` y `.h` desarrollados por el grupo.
  - Carpeta `/doc` con documentación.
  - Carpeta `/img` con imágenes.

⚠️ No se incluyen binarios, configuraciones del IDE ni archivos temporales.

### 2. Ubicación de carpetas
- La carpeta **Aurora** (código del grupo) debe quedar junto a la carpeta de la **Gran Biblioteca de Tópicos (GBT)**.  


### 3. Crear proyecto en Code::Blocks
- Abrir Code::Blocks.
- Crear un nuevo proyecto **Console application** en lenguaje C.
- Copiar el contenido del `.zip` en el directorio del proyecto.
- Asegurarse de que las carpetas `Aurora/` y `GBT/` estén presentes en la raíz del proyecto.

### 4. Configuración del Linker
- Clic derecho sobre el proyecto → **Build options**.
- En **Build target Debug**, ir a **Linker settings**.
- En **Other linker options**, agregar: -lgbt



### 5. Configuración de directorios
- En **Search Directories**:
- **Compiler** → agregar la ruta a `GBT/include/`.
- **Linker** → agregar la ruta a `GBT/lib/`.
- Guardar los cambios.

### 6. Compilación y ejecución
- Compilar el programa normalmente.
- Para ejecutar, copiar el archivo `gbt.dll` en la misma ruta donde se genera el `.exe`.


## Repositorio
URL: https://github.com/theonefay/TP_TOPICOS_2026_1C_LUNES_AURORA