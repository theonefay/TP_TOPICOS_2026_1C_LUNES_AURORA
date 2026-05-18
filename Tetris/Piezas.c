#include <stdlib.h>
#include <string.h>
#include "Piezas.h"
#include "Constantes.h"

#define N 3

int piezaI[3][3] = {
    {1,0,0},
    {1,0,0},
    {1,0,0}
};

int piezaJ[3][3] = {
    {1,0,0},
    {1,1,1},
    {0,0,0}
};

int piezaL[3][3] = {
    {0,0,1},
    {1,1,1},
    {0,0,0}
};

int piezaO[3][3] = {
    {1,1,0},
    {1,1,0},
    {0,0,0}
};

int piezaS[3][3] = {
    {0,1,1},
    {1,1,0},
    {0,0,0}
};

int piezaT[3][3] = {
    {1,1,1},
    {0,1,0},
    {0,0,0}
};

int piezaZ[3][3] = {
    {1,1,0},
    {0,1,1},
    {0,0,0}
};

static void copiarMatriz(int origen[3][3], int destino[3][3]) {
    memcpy(destino, origen, sizeof(int) * 3 * 3);
}

void nuevaPieza(Pieza *p) {
    int tipo = (rand() % 7) + 1;


    switch (tipo) {
        case PIEZA_I:
            copiarMatriz(piezaI, p->matriz);
            p->tipo = 'I';
            break;

        case PIEZA_J:
            copiarMatriz(piezaJ, p->matriz);
            p->tipo = 'J';
            break;

        case PIEZA_L:
            copiarMatriz(piezaL, p->matriz);
            p->tipo = 'L';
            break;

        case PIEZA_O:
            copiarMatriz(piezaO, p->matriz);
            p->tipo = 'O';
            break;

        case PIEZA_S:
            copiarMatriz(piezaS, p->matriz);
            p->tipo = 'S';
            break;

        case PIEZA_T:
            copiarMatriz(piezaT, p->matriz);
            p->tipo = 'T';
            break;

        case PIEZA_Z:
            copiarMatriz(piezaZ, p->matriz);
            p->tipo = 'Z';
            break;
    }

    p->posX = COLUMNAS / 2 - 1;
    p->posY = 0;
    p->color = 1 + rand() % 15;
}

int puedeMoverAbajo(Pieza *p, int tablero[FILAS][COLUMNAS], int grosorMarco) {
    (void)grosorMarco;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (p->matriz[i][j]) {
                int nuevaY = p->posY + i + 1;
                int nuevaX = p->posX + j;

                if (nuevaY >= FILAS) {
                    return 0;
                }

                if (nuevaX < 0 || nuevaX >= COLUMNAS) {
                    return 0;
                }

                if (tablero[nuevaY][nuevaX] != VACIO) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

void fijarPieza(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (p->matriz[i][j]) {
                int y = p->posY + i;
                int x = p->posX + j;

                if (y >= 0 && y < FILAS && x >= 0 && x < COLUMNAS) {
                    tablero[y][x] = p->color;
                }
            }
        }
    }
}

void rotarPieza(Pieza *p)
{
    if(p->tipo == 'O')
    {
        return;
    }

    int aux;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            aux = p->matriz[i][j];
            p->matriz[i][j] = p->matriz[j][i];
            p->matriz[j][i] = aux;
        }
    }

    for (int i = 0; i < N; i++)
    {
        aux = p->matriz[i][0];
        p->matriz[i][0] = p->matriz[i][N - 1];
        p->matriz[i][N - 1] = aux;
    }
}

