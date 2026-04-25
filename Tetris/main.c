#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"

int main()
{
    // Inicializar la biblioteca
    if (gbt_iniciar() < 0) {
        printf("Error al iniciar: %s\n", gbt_obtener_log());
        return -1;
    }

    // Crear ventana l�gica 320x240, escala 2
    if (gbt_crear_ventana("Demo Basico", 320, 240, 2) < 0) {
        printf("Error al crear ventana: %s\n", gbt_obtener_log());
        return -1;
    }

    // Aplicar paleta VGA por defecto
    gbt_aplicar_paleta(NULL, 0, GBT_FORMATO_888);

    // Crear temporizador de 1 segundo
    tGBT_Temporizador* timer = gbt_temporizador_crear(1.0);

    // Loop principal
    while (1) {
        // Procesar entrada de teclado
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) {
            // Salir si se presiona ESC
            break;
        }

        if (gbt_tecla_sostenida(GBTK_DERECHA)) {
            printf("Flecha derecha sostenida\n");
        }

        if (gbt_tecla_soltada(GBTK_IZQUIERDA)) {
            printf("Soltaste la flecha izquierda\n");
        }

        if (gbt_temporizador_consumir(timer)) {
            printf("Paso 1 segundo\n");
        }

        // Dibujar algo simple
        gbt_borrar_backbuffer(0);          // limpiar pantalla
        gbt_dibujar_pixel(50, 50, 1);      // pixel rojo
        gbt_dibujar_pixel(60, 60, 2);      // pixel verde
        gbt_dibujar_pixel(70, 70, 3);      // pixel azul
        gbt_volcar_backbuffer();           // mostrar en ventana

        gbt_esperar(16); // ~60 FPS
    }

    // Liberar recursos
    gbt_temporizador_destruir(timer);
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
