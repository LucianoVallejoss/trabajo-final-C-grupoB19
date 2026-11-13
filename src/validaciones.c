#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

int leer_entero_rango(const char *mensaje, int min, int max) {
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1) {
            printf("[ERROR]: Ingrese un numero entero valido.\n");
            // Limpiar buffer básico
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Limpiar salto de línea residual

        if (valor < min || valor > max) {
            printf("[ERROR]: El valor debe estar entre %d y %d.\n", min, max);
        } else {
            return valor;
        }
    }
}

double leer_double_rango(const char *mensaje, double min, double max) {
    double valor;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%lf", &valor) != 1) {
            printf("[ERROR]: Ingrese un valor numerico valido.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (valor < min || valor > max) {
            printf("[ERROR]: El valor debe estar entre %.2f y %.2f.\n", min, max);
        } else {
            return valor;
        }
    }
}

double leer_double_positivo(const char *mensaje) {
    double valor;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%lf", &valor) != 1) {
            printf("[ERROR]: Ingrese un valor numerico valido.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (valor <= 0.0) {
            printf("[ERROR]: El valor debe ser mayor a 0.\n");
        } else {
            return valor;
        }
    }
}
