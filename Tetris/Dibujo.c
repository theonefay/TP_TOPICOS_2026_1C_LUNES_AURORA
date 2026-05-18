#include "Dibujo.h"
#include "Constantes.h"
#include "Piezas.h"

// Dibuja el tablero completo
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int valor = tablero[i][j];

            if (valor != VACIO) {
                for (int y = 0; y < tamBloque; y++) {
                    for (int x = 0; x < tamBloque; x++) {
                        gbt_dibujar_pixel(
                            TABLERO_X + j * tamBloque + x,
                            TABLERO_Y + i * tamBloque + y,
                            valor
                        );
                    }
                }
            }
        }
    }
}

void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,
                  int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho) {

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
                   int posCeldaX, int posCeldaY, int tamBloque, int color) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (pieza[i][j] == 1) {
                for (int y = 0; y < tamBloque; y++) {
                    for (int x = 0; x < tamBloque; x++) {
                        gbt_dibujar_pixel(
                            TABLERO_X + (posCeldaX + j) * tamBloque + x,
                            TABLERO_Y + (posCeldaY + i) * tamBloque + y,
                            color
                        );
                    }
                }
            }
        }
    }
}

// Dibuja directamente una Pieza estructurada
void dibujarPiezaStruct(Pieza *p, int tamBloque) {
    dibujarMatriz(3, 3, p->matriz, p->posX, p->posY, tamBloque, p->color);
}
