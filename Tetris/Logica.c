#include "GBT/gbt.h"
#include "Logica.h"



void manejarPausa() {
    if (gbt_tecla_presionada(GBTK_p)) {
        juegoPausado = !juegoPausado; // alterna entre pausado y corriendo
    }
}


#include <stdio.h>
#include <string.h>
#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Piezas.h"
#include "Constantes.h"
#include "FuenteLetras.h"
#include "Configuraciones.h"

extern int score;
extern char nombreJugador[MAX_NOMBRE+1];
extern Config cfg;
extern int juegoPausado;
extern int tablero[FILAS][COLUMNAS];

void jugar() {
    // Inicializar tablero
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = VACIO;

    score = 0;
    juegoPausado = 0;

    // Piezas
    Pieza piezaActual;
    Pieza piezaSiguiente;
    nuevaPieza(&piezaActual);
    nuevaPieza(&piezaSiguiente);

    // Temporizadores
    tGBT_Temporizador* temporizador_gravedad = gbt_temporizador_crear(1.0);
    tGBT_Temporizador* temporizador_mov_bloques = gbt_temporizador_crear(0.2);
    tGBT_Temporizador* temporizador_fijacion = gbt_temporizador_crear(0.5);

    // Velocidad dinámica
    double velocidadCaida = 1000.0; // ms iniciales
    int piezasCaidas = 0;

    int gameOver = 0;

    while (!gameOver) {
        gbt_procesar_entrada();

        // Toggle de pausa con tecla P
        if (gbt_tecla_presionada(GBTK_p)) {
            juegoPausado = !juegoPausado;
        }

        if (!juegoPausado) {
            // --- Movimiento izquierda ---
            if (gbt_tecla_presionada(GBTK_IZQUIERDA)) {
                if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                    piezaActual.posX--;
            } else if (gbt_tecla_sostenida(GBTK_IZQUIERDA)) {
                if (gbt_temporizador_consumir(temporizador_mov_bloques))
                    if (puedeMoverHorizontal(&piezaActual, tablero, -1))
                        piezaActual.posX--;
            }

            // --- Movimiento derecha ---
            if (gbt_tecla_presionada(GBTK_DERECHA)) {
                if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                    piezaActual.posX++;
            } else if (gbt_tecla_sostenida(GBTK_DERECHA)) {
                if (gbt_temporizador_consumir(temporizador_mov_bloques))
                    if (puedeMoverHorizontal(&piezaActual, tablero, 1))
                        piezaActual.posX++;
            }

            // --- Movimiento abajo ---
            if (gbt_tecla_presionada(GBTK_ABAJO)) {
                if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO))
                    piezaActual.posY++;
                else {
                    fijarPieza(&piezaActual, tablero);
                    int lineas = limpiarLineas(tablero);
                    score += calcularPuntaje(lineas, velocidadCaida);

                    piezaActual = piezaSiguiente;
                    nuevaPieza(&piezaSiguiente);

                    // Velocidad dinámica
                    piezasCaidas++;
                    if (piezasCaidas % 10 == 0) velocidadCaida *= 0.97;

                    gbt_temporizador_destruir(temporizador_gravedad);
gbt_temporizador_destruir(temporizador_fijacion);

temporizador_gravedad = gbt_temporizador_crear(velocidadCaida / 1000.0);
temporizador_fijacion = gbt_temporizador_crear((velocidadCaida / 1000.0) * 0.5);


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
                        score += calcularPuntaje(lineas, velocidadCaida);

                        piezaActual = piezaSiguiente;
                        nuevaPieza(&piezaSiguiente);

                        // Velocidad dinámica
                        piezasCaidas++;
                        if (piezasCaidas % 10 == 0) velocidadCaida *= 0.97;
                        gbt_temporizador_destruir(temporizador_gravedad);
gbt_temporizador_destruir(temporizador_fijacion);

temporizador_gravedad = gbt_temporizador_crear(velocidadCaida / 1000.0);
temporizador_fijacion = gbt_temporizador_crear((velocidadCaida / 1000.0) * 0.5);


                        if (GameOver(&piezaActual, tablero)) gameOver = 1;
                    }
                }
            }

            // --- Rotación ---
            if (gbt_tecla_presionada(GBTK_ARRIBA))
                rotarPieza(&piezaActual, tablero);
            if (gbt_tecla_presionada(GBTK_ESPACIO))
                rotarPiezaContraria(&piezaActual, tablero);

            // --- Gravedad automática ---
            if (puedeMoverAbajo(&piezaActual, tablero, GROSOR_MARCO)) {
                if (gbt_temporizador_consumir(temporizador_gravedad))
                    piezaActual.posY++;
            } else {
                if (gbt_temporizador_consumir(temporizador_fijacion)) {
                    fijarPieza(&piezaActual, tablero);
                    int lineas = limpiarLineas(tablero);
                    score += calcularPuntaje(lineas, velocidadCaida);

                    piezaActual = piezaSiguiente;
                    nuevaPieza(&piezaSiguiente);

                    // Velocidad dinámica
                    piezasCaidas++;
                    if (piezasCaidas % 10 == 0) velocidadCaida *= 0.97;
                    gbt_temporizador_destruir(temporizador_gravedad);
gbt_temporizador_destruir(temporizador_fijacion);

temporizador_gravedad = gbt_temporizador_crear(velocidadCaida / 1000.0);
temporizador_fijacion = gbt_temporizador_crear((velocidadCaida / 1000.0) * 0.5);


                    if (GameOver(&piezaActual, tablero)) gameOver = 1;
                }
            }

            // --- Dibujado ---
            gbt_borrar_backbuffer(0);

            dibujarMarco(FILAS, COLUMNAS, TAM_BLOQUE, GROSOR_MARCO, 9, 12, 14, 11);

            dibujarMarcoPanel(
                PANEL_X - GROSOR_MARCO,
                PANEL_Y - GROSOR_MARCO,
                PANEL_ANCHO + GROSOR_MARCO * 2,
                PANEL_ALTO + GROSOR_MARCO * 2,
                GROSOR_MARCO,
                9, 12, 14, 11
            );

            // Score
            char textoScore[16];
            sprintf(textoScore, "%d", score);
            int escalaScore = 5;
            int anchoScore = strlen(textoScore) * (6 * escalaScore);
            int xScore = PANEL_X + (PANEL_ANCHO - anchoScore) / 2;
            dibujarTexto(textoScore, xScore, PANEL_Y + 60, escalaScore, 14, 0, 0);

            // Nombre
            int escalaNombre = 4;
            int anchoNombre = strlen(nombreJugador) * (6 * escalaNombre);
            while (anchoNombre > PANEL_ANCHO - 40 && escalaNombre > 2) {
                escalaNombre--;
                anchoNombre = strlen(nombreJugador) * (6 * escalaNombre);
            }
            int xNombre = PANEL_X + (PANEL_ANCHO - anchoNombre) / 2;
            dibujarTexto(nombreJugador, xNombre, PANEL_Y + 100, escalaNombre, 11, 0, 1);

            // Próxima pieza
            dibujarMatriz(
                3, 3,
                piezaSiguiente.matriz,
                (PANEL_X + 50 - TABLERO_X) / TAM_BLOQUE,
                (PANEL_Y + 120 - TABLERO_Y + 2 * TAM_BLOQUE) / TAM_BLOQUE,
                TAM_BLOQUE,
                piezaSiguiente.color
            );


// --- Velocidad de caída ---
// --- Velocidad de caída al lado derecho del tablero ---
char textoVel[32];
sprintf(textoVel, "Vel: %d ms", (int)velocidadCaida);

int escalaVel = 3;
int anchoVel = strlen(textoVel) * (6 * escalaVel);

// Posición: justo a la derecha del tablero
int xVel = TABLERO_X + COLUMNAS * TAM_BLOQUE + 20; // 20 px de margen
int yVel = TABLERO_Y + 40; // un poco debajo del borde superior

dibujarTexto(textoVel, xVel, yVel, escalaVel, 13, 0, 0);

// --- Tablero y pieza actual ---
dibujarTablero(FILAS, COLUMNAS, tablero, TAM_BLOQUE);
dibujarPiezaStruct(&piezaActual, TAM_BLOQUE);

gbt_volcar_backbuffer();


            // Tablero y pieza actual
            dibujarTablero(FILAS, COLUMNAS, tablero, TAM_BLOQUE);
            dibujarPiezaStruct(&piezaActual, TAM_BLOQUE);

            gbt_volcar_backbuffer();
        } else {
            // --- Pausa ---
            gbt_borrar_backbuffer(0);
            dibujarTexto("PAUSA", 0, altoVentana/2 - 40, 4, 14, 1, 1);
            gbt_volcar_backbuffer();
        }

        gbt_esperar(16);
    }

    // Pantalla de Game Over
    gbt_borrar_backbuffer(0);
    gbt_borrar_backbuffer(0);

// Centrado vertical dinámico
int escalaGO = 6;
dibujarTexto("GAME OVER", 0, altoVentana/2 - (escalaGO * 8), escalaGO, 12, 1, 1);

gbt_volcar_backbuffer();
gbt_esperar(3000);

    gbt_volcar_backbuffer();
    gbt_esperar(3000);

    // Guardar estadística del jugador actual
    guardarEstadistica(nombreJugador, score);
}

int calcularPuntaje(int lineas, double velocidadCaida) {
    int base = 0;

    switch (lineas) {
        case 1: base = 40; break;
        case 2: base = 100; break;
        case 3: base = 300; break;
        case 4: base = 1200; break;
    }

    // Factor de bonificación: cuanto menor la velocidad, mayor el puntaje
    // Ejemplo: velocidad inicial = 1000 ms → factor = 1.0
    // Si baja a 970 ms → factor ≈ 1.03
    double factor = 1000.0 / velocidadCaida;

    return (int)(base * factor);
}

