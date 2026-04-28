#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"

#define FILAS 15
#define COLUMNAS 15
#define TAM_BLOQUE 20 //cada posicion es de 20 pixeles
#define GROSOR_MARCO 8
#define TAM_BLOQUE_P 10 //cada pieza usa 10 pixeles por posicion

// Paleta de colores
tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00}, // 0: Negro
    {0x00, 0x00, 0xAA}, // 1: Azul
    {0x00, 0xAA, 0x00}, // 2: Verde
    {0x00, 0xAA, 0xAA}, // 3: Cian
    {0xAA, 0x00, 0x00}, // 4: Rojo
    {0xAA, 0x00, 0xAA}, // 5: Magenta
    {0xAA, 0x55, 0x00}, // 6: Marrón
    {0xAA, 0xAA, 0xAA}, // 7: Gris claro
    {0x55, 0x55, 0x55}, // 8: Gris oscuro
    {0x55, 0x55, 0xFF}, // 9: Azul brillante
    {0x55, 0xFF, 0x55}, // 10: Verde brillante
    {0x55, 0xFF, 0xFF}, // 11: Cian brillante
    {0xFF, 0x55, 0x55}, // 12: Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13: Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14: Amarillo
    {0xFF, 0xFF, 0xFF}  // 15: Blanco (transparente en GBT)
};


int tablero[FILAS][COLUMNAS] = {0};

int main() {
    if (gbt_iniciar() < 0) return -1;

    gbt_crear_ventana("Tetris Tablero", COLUMNAS*TAM_BLOQUE, FILAS*TAM_BLOQUE, 2);

    // inicia la paleta de colores que voy a usar
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);

    // Posición inicial de la pieza O
    int posX = COLUMNAS/2 * TAM_BLOQUE;
    int posY = 8;

    while (1) {
        gbt_borrar_backbuffer(0);

        // Dibujar tablero lógico
        dibujarTablero(FILAS, COLUMNAS, tablero, TAM_BLOQUE);

        // Dibujar marco alrededor
        dibujarMarco(FILAS, COLUMNAS, TAM_BLOQUE, GROSOR_MARCO,9,12,14, 11);



        dibujarPieza(3, 3, piezaL, posX, posY, TAM_BLOQUE_P, 4);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}


