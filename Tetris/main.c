//-------------------------------------------------------------------------------------------------------------------------------
/*
Apellido: Caire, Fabrizio Esteban
DNI: 43863061
Usuario: theonefay
Entrega: Sí

Apellido: Blanco, Rodrigo
DNI: 44109328
Usuario: BlancoRodrigo
Entrega: No

Apellido: ROCHA MALDONADO, WANDA
DNI: 39373348
Usuario: WandaRMaldo
Entrega: No
*/
//------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GBT/gbt.h"
#include "Dibujo.h"
#include "Constantes.h"
#include "FuenteLetras.h"
#include "Configuraciones.h"
#include "Logica.h"

//variables globales
int score = 0;
char nombreJugador[MAX_NOMBRE+1];
Config cfg;
int juegoPausado = 0;
int tablero[FILAS][COLUMNAS];
int altoVentana;
int anchoVentana;
int TAM_BLOQUE;
int TABLERO_X;
int TABLERO_Y;
int PANEL_X;
int PANEL_Y ;

//definicion de paleta de colores
tGBT_ColorRGB paletaCGA[16] = {
    {0x00, 0x00, 0x00}, {0x00, 0x00, 0xAA}, {0x00, 0xAA, 0x00}, {0x00, 0xAA, 0xAA},
    {0xAA, 0x00, 0x00}, {0xAA, 0x00, 0xAA}, {0xAA, 0x55, 0x00}, {0xAA, 0xAA, 0xAA},
    {0x55, 0x55, 0x55}, {0x55, 0x55, 0xFF}, {0x55, 0xFF, 0x55}, {0x55, 0xFF, 0xFF},
    {0xFF, 0x55, 0x55}, {0xFF, 0x55, 0xFF}, {0xFF, 0xFF, 0x55}, {0xFF, 0xFF, 0xFF}
};

int main(int argc, char* argv[]) {
    srand(time(NULL));

    if (gbt_iniciar() < 0) return -1;

    cargarConfig(&cfg);

    // Valores por defecto
    int resolucion = cfg.resolucion; // 0 = CGA, 1 = VGA
    int escala = 1;

    // Procesar argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "CGA") == 0) resolucion = 0;
        if (strcmp(argv[i], "VGA") == 0) resolucion = 1;
        if (strncmp(argv[i], "escala=", 7) == 0) escala = atoi(argv[i] + 7);
    }

    // Siempre abrir ventana en VGA (640x480)
    anchoVentana = 640;
    altoVentana  = 480;
    gbt_crear_ventana("Tetris", anchoVentana * escala, altoVentana * escala, 1);

    // Paleta de colores según modo elegido
    if (resolucion == 0) {
    // Simular CGA dentro de VGA
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);
    TAM_BLOQUE = 22;
    } else {
    // VGA
    gbt_aplicar_paleta(paletaCGA, 16, GBT_FORMATO_888);
    TAM_BLOQUE = 16;
}

    // Calcular posición dinámica del tablero
    TABLERO_X = (anchoVentana - COLUMNAS * TAM_BLOQUE) / 2;
    TABLERO_Y = (altoVentana - FILAS * TAM_BLOQUE) / 2;
    PANEL_X = 20;              // fijo
    PANEL_Y = TABLERO_Y;       // dinámico, depende del tablero


    pantallaPresentacion();

    while (1) {
        int opcion = menuInicial();

        if (opcion == 1) { // CONFIGURACION
            menuConfiguracion(&cfg);

        } else if (opcion == 0) { // JUGAR
            ingresarNombre(nombreJugador, MAX_NOMBRE);
            jugar();
            guardarEstadistica(nombreJugador, score);

        } else if (opcion == 2) { // ESTADISTICAS
            mostrarEstadisticas();

        } else if (opcion == 3) { // SALIR
            gbt_destruir_ventana();
            gbt_cerrar();
            return 0;
        }
    }
}
