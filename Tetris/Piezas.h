#ifndef PIEZAS_H_INCLUDED
#define PIEZAS_H_INCLUDED
#define COLUMNAS 15
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

typedef struct {
    int matriz[3][3];
    int posX;
    int posY;
    int color;
} Pieza;

// Declaración de las matrices de cada pieza
extern int piezaI[3][3];
extern int piezaJ[3][3];
extern int piezaL[3][3];
extern int piezaO[3][3];
extern int piezaS[3][3];
extern int piezaT[3][3];
extern int piezaZ[3][3];
void nuevaPieza(Pieza *p);

#endif // PIEZAS_H_INCLUDED
