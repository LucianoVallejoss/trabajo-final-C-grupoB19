#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#define TAM_LINEA 128

// Funciones preliminares para que el main compile y funcione.
// El Integrante 3 luego puede refinar estas funciones con su lógica avanzada.
int leer_entero_rango(const char *mensaje, int min, int max);
double leer_double_rango(const char *mensaje, double min, double max);
double leer_double_positivo(const char *mensaje);

#endif
