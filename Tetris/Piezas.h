#ifndef PIEZAS_H_INCLUDED
#define PIEZAS_H_INCLUDED

// Enumeración de tipos de piezas
typedef enum {
    PIEZA_I = 1,
    PIEZA_J,
    PIEZA_L,
    PIEZA_O,
    PIEZA_S,
    PIEZA_T,
    PIEZA_Z
} TipoPieza;

// Declaración de las matrices de cada pieza
extern int piezaI[3][3];
extern int piezaJ[3][3];
extern int piezaL[3][3];
extern int piezaO[3][3];
extern int piezaS[3][3];
extern int piezaT[3][3];
extern int piezaZ[3][3];

#endif // PIEZAS_H_INCLUDED
