#include "Piezas.h"
#include <stdlib.h>   // para rand()
#include <string.h>   // para memcpy()

// Definición de las matrices de cada pieza

// Pieza I
int piezaI[3][3] = {
    {1,1,1},
    {0,0,0},
    {0,0,0}
};

// Pieza J
int piezaJ[3][3] = {
    {1,0,0},
    {1,0,0},
    {1,1,0}
};

// Pieza L
int piezaL[3][3] = {
    {0,0,1},
    {0,0,1},
    {0,1,1}
};

// Pieza O (cuadrado)
int piezaO[3][3] = {
    {1,1,0},
    {1,1,0},
    {0,0,0}
};

// Pieza S
int piezaS[3][3] = {
    {0,1,1},
    {1,1,0},
    {0,0,0}
};

// Pieza T
int piezaT[3][3] = {
    {0,1,0},
    {1,1,1},
    {0,0,0}
};

// Pieza Z
int piezaZ[3][3] = {
    {1,1,0},
    {0,1,1},
    {0,0,0}
};

int ramdonColor(int color) {
    while(color == 0 || color == 15) {
        color = rand() % 16;
    }
    return color;
}

void nuevaPieza(Pieza *p)
//recibe el puntero(direccion) de la estructura pieza
 {
    int tipo = rand() % 7;//se elige aleatoriamente el tipo de pieza y se guarda en la variable tipo
    switch(tipo) {
        case PIEZA_I: memcpy(p->matriz, piezaI, sizeof(piezaI)); p->color = ramdonColor(rand() % 16); break;// hace que ese tipo se guarde en el campo matriz de la estructura ppieza
        case PIEZA_J: memcpy(p->matriz, piezaJ, sizeof(piezaJ)); p->color = ramdonColor(rand() % 16); break;
        case PIEZA_L: memcpy(p->matriz, piezaL, sizeof(piezaL)); p->color = ramdonColor(rand() % 16); break;
        case PIEZA_O: memcpy(p->matriz, piezaO, sizeof(piezaO)); p->color = ramdonColor(rand() % 16); break;
        case PIEZA_S: memcpy(p->matriz, piezaS, sizeof(piezaS)); p->color = ramdonColor(rand() % 16); break;
        case PIEZA_T: memcpy(p->matriz, piezaT, sizeof(piezaT)); p->color = ramdonColor(rand() % 16); break;
        case PIEZA_Z: memcpy(p->matriz, piezaZ, sizeof(piezaZ)); p->color = ramdonColor(rand() % 16); break;
    }
    p->posX = (COLUMNAS / 2) - 2;
    p->posY = 8;

}

