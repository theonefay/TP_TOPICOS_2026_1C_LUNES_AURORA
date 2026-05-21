#include "Fuente.h"
#include "GBT/gbt.h"

int digitos[10][5][3] = {

    // 0
    {
        {1,1,1},
        {1,0,1},
        {1,0,1},
        {1,0,1},
        {1,1,1}
    },

    // 1
    {
        {0,1,0},
        {1,1,0},
        {0,1,0},
        {0,1,0},
        {1,1,1}
    },

    // 2
    {
        {1,1,1},
        {0,0,1},
        {1,1,1},
        {1,0,0},
        {1,1,1}
    },

    // 3
    {
        {1,1,1},
        {0,0,1},
        {0,1,1},
        {0,0,1},
        {1,1,1}
    },

    // 4
    {
        {1,0,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {0,0,1}
    },

    // 5
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {0,0,1},
        {1,1,1}
    },

    // 6
    {
        {1,1,1},
        {1,0,0},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    },

    // 7
    {
        {1,1,1},
        {0,0,1},
        {0,1,0},
        {1,0,0},
        {1,0,0}
    },

    // 8
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {1,0,1},
        {1,1,1}
    },

    // 9
    {
        {1,1,1},
        {1,0,1},
        {1,1,1},
        {0,0,1},
        {1,1,1}
    }
};

void dibujarDigito(int x, int y, int numero, int escala, int color)
{
    for (int fila = 0; fila < 5; fila++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (digitos[numero][fila][col])
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

void dibujarNumero(int x, int y, int valor, int escala, int color)
{
    if (valor == 0)
    {
        dibujarDigito(x, y, 0, escala, color);
        return;
    }

    int numeros[10];
    int cantidad = 0;

    while (valor > 0)
    {
        numeros[cantidad] = valor % 10;
        valor /= 10;
        cantidad++;
    }

    for (int i = cantidad - 1; i >= 0; i--)
    {
        dibujarDigito(
            x,
            y,
            numeros[i],
            escala,
            color
        );

        x += 4 * escala;
    }
}
