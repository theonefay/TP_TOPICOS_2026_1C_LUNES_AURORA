#include <stdio.h>
#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"
#include "Constantes.h"
#include <stdlib.h>
#include <time.h>
#include "Fuente.h"
#include "FuenteLetras.h"


int score = 0;

tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00},
    {0x00, 0x00, 0xAA},
    {0x00, 0xAA, 0x00},
    {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00},
    {0xAA, 0x00, 0xAA},
    {0xAA, 0x55, 0x00},
    {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55},
    {0x55, 0x55, 0xFF},
    {0x55, 0xFF, 0x55},
    {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55},
    {0xFF, 0x55, 0xFF},
    {0xFF, 0xFF, 0x55},
    {0xFF, 0xFF, 0xFF}
};

int tablero[FILAS][COLUMNAS];

int main()
{
    srand(time(NULL));

    if (gbt_iniciar() < 0) return -1;

    gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, 1);
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);

    // Inicializar tablero
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = VACIO;

    // Piezas
    Pieza piezaActual;
    Pieza piezaSiguiente;
    nuevaPieza(&piezaActual);
    nuevaPieza(&piezaSiguiente);

    // Temporizadores
    tGBT_Temporizador* temporizador_gravedad = gbt_temporizador_crear(1.0);
    tGBT_Temporizador* temporizador_mov_bloques = gbt_temporizador_crear(0.2);
    tGBT_Temporizador* temporizador_fijacion = gbt_temporizador_crear(0.5);

    int gameOver = 0;

    while (!gameOver)
    {
        gbt_procesar_entrada();

        // Movimiento izquierda
        if (gbt_tecla_presionada(GBTK_IZQUIERDA))
        {
            if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                piezaActual.posX--;
        }
        else if (gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
                if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                    piezaActual.posX--;
        }

        // Movimiento derecha
        if (gbt_tecla_presionada(GBTK_DERECHA))
        {
            if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                piezaActual.posX++;
        }
        else if (gbt_tecla_sostenida(GBTK_DERECHA))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
                if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                    piezaActual.posX++;
        }

        // Movimiento abajo
        if (gbt_tecla_presionada(GBTK_ABAJO))
        {
            if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                piezaActual.posY++;
            else
            {
                fijarPieza(&piezaActual, tablero);
                int lineas = limpiarLineas(tablero);
                score += calcularPuntaje(lineas);

                piezaActual = piezaSiguiente;
                nuevaPieza(&piezaSiguiente);

                if (GameOver(&piezaActual, tablero)) gameOver = 1;
            }
        }

        if (gbt_tecla_sostenida(GBTK_ABAJO))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
            {
                if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                    piezaActual.posY++;
                else
                {
                    fijarPieza(&piezaActual, tablero);
                    int lineas = limpiarLineas(tablero);
                    score += calcularPuntaje(lineas);

                    piezaActual = piezaSiguiente;
                    nuevaPieza(&piezaSiguiente);

                    if (GameOver(&piezaActual, tablero)) gameOver = 1;
                }
            }
        }

        // Rotación
        if (gbt_tecla_presionada(GBTK_ARRIBA))
            rotarPieza(&piezaActual, tablero);

        // Gravedad
        if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
        {
            if (gbt_temporizador_consumir(temporizador_gravedad))
                piezaActual.posY++;
        }
        else
        {
            if (gbt_temporizador_consumir(temporizador_fijacion))
            {
                fijarPieza(&piezaActual, tablero);
                int lineas = limpiarLineas(tablero);
                score += calcularPuntaje(lineas);

                piezaActual = piezaSiguiente;
                nuevaPieza(&piezaSiguiente);

                if (GameOver(&piezaActual, tablero)) gameOver = 1;
            }
        }

        // Dibujado
        gbt_borrar_backbuffer(0);

        dibujarMarco(FILAS, COLUMNAS, TAM_BLOQUE, GROSOR_MARCO, 9, 12, 14, 11);
        dibujarPanel(PANEL_X, PANEL_Y, PANEL_ANCHO, PANEL_ALTO, 0);
        dibujarMarcoPanel(
            PANEL_X - GROSOR_MARCO,
            PANEL_Y - GROSOR_MARCO,
            PANEL_ANCHO + GROSOR_MARCO * 2,
            PANEL_ALTO + GROSOR_MARCO * 2,
            GROSOR_MARCO,
            9, 12, 14, 11
        );

        // Score
        dibujarNumero(PANEL_X + 20, PANEL_Y + 40, score, 6, 14);

        // Próxima pieza (dos casilleros más abajo)
        dibujarMatriz(
            3, 3,
            piezaSiguiente.matriz,
            (PANEL_X + 50 - TABLERO_X) / TAM_BLOQUE,
            (PANEL_Y + 120 - TABLERO_Y + 2 * TAM_BLOQUE) / TAM_BLOQUE,
            TAM_BLOQUE,
            piezaSiguiente.color
        );

        // Tablero y pieza actual
        dibujarTablero(FILAS, COLUMNAS, tablero, TAM_BLOQUE);
        dibujarPiezaStruct(&piezaActual, TAM_BLOQUE);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }


// Pantalla de Game Over
gbt_borrar_backbuffer(0);


// Mostrar mensaje GAME OVER
dibujarTextoGameOver(ANCHO_VENTANA/2 - 60, ALTO_VENTANA/2 - 40, 4, 4);

gbt_volcar_backbuffer();
gbt_esperar(3000); // espera 3 segundos


    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
