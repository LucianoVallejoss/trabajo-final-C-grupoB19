#include <stdio.h>
#include "artemis.h"

int main(void) {
    EstadoOrbital estado;

    printf("=== PRUEBA MODULO INTEGRANTE 1: FISICA ORBITAL LEO ===\n\n");

    // 1. Inicializar con los datos de la consigna (h = 192 km, m = 33000 kg)
    inicializar_estado_base(&estado);

    // 2. Mostrar resultados calculados
    printf("Parametros calculados para orbita LEO:\n");
    printf("- Altitud (h):            %.2f m (%.2f km)\n", estado.altitud_m, estado.altitud_m / 1000.0);
    printf("- Radio total (r):        %.2f m (%.2f km)\n", estado.radio_total_m, estado.radio_total_m / 1000.0);
    printf("- Rapidez orbital (v):    %.2f m/s (%.2f km/h)\n", estado.velocidad_orbital, estado.velocidad_orbital * 3.6);
    printf("- Periodo orbital (T):    %.2f s (%.2f min)\n", estado.periodo_segundos, estado.periodo_segundos / 60.0);
    printf("- Aceleracion centripeta: %.4f m/s^2\n\n", estado.aceleracion_centripeta);

    // 3. Imprimir el desarrollo algebraico formal
    imprimir_demostracion_teorica();

    return 0;
}