#include "FuenteLetras.h"
#include "GBT/gbt.h"

int letras[][5][5] = {
    // G
    {
        {1,1,1,1,1},
        {1,0,0,0,0},
        {1,0,1,1,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    },
    // A
    {
        {0,1,1,1,0},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1}
    },
    // M
    {
        {1,0,0,0,1},
        {1,1,0,1,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1}
    },
    // E
    {
        {1,1,1,1,1},
        {1,0,0,0,0},
        {1,1,1,1,0},
        {1,0,0,0,0},
        {1,1,1,1,1}
    },
    // O
    {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    },
    // V
    {
        {1,0,0,0,1},
        {1,0,0,0,1},
        {0,1,0,1,0},
        {0,1,0,1,0},
        {0,0,1,0,0}
    },
    // R
    {
        {1,1,1,1,0},
        {1,0,0,0,1},
        {1,1,1,1,0},
        {1,0,1,0,0},
        {1,0,0,1,0}
    }
};


void dibujarLetra(int x, int y, int indice, int escala, int color)
{
    for (int fila = 0; fila < 5; fila++)
    {
        for (int col = 0; col < 5; col++)
        {
            if (letras[indice][fila][col])
            {
                for (int dy = 0; dy < escala; dy++)
                {
                    for (int dx = 0; dx < escala; dx++)
                    {
                        gbt_dibujar_pixel(
                            x + col * escala + dx,
                            y + fila * escala + dy,
                            color
                        );
                    }
                }
            }
        }
    }
}

void dibujarTextoGameOver(int x, int y, int escala, int color)
{
    // GAME
    dibujarLetra(x, y, 0, escala, color); // G
    dibujarLetra(x + 6*escala, y, 1, escala, color); // A
    dibujarLetra(x + 12*escala, y, 2, escala, color); // M
    dibujarLetra(x + 18*escala, y, 3, escala, color); // E

    // OVER (segunda línea)
    dibujarLetra(x, y + 8*escala, 4, escala, color); // O
    dibujarLetra(x + 6*escala, y + 8*escala, 5, escala, color); // V
    dibujarLetra(x + 12*escala, y + 8*escala, 3, escala, color); // E
    dibujarLetra(x + 18*escala, y + 8*escala, 6, escala, color); // R
}
