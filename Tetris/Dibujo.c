#include "Dibujo.h"
#include <unistd.h>
//mi funcion dibujar tablero recorre todas las posiciones de la matriz de 15 filas
//y 15 columnas y en todas al encontrarlas en cero no les dibuja nada y por lo tanto queda en negro
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int tipo = tablero[i][j];
            if (tipo != 0) {
                for (int y = 0; y < tamBloque; y++) {
                    for (int x = 0; x < tamBloque; x++) {
                        gbt_dibujar_pixel(j*tamBloque + x, i*tamBloque + y, tipo);
                    }
                }
            }
        }
    }
}
//pinta pixel a pixeli niciando desde posiciones distintas
//el grosor es el maximo que quier que pinte
void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,
                  int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho) {

    int ancho = columnas * tamBloque;
    int alto  = filas * tamBloque;

    // Borde superior
    for (int y = 0; y < grosor; y++) {
        for (int x = 0; x < ancho; x++) {
            gbt_dibujar_pixel(x, y, colorSuperior);
        }
    }

    // Borde inferior
    for (int y = alto - grosor; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            gbt_dibujar_pixel(x, y, colorInferior);
        }
    }

    // Borde izquierdo
    for (int x = 0; x < grosor; x++) {
        for (int y = 0; y < alto; y++) {
            gbt_dibujar_pixel(x, y, colorIzquierdo);
        }
    }

    // Borde derecho
    for (int x = ancho - grosor; x < ancho; x++) {
        for (int y = 0; y < alto; y++) {
            gbt_dibujar_pixel(x, y, colorDerecho);
        }
    }
}


void dibujarPieza(int filas, int cols, int pieza[filas][cols], int posX, int posY, int tamBloque, int color) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (pieza[i][j] == 1) {
                for (int y = 0; y < tamBloque; y++) {
                    for (int x = 0; x < tamBloque; x++) {
                        gbt_dibujar_pixel(posX + j*tamBloque + x, posY + i*tamBloque + y, color);
                    }
                }
            }
        }
    }
}
