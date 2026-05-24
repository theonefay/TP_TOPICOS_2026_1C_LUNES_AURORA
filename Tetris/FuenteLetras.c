#include "FuenteLetras.h"
#include "GBT/gbt.h"
#include <string.h>
#include "Constantes.h"

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

// Dibuja una letra en pantalla usando su matriz de píxeles
void dibujarLetra(int x, int y, int indice, int escala, int color)
{
    // Cada letra está guardada como una matriz 5x5
    for (int fila = 0; fila < 5; fila++) {
        for (int col = 0; col < 5; col++) {
            if (letras[indice][fila][col] == 1) {
                // Dibujar bloque escalado
                for (int dy = 0; dy < escala; dy++) {
                    for (int dx = 0; dx < escala; dx++) {
                        gbt_dibujar_pixel(x + col*escala + dx,
                                          y + fila*escala + dy,
                                          color);
                    }
                }
            }
        }
    }
}


// Convierte un carácter (A–Z o 0–9) en un índice para buscar su matriz
int letraIndice(char c)
{
    // Letras A–Z
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    if (c == 'D') return 3;
    if (c == 'E') return 4;
    if (c == 'F') return 5;
    if (c == 'G') return 6;
    if (c == 'H') return 7;
    if (c == 'I') return 8;
    if (c == 'J') return 9;
    if (c == 'K') return 10;
    if (c == 'L') return 11;
    if (c == 'M') return 12;
    if (c == 'N') return 13;
    if (c == 'O') return 14;
    if (c == 'P') return 15;
    if (c == 'Q') return 16;
    if (c == 'R') return 17;
    if (c == 'S') return 18;
    if (c == 'T') return 19;
    if (c == 'U') return 20;
    if (c == 'V') return 21;
    if (c == 'W') return 22;
    if (c == 'X') return 23;
    if (c == 'Y') return 24;
    if (c == 'Z') return 25;

    // Dígitos 0–9
    if (c == '0') return 26;
    if (c == '1') return 27;
    if (c == '2') return 28;
    if (c == '3') return 29;
    if (c == '4') return 30;
    if (c == '5') return 31;
    if (c == '6') return 32;
    if (c == '7') return 33;
    if (c == '8') return 34;
    if (c == '9') return 35;

    return -1; // carácter no válido
}
void dibujarTexto(const char* texto, int x, int y, int escala, int color, int centrado, int multicolor)
{
    int ancho = 0;

    // Calcular ancho total incluyendo espacios
    for (int i = 0; texto[i] != '\0'; i++) {
        int indice = letraIndice(texto[i]);
        if (texto[i] == ' ') {
            ancho += 4 * escala; // espacio más chico que una letra
        } else if (indice != -1) {
            if (indice < 26) ancho += 6 * escala;   // letras (5 columnas + 1 espacio)
            else ancho += 4 * escala;               // dígitos (3 columnas + 1 espacio)
        }
    }

    // Centrado automático
    if (centrado == 1) {
    x = anchoVentana/2 - ancho/2;
}


    int offsetX = 0;

    // Dibujar cada carácter
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ' ') {
            offsetX += 4 * escala; // avanzar sin dibujar
            continue;
        }

        int indice = letraIndice(texto[i]);
        if (indice != -1) {
            int colorLetra = (multicolor == 1) ? (9 + (i % 6)) : color;

            if (indice < 26) {
                // Letras 5x5
                for (int fila = 0; fila < 5; fila++) {
                    for (int col = 0; col < 5; col++) {
                        if (letras[indice][fila][col] == 1) {
                            for (int dy = 0; dy < escala; dy++) {
                                for (int dx = 0; dx < escala; dx++) {
                                    gbt_dibujar_pixel(x + offsetX + col*escala + dx,
                                                      y + fila*escala + dy,
                                                      colorLetra);
                                }
                            }
                        }
                    }
                }
                offsetX += 6 * escala;
            } else {
                // Dígitos 5x3
                int dig = indice - 26;
                for (int fila = 0; fila < 5; fila++) {
                    for (int col = 0; col < 3; col++) {
                        if (digitos[dig][fila][col] == 1) {
                            for (int dy = 0; dy < escala; dy++) {
                                for (int dx = 0; dx < escala; dx++) {
                                    gbt_dibujar_pixel(x + offsetX + col*escala + dx,
                                                      y + fila*escala + dy,
                                                      colorLetra);
                                }
                            }
                        }
                    }
                }
                offsetX += 4 * escala;
            }
        }
    }
}
