#ifndef CONFIGURACIONES_H_INCLUDED
#define CONFIGURACIONES_H_INCLUDED
#include "Constantes.h"
#include <string.h>


typedef struct {
    int paleta;
    int resolucion;
    float velocidadCaida;
} Config;

// Estadísticas de jugadores
typedef struct {
    char nombre[MAX_NOMBRE+1];
    int maxScore;
} Estadistica;

void guardarConfig(Config *c);
void cargarConfig(Config *c);
void menuConfiguracion(Config *c);

// Estadísticas
void guardarEstadistica(const char* nombre, int score);
void mostrarEstadisticas();

#endif // CONFIGURACIONES_H_INCLUDED
