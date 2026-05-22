#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>   // para strlen en Game Over y centrar textos
#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"
#include "Constantes.h"
#include "FuenteLetras.h"   // ya unificado

int score = 0;
char nombreJugador[20];   // definición real

tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00}, {0x00, 0x00, 0xAA}, {0x00, 0xAA, 0x00}, {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00}, {0xAA, 0x00, 0xAA}, {0xAA, 0x55, 0x00}, {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55}, {0x55, 0x55, 0xFF}, {0x55, 0xFF, 0x55}, {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55}, {0xFF, 0x55, 0xFF}, {0xFF, 0xFF, 0x55}, {0xFF, 0xFF, 0xFF}
};

int tablero[FILAS][COLUMNAS];

int main()
{
    srand(time(NULL));

    if (gbt_iniciar() < 0) return -1;

    gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, 1);
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);

    // Pantalla de presentación
    pantallaPresentacion();

    // Menú inicial
    int opcion = menuInicial();
    if (opcion == 3) { // SALIR
        gbt_destruir_ventana();
        gbt_cerrar();
        return 0;
    }
    ingresarNombre(nombreJugador, 20);

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
        if (gbt_tecla_presionada(GBTK_IZQUIERDA)) {
            if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                piezaActual.posX--;
        } else if (gbt_tecla_sostenida(GBTK_IZQUIERDA)) {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
                if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                    piezaActual.posX--;
        }

        // Movimiento derecha
        if (gbt_tecla_presionada(GBTK_DERECHA)) {
            if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                piezaActual.posX++;
        } else if (gbt_tecla_sostenida(GBTK_DERECHA)) {
            if (gbt_temporizador_consumir(temporizador_mov_bloques))
                if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                    piezaActual.posX++;
        }

        // Movimiento abajo
        if (gbt_tecla_presionada(GBTK_ABAJO)) {
            if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                piezaActual.posY++;
            else {
                fijarPieza(&piezaActual, tablero);
                int lineas = limpiarLineas(tablero);
                score += calcularPuntaje(lineas);

                piezaActual = piezaSiguiente;
                nuevaPieza(&piezaSiguiente);

                if (GameOver(&piezaActual, tablero)) gameOver = 1;
            }
        }

        if (gbt_tecla_sostenida(GBTK_ABAJO)) {
            if (gbt_temporizador_consumir(temporizador_mov_bloques)) {
                if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                    piezaActual.posY++;
                else {
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

        // Gravedad automática
        if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO)) {
            if (gbt_temporizador_consumir(temporizador_gravedad))
                piezaActual.posY++;
        } else {
            if (gbt_temporizador_consumir(temporizador_fijacion)) {
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

        // 🔧 Ajuste dinámico del ancho del panel según el nombre
        int anchoNombre = strlen(nombreJugador) * 6 * 3;
        int anchoPanel = PANEL_ANCHO;
        if (anchoNombre + 40 > anchoPanel) {
            anchoPanel = anchoNombre + 40;
        }

        dibujarMarcoPanel(PANEL_X - GROSOR_MARCO,PANEL_Y - GROSOR_MARCO,anchoPanel + GROSOR_MARCO * 2,PANEL_ALTO + GROSOR_MARCO * 2,GROSOR_MARCO,9, 12, 14, 11);

            // Score arriba del nombre
            char textoScore[16];
            sprintf(textoScore, "%d", score);
            dibujarTexto(textoScore, PANEL_X + 20, PANEL_Y + 60, 5, 14, 0, 0);


            // Nombre multicolor debajo del score
            dibujarTexto(nombreJugador, PANEL_X + 20, PANEL_Y + 100, 3, 11, 0, 1);


        // Próxima pieza
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

   // Pantalla de Game Over centrada y multicolor
    gbt_borrar_backbuffer(0);
    dibujarTexto("GAME OVER", 0, ALTO_VENTANA/2 - 40, 4, 12, 1, 1);
    gbt_volcar_backbuffer();
    gbt_esperar(3000);

    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
