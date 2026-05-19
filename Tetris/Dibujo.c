#include "Dibujo.h"
#include "Constantes.h"
#include "Piezas.h"


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

// Dibuja una pieza desde matriz genérica
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


