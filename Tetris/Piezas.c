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
    int tipo = (rand() % 7) + 1;// el tipo va a ser aleatorio


    switch (tipo) {
        case PIEZA_I:
            copiarMatriz(piezaI, p->matriz);//copia la plantilla del mino en el campo matriz de la pieza actual
            p->tipo = 'I';//indica de que tipo es en el campo tipo de la pieza actual
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

    p->posX = COLUMNAS / 2 - 1;// la pieza aparece en el centro
    p->posY = 0;// la pieza aparece arriba de todo del tablero
    p->color = 9 + rand() % 6;// se le asigna un color random
}


int puedeMoverHorizontal(Pieza *p, int tablero[FILAS][COLUMNAS], int direccion)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (p->matriz[i][j]==1)//solo acceden las posicion con un 1
            {
                int nuevaY = p->posY + i;//ubica el casillero en el tablero
                int nuevaX = p->posX + j + direccion;//ubica el casillero en el tablero + el movimiento

                if (nuevaX < 0 || nuevaX >= COLUMNAS)//verifica si no se choco con los bordes
                {
                    return 0;
                }

                if (nuevaY >= 0 && nuevaY < FILAS && tablero[nuevaY][nuevaX] != VACIO)//verifca que no choque con otra pieza
                {
                    return 0;
                }
            }
        }
    }

    return 1;
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
            if (p->matriz[i][j]==1) {
                int y = p->posY + i;
                int x = p->posX + j;

                if (y >= 0 && y < FILAS && x >= 0 && x < COLUMNAS) {
                    tablero[y][x] = p->color;//pone en donde habia un 1 el numero del color que se pintara
                }
            }
        }
    }
}

void rotarPieza(Pieza *p, int tablero[FILAS][COLUMNAS])
{
    if (p->tipo == 'O')
    {
        return;
    }

    int backup[3][3];

    memcpy(backup, p->matriz, sizeof(backup));

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

    if (!puedeRotar(p, tablero))
    {
        memcpy(p->matriz, backup, sizeof(backup));
    }
}


int puedeRotar(Pieza *p, int tablero[FILAS][COLUMNAS])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (p->matriz[i][j])
            {
                int x = p->posX + j;
                int y = p->posY + i;

                if (x < 0 || x >= COLUMNAS)
                {
                    return 0;
                }

                if (y < 0 || y >= FILAS)
                {
                    return 0;
                }

                if (tablero[y][x] != VACIO)
                {
                    return 0;
                }
            }
        }
    }

    return 1;
}






int limpiarLineas(int tablero[FILAS][COLUMNAS])
{
    int lineasEliminadas = 0;

    for (int i = FILAS - 1; i >= 0; i--)
    {
        int completa = 1;

        for (int j = 0; j < COLUMNAS; j++)
        {
            if (tablero[i][j] == VACIO)
            {
                completa = 0;
                break;
            }
        }

        if (completa)
        {
            lineasEliminadas++;

            // bajar filas
            for (int y = i; y > 0; y--)
            {
                for (int x = 0; x < COLUMNAS; x++)
                {
                    tablero[y][x] = tablero[y - 1][x];
                }
            }

            // vaciar fila superior
            for (int x = 0; x < COLUMNAS; x++)
            {
                tablero[0][x] = VACIO;
            }

            // volver a revisar la misma fila
            i++;
        }
    }

    return lineasEliminadas;
}
int GameOver(Pieza *p, int tablero[FILAS][COLUMNAS])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (p->matriz[i][j])
            {
                int y = p->posY + i;
                int x = p->posX + j;

                if (tablero[y][x] != VACIO)
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}
int calcularPuntaje(int lineas)
{
    switch (lineas)
    {
        case 1:
            return 100;

        case 2:
            return 300;

        case 3:
            return 500;

        case 4:
            return 800;

        default:
            return 0;
    }
}
