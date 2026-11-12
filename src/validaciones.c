#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "validaciones.h"

#define BUFFER_SIZE 128

static void limpiar_buffer_entrada(const char *buffer) {
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int leer_entero_rango(const char *mensaje, int min, int max) {
    char buffer[BUFFER_SIZE];
    char *fin_ptr;
    long valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("[ERROR] Error inesperado de lectura. Intente nuevamente.\n");
            continue;
        }

        limpiar_buffer_entrada(buffer);

        char *inicio = buffer;
        while (isspace((unsigned char)*inicio)) {
            inicio++;
        }

        if (*inicio == '\0') {
            printf("[ADVERTENCIA] Entrada vacia. Debe ingresar un numero entero.\n");
            continue;
        }

        errno = 0;
        valor = strtol(inicio, &fin_ptr, 10);

        while (isspace((unsigned char)*fin_ptr)) {
            fin_ptr++;
        }

        if (*fin_ptr != '\0') {
            printf("[ADVERTENCIA] Entrada invalida. Ingrese unicamente numeros enteros.\n");
            continue;
        }

        if (errno == ERANGE || valor < min || valor > max) {
            printf("[ADVERTENCIA] Valor fuera de rango. Debe estar entre %d y %d.\n", min, max);
            continue;
        }

        return (int)valor;
    }
}

double leer_double_rango(const char *mensaje, double min, double max) {
    char buffer[BUFFER_SIZE];
    char *fin_ptr;
    double valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("[ERROR] Error inesperado de lectura. Intente nuevamente.\n");
            continue;
        }

        limpiar_buffer_entrada(buffer);

        char *inicio = buffer;
        while (isspace((unsigned char)*inicio)) {
            inicio++;
        }

        if (*inicio == '\0') {
            printf("[ADVERTENCIA] Entrada vacia. Debe ingresar un valor numerico.\n");
            continue;
        }

        errno = 0;
        valor = strtod(inicio, &fin_ptr);

        while (isspace((unsigned char)*fin_ptr)) {
            fin_ptr++;
        }

        if (*fin_ptr != '\0') {
            printf("[ADVERTENCIA] Formato invalido. Use punto decimal (ej. 192.5) y solo numeros.\n");
            continue;
        }

        if (errno == ERANGE || valor < min || valor > max) {
            printf("[ADVERTENCIA] Valor fuera de rango. Debe estar entre %.2f y %.2f.\n", min, max);
            continue;
        }

        return valor;
    }
}

double leer_double_mayor_que(const char *mensaje, double limite_inferior) {
    char buffer[BUFFER_SIZE];
    char *fin_ptr;
    double valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("[ERROR] Error inesperado de lectura. Intente nuevamente.\n");
            continue;
        }

        limpiar_buffer_entrada(buffer);

        char *inicio = buffer;
        while (isspace((unsigned char)*inicio)) {
            inicio++;
        }

        if (*inicio == '\0') {
            printf("[ADVERTENCIA] Entrada vacia. Debe ingresar un valor numerico.\n");
            continue;
        }

        errno = 0;
        valor = strtod(inicio, &fin_ptr);

        while (isspace((unsigned char)*fin_ptr)) {
            fin_ptr++;
        }

        if (*fin_ptr != '\0') {
            printf("[ADVERTENCIA] Formato invalido. Ingrese solo valores numericos.\n");
            continue;
        }

        if (errno == ERANGE || valor <= limite_inferior) {
            printf("[ADVERTENCIA] El valor debe ser estrictamente mayor a %.2f.\n", limite_inferior);
            continue;
        }

        return valor;
    }
}

char leer_opcion_caracter(const char *mensaje, char op1, char op2) {
    char buffer[BUFFER_SIZE];
    char c1 = (char)tolower((unsigned char)op1);
    char c2 = (char)tolower((unsigned char)op2);

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("[ERROR] Error inesperado de lectura.\n");
            continue;
        }

        limpiar_buffer_entrada(buffer);

        char *inicio = buffer;
        while (isspace((unsigned char)*inicio)) {
            inicio++;
        }

        char elegida = (char)tolower((unsigned char)*inicio);

        if (elegida != '\0') {
            char *resto = inicio + 1;
            while (isspace((unsigned char)*resto)) {
                resto++;
            }
            if (*resto == '\0' && (elegida == c1 || elegida == c2)) {
                return elegida;
            }
        }

        printf("[ADVERTENCIA] Opcion invalida. Ingrese '%c' o '%c'.\n", op1, op2);
    }
}

void pausar_consola(void) {
    char buffer[BUFFER_SIZE];
    printf("\nPresione ENTER para continuar...");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        limpiar_buffer_entrada(buffer);
    }
}