#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int leer_entero_rango(const char *mensaje, int min, int max);

double leer_double_rango(const char *mensaje, double min, double max);

char leer_opcion_caracter(const char *mensaje, char op1, char op2);

void pausar_consola(void);

#endif