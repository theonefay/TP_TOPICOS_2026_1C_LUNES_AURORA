#include "Dibujo.h"
#include "Constantes.h"
#include "Piezas.h"
#include "FuenteLetras.h"
#include "Fuente.h"
#include <string.h>


void dibujarBloque(int xPantalla, int yPantalla, int tam, int color)
{
    int grosor = 2; // grosor del borde
    int color_sup = 8;
    int color_inf = 7;

    int x, y;


    //  CENTRO DEL BLOQUE
    for (y = grosor; y < tam - grosor; y++)
    {
        for (x = grosor; x < tam - grosor; x++)
        {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color);
        }
    }

    //BORDE SUPERIOR
    for (y = 0; y < grosor; y++)
    {
        for (x = 0; x < tam; x++)
        {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color_sup);
        }
    }

    // BORDE IZQUIERDO
    for (x = 0; x < grosor; x++)
    {
        for (y = 0; y < tam; y++)
        {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color_sup);
        }
    }


    //BORDE INFERIOR
    for (y = 0; y < grosor; y++)
    {
        for (x = 0; x < tam; x++)
        {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + tam - 1 - y, color_inf);
        }
    }

    //  BORDE DERECHO (OSCURO)
    for (x = 0; x < grosor; x++)
    {
        for (y = 0; y < tam; y++)
        {
            gbt_dibujar_pixel(xPantalla + tam - 1 - x, yPantalla + y, color_inf);
        }
    }

    // ESQUINAS

    // arriba izquierda
    gbt_dibujar_pixel(xPantalla, yPantalla, color_sup);

    // arriba derecha
    gbt_dibujar_pixel(xPantalla + tam - 1, yPantalla, color_sup);

    // abajo izquierda
    gbt_dibujar_pixel(xPantalla, yPantalla + tam - 1, color_inf);

    // abajo derecha
    gbt_dibujar_pixel(xPantalla + tam - 1, yPantalla + tam - 1, color_inf);
}







// Dibuja el tablero completo
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            int valor = tablero[i][j];

            if (valor != VACIO)
            {
                dibujarBloque(TABLERO_X + j * tamBloque,TABLERO_Y + i * tamBloque,tamBloque,valor);


            }
        }
    }
}


void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho) {


    int ancho = columnas * tamBloque;
    int alto  = filas * tamBloque;

    int xInicio = TABLERO_X - grosor;
    int yInicio = TABLERO_Y - grosor;

    int anchoTotal = ancho + 2 * grosor;
    int altoTotal  = alto + 2 * grosor;

    // Borde superior
    for (int y = 0; y < grosor; y++) {
        for (int x = 0; x < anchoTotal; x++) {
            gbt_dibujar_pixel(xInicio + x, yInicio + y, colorSuperior);
        }
    }

    // Borde inferior
    for (int y = alto + grosor; y < altoTotal; y++) {
        for (int x = 0; x < anchoTotal; x++) {
            gbt_dibujar_pixel(xInicio + x, yInicio + y, colorInferior);
        }
    }

    // Borde izquierdo
    for (int x = 0; x < grosor; x++) {
        for (int y = 0; y < altoTotal; y++) {
            gbt_dibujar_pixel(xInicio + x, yInicio + y, colorIzquierdo);
        }
    }

    // Borde derecho
    for (int x = ancho + grosor; x < anchoTotal; x++) {
        for (int y = 0; y < altoTotal; y++) {
            gbt_dibujar_pixel(xInicio + x, yInicio + y, colorDerecho);
        }
    }
}

// Dibuja una pieza desde matriz gen�rica
void dibujarMatriz(int filas, int cols, int pieza[filas][cols],
                   int posCeldaX, int posCeldaY, int tamBloque, int color)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (pieza[i][j] == 1)
            {
                dibujarBloque(TABLERO_X + (posCeldaX + j) * tamBloque,TABLERO_Y + (posCeldaY + i) * tamBloque,tamBloque,color);
            }
        }
    }
}

// Dibuja directamente una Pieza estructurada
void dibujarPiezaStruct(Pieza *p, int tamBloque) {
    dibujarMatriz(3, 3, p->matriz, p->posX, p->posY, tamBloque, p->color);
}

void dibujarPanel(int x, int y, int ancho, int alto, int color)
{
    // superior
    for (int i = 0; i < ancho; i++)
    {
        gbt_dibujar_pixel(x + i, y, color);
    }

    // inferior
    for (int i = 0; i < ancho; i++)
    {
        gbt_dibujar_pixel(x + i, y + alto, color);
    }

    // izquierda
    for (int i = 0; i < alto; i++)
    {
        gbt_dibujar_pixel(x, y + i, color);
    }

    // derecha
    for (int i = 0; i < alto; i++)
    {
        gbt_dibujar_pixel(x + ancho, y + i, color);
    }
}
void dibujarMarcoPanel(
    int x,
    int y,
    int ancho,
    int alto,
    int grosor,
    int colorSuperior,
    int colorInferior,
    int colorIzquierdo,
    int colorDerecho
)
{
    // superior
    for (int py = 0; py < grosor; py++)
    {
        for (int px = 0; px < ancho; px++)
        {
            gbt_dibujar_pixel(x + px, y + py, colorSuperior);
        }
    }

    // inferior
    for (int py = alto - grosor; py < alto; py++)
    {
        for (int px = 0; px < ancho; px++)
        {
            gbt_dibujar_pixel(x + px, y + py, colorInferior);
        }
    }

    // izquierdo
    for (int px = 0; px < grosor; px++)
    {
        for (int py = 0; py < alto; py++)
        {
            gbt_dibujar_pixel(x + px, y + py, colorIzquierdo);
        }
    }

    // derecho
    for (int px = ancho - grosor; px < ancho; px++)
    {
        for (int py = 0; py < alto; py++)
        {
            gbt_dibujar_pixel(x + px, y + py, colorDerecho);
        }
    }
}

void pantallaPresentacion()
{
    gbt_borrar_backbuffer(0);

    // Texto "TETRIS AURORA" más grande y centrado
    int escala = 7;
    int anchoTitulo = strlen("TETRIS AURORA") * 6 * escala;
    int xBase = ANCHO_VENTANA/2 - anchoTitulo/2;
    int yBase = ALTO_VENTANA/2 - 60;

    // "TETRIS"
    dibujarTexto("T", xBase, yBase, escala, 12); // rojo
    dibujarTexto("E", xBase + 6*escala, yBase, escala, 11); // cyan
    dibujarTexto("T", xBase + 12*escala, yBase, escala, 14); // amarillo
    dibujarTexto("R", xBase + 18*escala, yBase, escala, 10); // verde
    dibujarTexto("I", xBase + 24*escala, yBase, escala, 13); // magenta
    dibujarTexto("S", xBase + 30*escala, yBase, escala, 9);  // azul

    // "AURORA"
    dibujarTexto("A", xBase + 38*escala, yBase, escala, 11);
    dibujarTexto("U", xBase + 44*escala, yBase, escala, 14); // amarillo
    dibujarTexto("R", xBase + 50*escala, yBase, escala, 12); // rojo
    dibujarTexto("O", xBase + 56*escala, yBase, escala, 9); // cyan
    dibujarTexto("R", xBase + 62*escala, yBase, escala, 10); // verde
    dibujarTexto("A", xBase + 68*escala, yBase, escala, 13); // magenta


    gbt_volcar_backbuffer();

    while (!gbt_tecla_presionada(GBTK_ENTER))
    {
        gbt_procesar_entrada();
        gbt_esperar(16);
    }
}



int menuInicial()
{
    int opcion = 0; // 0=Jugar, 1=Config, 2=Stats, 3=Salir

    while (1)
    {
        gbt_borrar_backbuffer(0);

        // Título multicolor centrado
        int escalaTitulo = 6;
        int anchoTitulo = strlen("TETRIS") * 7 * escalaTitulo;
        int xTitulo = ANCHO_VENTANA/2 - anchoTitulo/2;
        int yTitulo = 80;

        char* titulo = "TETRIS";
        for (int i = 0; titulo[i] != '\0'; i++) {
            char letra[2] = { titulo[i], '\0' };
            int color = 9 + (i % 6); // alterna colores vivos
            dibujarTexto(letra, xTitulo + i*7*escalaTitulo, yTitulo, escalaTitulo, color);
        }

        // Opciones multicolor centradas
        int escalaOpc = 4;
        int yBase = 200;
        int salto = 60;

        // JUGAR
        char* jugar = "JUGAR";
        int anchoJugar = strlen(jugar) * 7 * escalaOpc;
        int xJugar = ANCHO_VENTANA/2 - anchoJugar/2;
        for (int i = 0; jugar[i] != '\0'; i++) {
            char letra[2] = { jugar[i], '\0' };
            int color = (opcion==0) ? (9 + (i % 6)) : 7;
            dibujarTexto(letra, xJugar + i*7*escalaOpc, yBase, escalaOpc, color);
        }

        // CONFIGURACION
        yBase += salto;
        char* config = "CONFIGURACION";
        int anchoConfig = strlen(config) * 7 * escalaOpc;
        int xConfig = ANCHO_VENTANA/2 - anchoConfig/2;
        for (int i = 0; config[i] != '\0'; i++) {
            char letra[2] = { config[i], '\0' };
            int color = (opcion==1) ? (9 + (i % 6)) : 7;
            dibujarTexto(letra, xConfig + i*7*escalaOpc, yBase, escalaOpc, color);
        }

        // ESTADISTICAS
        yBase += salto;
        char* stats = "ESTADISTICAS";
        int anchoStats = strlen(stats) * 7 * escalaOpc;
        int xStats = ANCHO_VENTANA/2 - anchoStats/2;
        for (int i = 0; stats[i] != '\0'; i++) {
            char letra[2] = { stats[i], '\0' };
            int color = (opcion==2) ? (9 + (i % 6)) : 7;
            dibujarTexto(letra, xStats + i*7*escalaOpc, yBase, escalaOpc, color);
        }

        // SALIR
        yBase += salto;
        char* salir = "SALIR";
        int anchoSalir = strlen(salir) * 7 * escalaOpc;
        int xSalir = ANCHO_VENTANA/2 - anchoSalir/2;
        for (int i = 0; salir[i] != '\0'; i++) {
            char letra[2] = { salir[i], '\0' };
            int color = (opcion==3) ? (9 + (i % 6)) : 7;
            dibujarTexto(letra, xSalir + i*7*escalaOpc, yBase, escalaOpc, color);
        }

        gbt_volcar_backbuffer();
        gbt_procesar_entrada();

        // Navegación con flechas
        if (gbt_tecla_presionada(GBTK_ARRIBA)) opcion = (opcion+3)%4;
        if (gbt_tecla_presionada(GBTK_ABAJO))  opcion = (opcion+1)%4;

        // Selección con ENTER
        if (gbt_tecla_presionada(GBTK_ENTER)) return opcion;

        gbt_esperar(16);
    }
}





void ingresarNombre(char* nombre, int maxLen)
{
    int pos = 0;
    nombre[0] = '\0';

    while (1)
    {
        gbt_procesar_entrada();

        // Letras A–Z
        if (gbt_tecla_presionada(GBTK_a) && pos < maxLen-1) { nombre[pos++] = 'A'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_b) && pos < maxLen-1) { nombre[pos++] = 'B'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_c) && pos < maxLen-1) { nombre[pos++] = 'C'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_d) && pos < maxLen-1) { nombre[pos++] = 'D'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_e) && pos < maxLen-1) { nombre[pos++] = 'E'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_f) && pos < maxLen-1) { nombre[pos++] = 'F'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_g) && pos < maxLen-1) { nombre[pos++] = 'G'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_h) && pos < maxLen-1) { nombre[pos++] = 'H'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_i) && pos < maxLen-1) { nombre[pos++] = 'I'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_j) && pos < maxLen-1) { nombre[pos++] = 'J'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_k) && pos < maxLen-1) { nombre[pos++] = 'K'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_l) && pos < maxLen-1) { nombre[pos++] = 'L'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_m) && pos < maxLen-1) { nombre[pos++] = 'M'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_n) && pos < maxLen-1) { nombre[pos++] = 'N'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_o) && pos < maxLen-1) { nombre[pos++] = 'O'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_p) && pos < maxLen-1) { nombre[pos++] = 'P'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_q) && pos < maxLen-1) { nombre[pos++] = 'Q'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_r) && pos < maxLen-1) { nombre[pos++] = 'R'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_s) && pos < maxLen-1) { nombre[pos++] = 'S'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_t) && pos < maxLen-1) { nombre[pos++] = 'T'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_u) && pos < maxLen-1) { nombre[pos++] = 'U'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_v) && pos < maxLen-1) { nombre[pos++] = 'V'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_w) && pos < maxLen-1) { nombre[pos++] = 'W'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_x) && pos < maxLen-1) { nombre[pos++] = 'X'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_y) && pos < maxLen-1) { nombre[pos++] = 'Y'; nombre[pos] = '\0'; }
        if (gbt_tecla_presionada(GBTK_z) && pos < maxLen-1) { nombre[pos++] = 'Z'; nombre[pos] = '\0'; }

        // Espacio
        if (gbt_tecla_presionada(GBTK_ESPACIO) && pos < maxLen-1) {
            nombre[pos++] = ' ';
            nombre[pos] = '\0';
        }

        // Backspace
        if (gbt_tecla_presionada(GBTK_RETROCESO) && pos > 0) {
            pos--;
            nombre[pos] = '\0';
        }

        // Confirmar con ENTER
        if (gbt_tecla_presionada(GBTK_ENTER)) break;

        // Dibujar pantalla de ingreso
        gbt_borrar_backbuffer(0);

        // Texto fijo centrado y multicolor
        char* titulo = "INGRESE SU NOMBRE";
        int escalaTitulo = 4;
        int anchoTitulo = strlen(titulo) * 7 * escalaTitulo;
        int xTitulo = ANCHO_VENTANA/2 - anchoTitulo/2;
        int yTitulo = ALTO_VENTANA/2 - 60;

        for (int i = 0; titulo[i] != '\0'; i++) {
            char letra[2] = { titulo[i], '\0' };
            int color = 9 + (i % 6); // alterna colores retro
            dibujarTexto(letra, xTitulo + i*7*escalaTitulo, yTitulo, escalaTitulo, color);
        }

        // Nombre centrado dinámicamente y multicolor
        int escalaNombre = 4;
        int anchoNombre = strlen(nombre) * 7 * escalaNombre;
        int xNombre = ANCHO_VENTANA/2 - anchoNombre/2;
        int yNombre = ALTO_VENTANA/2;

        for (int i = 0; nombre[i] != '\0'; i++) {
            char letra[2] = { nombre[i], '\0' };
            int color = 9 + (i % 6); // alterna colores retro
            dibujarTexto(letra, xNombre + i*7*escalaNombre, yNombre, escalaNombre, color);
        }

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}


