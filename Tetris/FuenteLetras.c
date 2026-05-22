#include "FuenteLetras.h"
#include "GBT/gbt.h"
#include "Fuente.h"

int letras[26][5][5] = {
    // A
    {{0,1,1,1,0},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}},
    // B
    {{1,1,1,0,0},{1,0,0,1,0},{1,1,1,0,0},{1,0,0,1,0},{1,1,1,0,0}},
    // C
    {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,0},{1,0,0,0,1},{0,1,1,1,0}},
    // D
    {{1,1,1,0,0},{1,0,0,1,0},{1,0,0,1,0},{1,0,0,1,0},{1,1,1,0,0}},
    // E
    {{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,1,1,1,1}},
    // F
    {{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,0,0,0,0}},
    // G
    {{1,1,1,1,1},{1,0,0,0,0},{1,0,1,1,1},{1,0,0,0,1},{1,1,1,1,1}},
    // H
    {{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}},
    // I
    {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1}},
    // J
    {{0,0,1,1,1},{0,0,0,0,1},{0,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
    // K
    {{1,0,0,0,1},{1,0,0,1,0},{1,1,1,0,0},{1,0,0,1,0},{1,0,0,0,1}},
    // L
    {{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}},
    // M
    {{1,0,0,0,1},{1,1,0,1,1},{1,0,1,0,1},{1,0,0,0,1},{1,0,0,0,1}},
    // N
    {{1,0,0,0,1},{1,1,0,0,1},{1,0,1,0,1},{1,0,0,1,1},{1,0,0,0,1}},
    // O
    {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
    // P
    {{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,0},{1,0,0,0,0}},
    // Q
    {{0,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,1,0,1},{0,1,1,1,1}},
    // R
    {{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,1,0,0},{1,0,0,1,0}},
    // S
    {{0,1,1,1,1},{1,0,0,0,0},{0,1,1,1,0},{0,0,0,0,1},{1,1,1,1,0}},
    // T
    {{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
    // U
    {{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,1,1,0}},
    // V
    {{1,0,0,0,1},{1,0,0,0,1},{0,1,0,1,0},{0,1,0,1,0},{0,0,1,0,0}},
    // W
    {{1,0,0,0,1},{1,0,0,0,1},{1,0,1,0,1},{1,1,0,1,1},{1,0,0,0,1}},
    // X
    {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1}},
    // Y
    {{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
    // Z
    {{1,1,1,1,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0},{1,1,1,1,1}}
};
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
int letraIndice(char c)
{
    // Convertir a mayúscula
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';

    // Mapear A–Z a índices 0–25
    if (c >= 'A' && c <= 'Z')
        return c - 'A';

    // Si no es letra, devolvemos -1 (espacio u otro símbolo)
    return -1;
}
void dibujarTexto(const char* texto, int x, int y, int escala, int color)
{
    int offset = 0;
    for (int i = 0; texto[i] != '\0'; i++)
    {
        char c = texto[i];

        // Espacio
        if (c == ' ')
        {
            offset += 6 * escala;
            continue;
        }

        // Números
        if (c >= '0' && c <= '9')
        {
            int numero = c - '0';
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
                                    x + offset + col * escala + dx,
                                    y + fila * escala + dy,
                                    color
                                );
                            }
                        }
                    }
                }
            }
            offset += 4 * escala; // ancho de dígito
            continue;
        }

        // Letras
        int indice = letraIndice(c);
        if (indice != -1)
        {
            dibujarLetra(x + offset, y, indice, escala, color);
            offset += 6 * escala; // ancho de letra
        }
    }
}

