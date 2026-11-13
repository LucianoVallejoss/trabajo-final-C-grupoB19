#include <stdio.h>
#include <stdlib.h>
#include "artemis.h"
#include "validaciones.h"

int main(void) {
    EstadoOrbital estado;
    ManiobraLateral maniobra;
    RegistroMision historial[MAX_HISTORIAL];
    int cant_historial = 0;
    int hubo_maniobra_actual = 0;
    int opcion = 0;

    // Inicializar estado orbital nominal (h = 192 km, m = 33000 kg)
    inicializar_estado_base(&estado);

    // Inicializar maniobra lateral por defecto (a_y = 0.50 m/s^2, dt = 10 s)
    ejecutar_pulso_lateral(&maniobra, 0.50, 10.0);

    do {
        printf("\n=========================================================================\n");
        printf("       SIMULADOR ARTEMIS - ESCENARIO 2: ORBITA TERRESTRE BAJA (LEO)\n");
        printf("=========================================================================\n");
        printf(" 1. Ver demostracion analitica (La gravedad como fuerza centripeta)\n");
        printf(" 2. Modificar parametros orbitales (Altitud y Masa)\n");
        printf(" 3. Ver telemetria orbital detallada\n");
        printf(" 4. Simular pulso de propulsor auxiliar lateral\n");
        printf(" 5. Guardar simulacion actual en el historial (%d/%d)\n", cant_historial, MAX_HISTORIAL);
        printf(" 6. Emitir reporte final de auditoria del historial\n");
        printf(" 7. Salir\n");
        printf("=========================================================================\n");

        opcion = leer_entero_rango(" Seleccione una opcion (1-7): ", 1, 7);

        switch (opcion) {
            case 1:
                imprimir_demostracion_teorica();
                break;

            case 2: {
                printf("\n--- CONFIGURACION DE PARAMETROS ORBITALES ---\n");
                double nueva_alt = leer_double_rango(" Ingrese nueva altitud h [m] (ej. 192000): ", 100000.0, 2000000.0);
                double nueva_masa = leer_double_positivo(" Ingrese masa de la nave Orion [kg] (ej. 33000): ");

                estado.altitud_m = nueva_alt;
                estado.masa_nave_kg = nueva_masa;
                recalcular_dinamica_orbital(&estado);
                hubo_maniobra_actual = 0;

                printf("\n[OK]: Dinamica orbital recalculada correctamente.\n");
                if (!estado.es_orbita_estable) {
                    printf("[ADVERTENCIA]: Altitud inferior a 160 km. Riesgo de decaimiento atmosferico.\n");
                }
                break;
            }

            case 3:
                mostrar_telemetria_detallada(&estado);
                break;

            case 4: {
                printf("\n--- SIMULACION DE MANIOBRA DE PROPULSION LATERAL ---\n");
                double a_aux = leer_double_positivo(" Ingrese aceleracion lateral constante a_y [m/s^2] (ej. 0.50): ");
                double dt_aux = leer_double_positivo(" Ingrese duracion del encendido Delta t [s] (ej. 10.0): ");

                ejecutar_pulso_lateral(&maniobra, a_aux, dt_aux);
                hubo_maniobra_actual = 1;
                mostrar_reporte_maniobra(&estado, &maniobra);
                break;
            }

            case 5:
                if (guardar_en_historial(historial, &cant_historial, &estado, &maniobra, hubo_maniobra_actual)) {
                    printf("\n[OK]: Ejecucion registrada con exito en el historial (ID #%d).\n", cant_historial);
                }
                break;

            case 6:
                mostrar_reporte_final_historial(historial, cant_historial);
                break;

            case 7:
                printf("\nFinalizando simulador Artemis LEO. ¡Exitos en el coloquio!\n");
                break;
        }

    } while (opcion != 7);

    return 0;
}
