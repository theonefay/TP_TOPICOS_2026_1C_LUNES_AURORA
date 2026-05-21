#ifndef PIEZAS_H_INCLUDED
#define PIEZAS_H_INCLUDED

#include "Constantes.h"

// Enumeraci�n de tipos de piezas para llamarlas por n�mero
typedef enum {
    PIEZA_I = 1,
    PIEZA_J,
    PIEZA_L,
    PIEZA_O,
    PIEZA_S,
    PIEZA_T,
    PIEZA_Z
} TipoPieza;

// Enumeraci�n de colores CGA (0�15)
typedef enum {
    COLOR_NEGRO = 0,
    COLOR_AZUL,
    COLOR_VERDE,
    COLOR_CIAN,
    COLOR_ROJO,
    COLOR_MAGENTA,
    COLOR_MARRON,
    COLOR_GRIS_CLARO,
    COLOR_GRIS,
    COLOR_AZUL_CLARO,
    COLOR_VERDE_CLARO,
    COLOR_CIAN_CLARO,
    COLOR_ROJO_CLARO,
    COLOR_MAGENTA_CLARO,
    COLOR_AMARILLO,
    COLOR_BLANCO
} ColorCGA;

// Declaraci�n de las matrices de cada pieza
extern int piezaI[3][3];
extern int piezaJ[3][3];
extern int piezaL[3][3];
extern int piezaO[3][3];
extern int piezaS[3][3];
extern int piezaT[3][3];
extern int piezaZ[3][3];

// Estructura que representa la pieza activa en el tablero
typedef struct {
    int matriz[3][3];
    int posX;
    int posY;
    ColorCGA color;
    char tipo;
} Pieza;

// Prototipos de funciones
void rotarPieza(Pieza *p, int tablero[FILAS][COLUMNAS]);
void nuevaPieza(Pieza *p);
int puedeRotar(Pieza *p, int tablero[FILAS][COLUMNAS]);
int puedeMoverAbajo(Pieza *p, int tablero[FILAS][COLUMNAS], int grosorMarco);
int limpiarLineas(int tablero[FILAS][COLUMNAS]);
void fijarPieza(Pieza *p, int tablero[FILAS][COLUMNAS]);
int GameOver(Pieza *p, int tablero[FILAS][COLUMNAS]);
int puedeMoverHorizontal(Pieza *p, int tablero[FILAS][COLUMNAS], int direccion);
int calcularPuntaje(int lineas);

#endif // PIEZAS_H_INCLUDED
