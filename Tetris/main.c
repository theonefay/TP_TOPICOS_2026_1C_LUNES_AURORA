#include <stdio.h>
#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"
#include "Constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int score = 0;
tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00}, {0x00, 0x00, 0xAA}, {0x00, 0xAA, 0x00}, {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00}, {0xAA, 0x00, 0xAA}, {0xAA, 0x55, 0x00}, {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55}, {0x55, 0x55, 0xFF}, {0x55, 0xFF, 0x55}, {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55}, {0xFF, 0x55, 0xFF}, {0xFF, 0xFF, 0x55}, {0xFF, 0xFF, 0xFF}
};

int tablero[FILAS][COLUMNAS];



int main()
{
    srand(time(NULL));// cambia la secuencia de random en cada partida

    if (gbt_iniciar() < 0)
    {
        return -1;
    }

    gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, 1);

    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);

    // Inicializar tablero en vacio
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            tablero[i][j] = VACIO;
        }
    }

    Pieza piezaActual; //creo mi pieza actual
    nuevaPieza(&piezaActual);//llamo a la funcion de nueva pieza y le envio la direccion de la que cree en main


   //creacion de temporizadores
    tGBT_Temporizador* temporizador_gravedad =gbt_temporizador_crear(1.0);

    tGBT_Temporizador* temporizador_mov_bloques =gbt_temporizador_crear(0.2);

    tGBT_Temporizador* temporizador_fijacion =gbt_temporizador_crear(0.5);


    while (1)//bucle principal del juego
    {
        gbt_procesar_entrada();

        // Movimiento izquierda
        if (gbt_tecla_presionada(GBTK_IZQUIERDA))
        {
            if (puedeMoverHorizontal(&piezaActual, tablero, -1))
            {
                piezaActual.posX--;
            }
        }
        else if (gbt_tecla_sostenida(GBTK_IZQUIERDA))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
            {
                if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                {
                    piezaActual.posX--;
                }
            }
        }

        // Movimiento derecha
        if (gbt_tecla_presionada(GBTK_DERECHA))
        {
            if (puedeMoverHorizontal(&piezaActual, tablero, 1))
            {
                piezaActual.posX++;
            }
        }
        else if (gbt_tecla_sostenida(GBTK_DERECHA))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))//si se consumio el tiempo se puede mover
            {
                if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                {
                    piezaActual.posX++;
                }
            }
        }

        // Movimiento hacia abajo
        if (gbt_tecla_presionada(GBTK_ABAJO))
        {
            if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
            {
                piezaActual.posY++;
            }
            else
            {
                fijarPieza(&piezaActual, tablero);

                limpiarLineas(tablero);

                nuevaPieza(&piezaActual);

                if (GameOver(&piezaActual, tablero))
                {
                    break;
                }
            }
        }


        if (gbt_tecla_sostenida(GBTK_ABAJO))
        {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
            {
                if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                {
                    piezaActual.posY++;
                }
                else
                {
                    fijarPieza(&piezaActual, tablero);

                    limpiarLineas(tablero);

                    nuevaPieza(&piezaActual);

                    if (GameOver(&piezaActual, tablero))
                    {
                        break;
                    }
                }
            }
        }

        // Rotaci�n
        if (gbt_tecla_presionada(GBTK_ARRIBA))
        {
            rotarPieza(&piezaActual, tablero);
        }

        // Gravedad
        if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
        {
            if (gbt_temporizador_consumir(temporizador_gravedad))
            {
                piezaActual.posY++;
            }
        }
        else
        {
            if (gbt_temporizador_consumir(temporizador_fijacion))
            {
                fijarPieza(&piezaActual, tablero);

                limpiarLineas(tablero);

                nuevaPieza(&piezaActual);

                //funcion dibujar panel

                if (GameOver(&piezaActual, tablero))
                {
                    break;
                }
            }
        }

        // que todo se dibuje en pantalla
        gbt_borrar_backbuffer(0);

        dibujarMarco(FILAS,COLUMNAS,TAM_BLOQUE,GROSOR_MARCO,9,12,14,11);

        dibujarTablero(FILAS,COLUMNAS,tablero,TAM_BLOQUE);

        dibujarPiezaStruct(&piezaActual,TAM_BLOQUE);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_destruir_ventana();

    gbt_cerrar();

    return 0;
}
