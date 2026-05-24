#include <stdio.h>
#include "GBT/gbt.h"
#include "FuenteLetras.h"
#include "Configuraciones.h"
#include "Dibujo.h"

void guardarConfig(Config *c) {
    FILE *f = fopen("config.dat","wb");
    if (f) { fwrite(c,sizeof(Config),1,f); fclose(f); }
}

void cargarConfig(Config *c) {
    FILE *f = fopen("config.dat","rb");
    if (f) {
        fread(c,sizeof(Config),1,f);
        fclose(f);
    } else {
        // Valores por defecto
        c->paleta = 0;
        c->resolucion = 1;        // VGA por defecto
        c->velocidadCaida = 1.0;
    }
}


void menuConfiguracion(Config *c) {
    while (1) {
        gbt_borrar_backbuffer(0);

        // Título centrado
        dibujarTexto("CONFIGURACION", anchoVentana/2, 60, 4, 12, 1, 1);

        // Mostrar resolución actual centrada
        char textoRes[32];
        sprintf(textoRes, "Resolucion: %s",
            c->resolucion == 0 ? "CGA (320x200)" : "VGA (640x480)");
        dibujarTexto(textoRes, anchoVentana/2, 120, 3, 11, 1, 1);

        // Instrucciones centradas
        dibujarTexto("1 = Cambiar", anchoVentana/2, 180, 3, 14, 1, 1);
        dibujarTexto("ENTER = Guardar", anchoVentana/2, 220, 3, 14, 1, 1);
        dibujarTexto("ESC = Volver", anchoVentana/2, 260, 3, 14, 1, 1);

        gbt_volcar_backbuffer();
        gbt_procesar_entrada();

        // Cambiar resolución
        if (gbt_tecla_presionada(GBTK_1))
            c->resolucion = (c->resolucion + 1) % 2;

        // Guardar configuración
        if (gbt_tecla_presionada(GBTK_ENTER)) {
            guardarConfig(c);
            break;
        }

        // Volver sin guardar
        if (gbt_tecla_presionada(GBTK_ESCAPE)) break;

        gbt_esperar(16);
    }
}


// Estadísticas de jugadores
void guardarEstadistica(const char* nombre, int score) {
    Estadistica stats[10];
    int count = 0;

    FILE* f = fopen("estadisticas.dat", "rb");
    if (f) {
        count = fread(stats, sizeof(Estadistica), 10, f);
        fclose(f);
    }

    // Buscar si el jugador ya existe
    int encontrado = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(stats[i].nombre, nombre) == 0) {
            if (score > stats[i].maxScore)
                stats[i].maxScore = score;
            encontrado = 1;
            break;
        }
    }

    // Si no existe y hay espacio, agregarlo
    if (!encontrado && count < 10) {
        strcpy(stats[count].nombre, nombre);
        stats[count].maxScore = score;
        count++;
    }

    // Guardar todo de nuevo
    f = fopen("estadisticas.dat", "wb");
    fwrite(stats, sizeof(Estadistica), count, f);
    fclose(f);
}
void mostrarEstadisticas() {
    Estadistica stats[10];
    int count = 0;

    FILE* f = fopen("estadisticas.dat", "rb");
    if (f) {
        count = fread(stats, sizeof(Estadistica), 10, f);
        fclose(f);
    }

    int salir = 0;
    while (!salir) {
        gbt_borrar_backbuffer(0);

        // Título centrado y multicolor
        dibujarTexto("ESTADISTICAS", anchoVentana/2, 40, 5, 14, 1, 1);

        // Mostrar hasta 5 jugadores en amarillo, centrados
        for (int i = 0; i < count && i < 5; i++) {
            char linea[64];
            sprintf(linea, "%s - %d", stats[i].nombre, stats[i].maxScore);

            dibujarTexto(linea, anchoVentana/2, 120 + i*60, 4, 14, 1, 0);
        }

        gbt_volcar_backbuffer();

        // Esperar entrada del usuario para salir
        gbt_procesar_entrada();
        if (gbt_tecla_presionada(GBTK_ENTER) || gbt_tecla_presionada(GBTK_ESCAPE)) {
            salir = 1;
        }

        gbt_esperar(16);
    }
}



