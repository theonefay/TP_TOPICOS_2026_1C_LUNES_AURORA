#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"
#include "Constantes.h"

tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00}, {0x00, 0x00, 0xAA}, {0x00, 0xAA, 0x00}, {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00}, {0xAA, 0x00, 0xAA}, {0xAA, 0x55, 0x00}, {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55}, {0x55, 0x55, 0xFF}, {0x55, 0xFF, 0x55}, {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55}, {0xFF, 0x55, 0xFF}, {0xFF, 0xFF, 0x55}, {0xFF, 0xFF, 0xFF}
};

int tablero[FILAS][COLUMNAS];

static int puedeMoverHorizontal(Pieza *p, int tablero[FILAS][COLUMNAS], int direccion) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (p->matriz[i][j]) {
                int nuevaY = p->posY + i;
                int nuevaX = p->posX + j + direccion;

                if (nuevaX < 0 || nuevaX >= COLUMNAS) {
                    return 0;
                }

                if (nuevaY >= 0 && nuevaY < FILAS && tablero[nuevaY][nuevaX] != VACIO) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int main() {
    if (gbt_iniciar() < 0) {
        return -1;
    }

    gbt_crear_ventana("Tetris", ANCHO_VENTANA, ALTO_VENTANA, 2);
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = VACIO;
        }
    }

    Pieza piezaActual;
    nuevaPieza(&piezaActual);

    tGBT_Temporizador* temporizador_gravedad = gbt_temporizador_crear(1.0);
    tGBT_Temporizador* temporizador_mov_bloques = gbt_temporizador_crear(0.2);
    tGBT_Temporizador* temporizador_fijacion = gbt_temporizador_crear(0.5);

    while (1) {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_IZQUIERDA)) {
            if (puedeMoverHorizontal(&piezaActual, tablero, -1)) {
                piezaActual.posX--;
            }
        }
        else if (gbt_tecla_sostenida(GBTK_IZQUIERDA)) {
            if (gbt_temporizador_consumir(temporizador_mov_bloques)) {
                if (puedeMoverHorizontal(&piezaActual, tablero, -1)) {
                    piezaActual.posX--;
                }
            }
        }

        if (gbt_tecla_presionada(GBTK_DERECHA)) {
            if (puedeMoverHorizontal(&piezaActual, tablero, 1)) {
                piezaActual.posX++;
            }
        }
        else if (gbt_tecla_sostenida(GBTK_DERECHA)) {
            if (gbt_temporizador_consumir(temporizador_mov_bloques)) {
                if (puedeMoverHorizontal(&piezaActual, tablero, 1)) {
                    piezaActual.posX++;
                }
            }
        }

        if (gbt_tecla_presionada(GBTK_ABAJO)) {
            if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO)) {
                piezaActual.posY++;
            }
            else {
                fijarPieza(&piezaActual, tablero);
                nuevaPieza(&piezaActual);
            }
        }

        if (gbt_tecla_sostenida(GBTK_ABAJO)) {
            if(gbt_temporizador_consumir(temporizador_mov_bloques)){
                if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO)) {
                    piezaActual.posY++;
                }
                else {
                fijarPieza(&piezaActual, tablero);
                nuevaPieza(&piezaActual);
                }

            }
        }

        if(gbt_tecla_presionada(GBTK_ARRIBA))
        {
                rotarPieza(&piezaActual);
        }


         if(puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO)) {
            if (gbt_temporizador_consumir(temporizador_gravedad)) {
                piezaActual.posY++;
            }
        }
        else {
            if (gbt_temporizador_consumir(temporizador_fijacion)) {
                fijarPieza(&piezaActual, tablero);
                nuevaPieza(&piezaActual);
            }
        }

        gbt_borrar_backbuffer(0);

        dibujarMarco(FILAS, COLUMNAS, TAM_BLOQUE, GROSOR_MARCO, 9, 12, 14, 11);
        dibujarTablero(FILAS, COLUMNAS, tablero, TAM_BLOQUE);
        dibujarPiezaStruct(&piezaActual, TAM_BLOQUE);

        for (int y = PANEL_Y; y < PANEL_Y + 300; y++) {
            gbt_dibujar_pixel(PANEL_X, y, 15);
        }

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
