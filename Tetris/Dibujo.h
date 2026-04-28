#ifndef DIBUJOS_H
#define DIBUJOS_H

#include "GBT/gbt.h"

// Función para dibujar el tablero completo
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque);

// Función para dibujar el marco alrededor del tablero
void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,
                  int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho);

// Función para dibujar una pieza en una posición
void dibujarPieza(int filas, int cols, int pieza[filas][cols], int posX, int posY, int tamBloque, int color);

#endif
