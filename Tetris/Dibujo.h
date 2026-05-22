#ifndef DIBUJOS_H
#define DIBUJOS_H

#include "Constantes.h"
#include "GBT/gbt.h"
#include "Piezas.h"

void dibujarTablero(int filas, int columnas, int tablero[filas][columnas], int tamBloque);
void dibujarMarco(int filas, int columnas, int tamBloque, int grosor,int colorSuperior, int colorInferior, int colorIzquierdo, int colorDerecho);
void dibujarMatriz(int filas, int cols, int pieza[filas][cols],int posCeldaX, int posCeldaY, int tamBloque, int color);
void dibujarPiezaStruct(Pieza *p, int tamBloque);
void dibujarMarcoPanel(int x,int y,int ancho,int alto,int grosor,int colorSuperior,int colorInferior,int colorIzquierdo,int colorDerecho);
void pantallaPresentacion();
int menuInicial();
void ingresarNombre(char* nombre, int maxLen);
#endif
