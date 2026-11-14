#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "validaciones.h"

#define BUFFER_SIZE 128

// Devuelve 1 si el texto esta vacio o contiene solo espacios
static int solo_espacios(const char *texto) {
    while (*texto != '\0') {
        if (!isspace((unsigned char)*texto)) {
            return 0;
        }
        texto++;
    }
    return 1;
}

static int es_texto_numerico(const char *texto) {
    while (*texto != '\0') {
        if (!isdigit((unsigned char)*texto) && !isspace((unsigned char)*texto) &&
            *texto != '+' && *texto != '-' && *texto != '.' &&
            *texto != 'e' && *texto != 'E') {
            return 0;
        }
        texto++;
    }
    return 1;
}

static char *leer_linea(const char *mensaje, char *buffer, int tam) {
    char *inicio;

    printf("%s", mensaje);

    if (fgets(buffer, tam, stdin) == NULL) {
        printf("\n[ERROR] Fin de la entrada. Cerrando el programa.\n");
        exit(EXIT_FAILURE);
    }

    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    inicio = buffer;
    while (isspace((unsigned char)*inicio)) {
        inicio++;
    }
    return inicio;
}

static char *leer_linea_no_vacia(const char *mensaje, char *buffer, int tam) {
    char *inicio;

    while (1) {
        inicio = leer_linea(mensaje, buffer, tam);
        if (*inicio != '\0') {
            return inicio;
        }
        printf("[ADVERTENCIA] Entrada vacia. Debe ingresar un valor.\n");
    }
}

int leer_entero_rango(const char *mensaje, int min, int max) {
    char buffer[BUFFER_SIZE];
    char *inicio;
    char *fin_ptr;
    long valor;

    while (1) {
        inicio = leer_linea_no_vacia(mensaje, buffer, BUFFER_SIZE);

        errno = 0;
        valor = strtol(inicio, &fin_ptr, 10);

        if (!solo_espacios(fin_ptr)) {
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
    char *inicio;
    char *fin_ptr;
    double valor;

    while (1) {
        inicio = leer_linea_no_vacia(mensaje, buffer, BUFFER_SIZE);

        errno = 0;
        valor = strtod(inicio, &fin_ptr);

        if (!es_texto_numerico(inicio) || !solo_espacios(fin_ptr)) {
            printf("[ADVERTENCIA] Formato invalido. Use punto decimal (ej. 192.5) y solo numeros.\n");
            continue;
        }

        if (errno == ERANGE || !isfinite(valor) || valor < min || valor > max) {
            printf("[ADVERTENCIA] Valor fuera de rango. Debe estar entre %.2f y %.2f.\n", min, max);
            continue;
        }

        return valor;
    }
}

char leer_opcion_caracter(const char *mensaje, char op1, char op2) {
    char buffer[BUFFER_SIZE];
    char c1 = (char)tolower((unsigned char)op1);
    char c2 = (char)tolower((unsigned char)op2);
    char *inicio;
    char elegida;

    while (1) {
        inicio = leer_linea(mensaje, buffer, BUFFER_SIZE);
        elegida = (char)tolower((unsigned char)*inicio);

        if (elegida != '\0' && solo_espacios(inicio + 1) &&
            (elegida == c1 || elegida == c2)) {
            return elegida;
        }

        printf("[ADVERTENCIA] Opcion invalida. Ingrese '%c' o '%c'.\n", op1, op2);
    }
}

void pausar_consola(void) {
    char buffer[BUFFER_SIZE];

    leer_linea("\nPresione ENTER para continuar...", buffer, BUFFER_SIZE);
}
