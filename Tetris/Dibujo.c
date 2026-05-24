#include "Dibujo.h"
#include "Constantes.h"
#include "Piezas.h"
#include "FuenteLetras.h"
#include <string.h>


// Dibuja un bloque cuadrado con borde claro/oscuro
void dibujarBloque(int xPantalla, int yPantalla, int tam, int color)
{
    int grosor = 2;        // grosor del borde
    int color_sup = 8;     // color para borde superior/izquierdo
    int color_inf = 7;     // color para borde inferior/derecho

    // Centro del bloque (relleno)
    for (int y = grosor; y < tam - grosor; y++) {
        for (int x = grosor; x < tam - grosor; x++) {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color);
        }
    }

    // Borde superior
    for (int y = 0; y < grosor; y++) {
        for (int x = 0; x < tam; x++) {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color_sup);
        }
    }

    // Borde izquierdo
    for (int x = 0; x < grosor; x++) {
        for (int y = 0; y < tam; y++) {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + y, color_sup);
        }
    }

    // Borde inferior
    for (int y = 0; y < grosor; y++) {
        for (int x = 0; x < tam; x++) {
            gbt_dibujar_pixel(xPantalla + x, yPantalla + tam - 1 - y, color_inf);
        }
    }

    // Borde derecho
    for (int x = 0; x < grosor; x++) {
        for (int y = 0; y < tam; y++) {
            gbt_dibujar_pixel(xPantalla + tam - 1 - x, yPantalla + y, color_inf);
        }
    }
}







// Dibuja todo el tablero con las piezas ya fijadas
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque)
{
    for (int fila = 0; fila < filas; fila++) {
        for (int col = 0; col < columnas; col++) {
            int valor = tablero[fila][col];

            // Si la celda no está vacía → dibujar bloque
            if (valor != VACIO) {
                dibujarBloque(TABLERO_X + col * tamBloque,TABLERO_Y + fila * tamBloque,tamBloque,valor);
            }
        }
    }
}



// Dibuja un marco alrededor del tablero
void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,
                  int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho)
{
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


void dibujarMarcoPanel(int x,int y,int ancho,int alto,int grosor,int colorSuperior,int colorInferior,int colorIzquierdo,int colorDerecho)
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

// Muestra la pantalla inicial con el título "TETRIS AURORA"
void pantallaPresentacion()
{
    gbt_borrar_backbuffer(0); // limpiar pantalla

    int escala = 7; // tamaño de las letras
    int yBase = altoVentana/2 - 60; // posición vertical

    // Dibujar título completo centrado y multicolor
    dibujarTexto("TETRIS AURORA", anchoVentana/2, yBase, escala, 12, 1, 1);


    gbt_volcar_backbuffer(); // mostrar en pantalla

    // Esperar hasta que el jugador presione ENTER
    while (!gbt_tecla_presionada(GBTK_ENTER)) {
        gbt_procesar_entrada();
        gbt_esperar(16);
    }
}




int menuInicial()
{
    int opcion = 0;

    while (1) {
        gbt_borrar_backbuffer(0);

        // Título centrado y multicolor (aprox. 1/4 de la altura)
        dibujarTexto("TETRIS", anchoVentana/2, altoVentana/4, 6, 12, 1, 1);

        // Opciones del menú
        int escalaOpc = 4;
        int salto = 60;
        int yBase = altoVentana/2; // centrado dinámico

        if (opcion == 0)
            dibujarTexto("JUGAR", anchoVentana/2, yBase, escalaOpc, 7, 1, 1);
        else
            dibujarTexto("JUGAR", anchoVentana/2, yBase, escalaOpc, 7, 1, 0);

        if (opcion == 1)
            dibujarTexto("CONFIGURACION", anchoVentana/2, yBase+salto, escalaOpc, 7, 1, 1);
        else
            dibujarTexto("CONFIGURACION", anchoVentana/2, yBase+salto, escalaOpc, 7, 1, 0);

        if (opcion == 2)
            dibujarTexto("ESTADISTICAS", anchoVentana/2, yBase+2*salto, escalaOpc, 7, 1, 1);
        else
            dibujarTexto("ESTADISTICAS", anchoVentana/2, yBase+2*salto, escalaOpc, 7, 1, 0);

        if (opcion == 3)
            dibujarTexto("SALIR", anchoVentana/2, yBase+3*salto, escalaOpc, 7, 1, 1);
        else
            dibujarTexto("SALIR", anchoVentana/2, yBase+3*salto, escalaOpc, 7, 1, 0);

        gbt_volcar_backbuffer();
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ARRIBA)) {
            opcion--; if (opcion < 0) opcion = 3;
        }
        if (gbt_tecla_presionada(GBTK_ABAJO)) {
            opcion++; if (opcion > 3) opcion = 0;
        }
        if (gbt_tecla_presionada(GBTK_ENTER)) return opcion;

        gbt_esperar(16);
    }
}








// Permite al jugador escribir su nombre con letras A–Z, espacio y retroceso
// El mensaje fijo y el nombre se muestran centrados y multicolor letra por letra
void ingresarNombre(char* nombre, int maxLen)
{
    int pos = 0;
    nombre[0] = '\0'; // empezar vacío

    while (1) {
        gbt_procesar_entrada();

        // Letras A–Z (cada una con un if básico)
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

        // Retroceso
        if (gbt_tecla_presionada(GBTK_RETROCESO) && pos > 0) {
            pos--;
            nombre[pos] = '\0';
        }

        // Confirmar con ENTER
        if (gbt_tecla_presionada(GBTK_ENTER)) {
            break;
        }

        // Dibujar pantalla
        gbt_borrar_backbuffer(0);

dibujarTexto("INGRESE SU NOMBRE", anchoVentana/2, altoVentana/3, 4, 12, 1, 1);
dibujarTexto(nombre, anchoVentana/2, altoVentana/2, 4, 11, 1, 1);


        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}
