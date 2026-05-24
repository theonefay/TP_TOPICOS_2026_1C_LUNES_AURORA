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



// Crea una nueva pieza aleatoria y la coloca en la parte superior del tablero
void nuevaPieza(Pieza *p) {
    // Elegir un tipo de pieza al azar (1 a 7)
    int tipo = (rand() % 7) + 1;

    // Copiar la matriz correspondiente y asignar el tipo
    switch (tipo) {
        case PIEZA_I: memcpy(p->matriz, piezaI, sizeof(p->matriz)); p->tipo = 'I'; break;
        case PIEZA_J: memcpy(p->matriz, piezaJ, sizeof(p->matriz)); p->tipo = 'J'; break;
        case PIEZA_L: memcpy(p->matriz, piezaL, sizeof(p->matriz)); p->tipo = 'L'; break;
        case PIEZA_O: memcpy(p->matriz, piezaO, sizeof(p->matriz)); p->tipo = 'O'; break;
        case PIEZA_S: memcpy(p->matriz, piezaS, sizeof(p->matriz)); p->tipo = 'S'; break;
        case PIEZA_T: memcpy(p->matriz, piezaT, sizeof(p->matriz)); p->tipo = 'T'; break;
        case PIEZA_Z: memcpy(p->matriz, piezaZ, sizeof(p->matriz)); p->tipo = 'Z'; break;
    }

    // Posición inicial: centro arriba del tablero
    p->posX = COLUMNAS / 2 - 1;
    p->posY = 0;

    // Color aleatorio (entre 9 y 14)
    p->color = 9 + rand() % 6;
}



// Verifica si la pieza puede moverse a izquierda (-1) o derecha (+1)
int puedeMoverHorizontal(Pieza *p, int tablero[FILAS][COLUMNAS], int direccion) {
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (p->matriz[fila][col] == 1) {
                int nuevaFila = p->posY + fila;
                int nuevaCol = p->posX + col + direccion;

                // Si se sale del tablero → no puede moverse
                if (nuevaCol < 0 || nuevaCol >= COLUMNAS) return 0;

                // Si choca con otra pieza → no puede moverse
                if (nuevaFila >= 0 && nuevaFila < FILAS && tablero[nuevaFila][nuevaCol] != VACIO) return 0;
            }
        }
    }
    return 1; // Movimiento válido
}






// Verifica si la pieza puede bajar una fila
int puedeMoverAbajo(Pieza *p, int tablero[FILAS][COLUMNAS], int grosorMarco) {
    (void)grosorMarco; // no se usa

    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (p->matriz[fila][col] == 1) {
                int nuevaFila = p->posY + fila + 1;
                int nuevaCol = p->posX + col;

                // Si toca el fondo → no puede bajar
                if (nuevaFila >= FILAS) return 0;

                // Si choca con otra pieza → no puede bajar
                if (tablero[nuevaFila][nuevaCol] != VACIO) return 0;
            }
        }
    }
    return 1; // Puede bajar
}


// Rota la pieza en sentido horario
void rotarPieza(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    if (p->tipo == 'O') return; // El cuadrado no rota

    int copia[3][3];
    memcpy(copia, p->matriz, sizeof(copia)); // Guardar copia

    // Transponer matriz
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int aux = p->matriz[i][j];
            p->matriz[i][j] = p->matriz[j][i];
            p->matriz[j][i] = aux;
        }
    }

    // Invertir columnas (rotación completa)
    for (int i = 0; i < 3; i++) {
        int aux = p->matriz[i][0];
        p->matriz[i][0] = p->matriz[i][2];
        p->matriz[i][2] = aux;
    }

    // Si no puede rotar, volver a la copia
    if (!puedeRotar(p, tablero)) memcpy(p->matriz, copia, sizeof(copia));
}


// Rota la pieza en sentido antihorario
void rotarPiezaContraria(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    if (p->tipo == 'O') return; // El cuadrado no rota

    int copia[3][3];
    memcpy(copia, p->matriz, sizeof(copia)); // Guardar copia

    // Transponer matriz
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            int aux = p->matriz[i][j];
            p->matriz[i][j] = p->matriz[j][i];
            p->matriz[j][i] = aux;
        }
    }

    // Invertir filas (rotación antihoraria)
    for (int j = 0; j < 3; j++) {
        int aux = p->matriz[0][j];
        p->matriz[0][j] = p->matriz[2][j];
        p->matriz[2][j] = aux;
    }

    // Si no puede rotar, volver a la copia
    if (!puedeRotar(p, tablero)) memcpy(p->matriz, copia, sizeof(copia));
}


// Copia la pieza al tablero (la fija en su lugar)
void fijarPieza(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (p->matriz[fila][col] == 1) {
                int y = p->posY + fila;
                int x = p->posX + col;

                // Si está dentro del tablero, guarda el color
                if (y >= 0 && y < FILAS && x >= 0 && x < COLUMNAS) {
                    tablero[y][x] = p->color;
                }
            }
        }
    }
}


// Verifica si la rotación  no choca ni se sale
int puedeRotar(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (p->matriz[fila][col] == 1) {
                int x = p->posX + col;
                int y = p->posY + fila;

                if (x < 0 || x >= COLUMNAS) return 0; // fuera de tablero
                if (y < 0 || y >= FILAS) return 0;    // fuera de tablero
                if (tablero[y][x] != VACIO) return 0; // celda ocupada
            }
        }
    }
    return 1;
}







// Elimina las filas completas y baja las superiores
int limpiarLineas(int tablero[FILAS][COLUMNAS]) {
    int lineasEliminadas = 0;

    for (int fila = FILAS - 1; fila >= 0; fila--) {
        int completa = 1;

        // Verificar si la fila está llena
        for (int col = 0; col < COLUMNAS; col++) {
            if (tablero[fila][col] == VACIO) {
                completa = 0;
                break;
            }
        }

        // Si está completa → eliminar
        if (completa) {
            lineasEliminadas++;

            // Bajar todas las filas superiores
            for (int y = fila; y > 0; y--) {
                for (int x = 0; x < COLUMNAS; x++) {
                    tablero[y][x] = tablero[y - 1][x];
                }
            }

            // Vaciar la fila superior
            for (int x = 0; x < COLUMNAS; x++) {
                tablero[0][x] = VACIO;
            }

            fila++; // Revisar la misma fila otra vez
        }
    }
    return lineasEliminadas;
}



// Verifica si la nueva pieza choca al aparecer
int GameOver(Pieza *p, int tablero[FILAS][COLUMNAS]) {
    for (int fila = 0; fila < 3; fila++) {
        for (int col = 0; col < 3; col++) {
            if (p->matriz[fila][col] == 1) {
                int y = p->posY + fila;
                int x = p->posX + col;

                if (tablero[y][x] != VACIO) return 1; // choque → game over
            }
        }
    }
    return 0; // sigue el juego
}

