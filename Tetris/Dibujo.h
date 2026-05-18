#ifndef DIBUJOS_H
#define DIBUJOS_H

#include "Constantes.h"
#include "GBT/gbt.h"
#include "Piezas.h"

// Función para dibujar el tablero completo
void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque);

// Función para dibujar el marco alrededor del tablero
void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,
                  int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho);

// Función para dibujar una matriz genérica en una posición de celda
void dibujarMatriz(int filas, int cols, int pieza[filas][cols],
                   int posCeldaX, int posCeldaY, int tamBloque, int color);

// Función para dibujar directamente una Pieza estructurada
void dibujarPiezaStruct(Pieza *p, int tamBloque);

#endif // DIBUJOS_H
