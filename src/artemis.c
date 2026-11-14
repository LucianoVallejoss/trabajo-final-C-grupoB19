#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "artemis.h"
#include "validaciones.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Asigna las condiciones iniciales del problema
void inicializar_estado_base(EstadoOrbital *estado) {
    if (!estado) return;
    estado->altitud_m = 192000.0;     // h = 192 km
    estado->masa_nave_kg = 33000.0;    // m = 33 ton
    recalcular_dinamica_orbital(estado);
}

// Resuelve la cinematica y dinamica orbital usando paso por referencia
void recalcular_dinamica_orbital(EstadoOrbital *estado) {
    if (!estado) return;

    estado->radio_total_m = R_TIERRA + estado->altitud_m;
    estado->velocidad_orbital = sqrt((G_CONST * M_TIERRA) / estado->radio_total_m);
    estado->periodo_segundos = (2.0 * M_PI * estado->radio_total_m) / estado->velocidad_orbital;
    estado->aceleracion_centripeta = (estado->velocidad_orbital * estado->velocidad_orbital) / estado->radio_total_m;
    estado->es_orbita_estable = verificar_estabilidad_orbital(estado);
}

// Evalua si la altitud evita el frenado por rozamiento atmosferico (> 160 km)
int verificar_estabilidad_orbital(const EstadoOrbital *estado) {
    if (!estado) return 0;
    return (estado->altitud_m >= LIMITE_ATMOSFERA) ? 1 : 0;
}

// Consigna a 
void imprimir_demostracion_teorica(void) {
    printf("\n----------------------------------------------------------------------\n");
    printf(" DEMOSTRACION ANALITICA: LA GRAVEDAD COMO FUERZA CENTRIPETA\n");
    printf("----------------------------------------------------------------------\n");
    printf("1. Fuerza gravitatoria universal de atraccion hacia el centro terrestre:\n");
    printf("      Fg = G * (M_T * m_orion) / r^2\n\n");
    printf("2. Fuerza centripeta requerida para mantener la trayectoria circular (MCU):\n");
    printf("      Fc = m_orion * ac = m_orion * (v^2 / r)\n\n");
    printf("3. Al ser la gravedad la unica fuerza radial neta actuante (Fg = Fc):\n");
    printf("      G * (M_T * m_orion) / r^2 = m_orion * (v^2 / r)\n\n");
    printf("4. Despeje formal simplificando m_orion y un factor de radio r:\n");
    printf("      (G * M_T) / r = v^2  ==>  v = sqrt((G * M_T) / r)\n\n");
    printf("Conclusion fisica:\n");
    printf("- La rapidez orbital requerida NO depende de la masa de la nave.\n");
    printf("- Depende unicamente de la masa del cuerpo central (Tierra) y de la distancia r.\n");
    printf("----------------------------------------------------------------------\n");
}

// Calcula la cinematica del pulso perpendicular por referencia
void ejecutar_pulso_lateral(ManiobraLateral *maniobra, double a_y, double delta_t) {
    if (!maniobra) return;
    maniobra->a_y = a_y;
    maniobra->delta_t = delta_t;
    maniobra->v_y = maniobra->a_y * maniobra->delta_t;
    maniobra->delta_y = 0.5 * maniobra->a_y * (maniobra->delta_t * maniobra->delta_t);
}

// Muestra en tabla todos los parametros orbitales
void mostrar_telemetria_detallada(const EstadoOrbital *estado) {
    if (!estado) return;

    double altitud_km = estado->altitud_m / 1000.0;
    double radio_km = estado->radio_total_m / 1000.0;
    double velocidad_kmh = estado->velocidad_orbital * 3.6;
    double periodo_min = estado->periodo_segundos / 60.0;
    double fuerza_centripeta = estado->masa_nave_kg * estado->aceleracion_centripeta;
    double factor_g = estado->aceleracion_centripeta / G_SUPERFICIE;

    printf("\n+-------------------------------------------------------------------------+\n");
    printf("|                  TELEMETRIA ORBITAL DETALLADA - NAVE ORION              |\n");
    printf("+-----------------------------------+--------------------+----------------+\n");
    printf("| PARAMETRO FISICO                  | VALOR PRINCIPAL    | EQUIVALENCIA   |\n");
    printf("+-----------------------------------+--------------------+----------------+\n");
    printf("| Masa de la nave (m_orion)         | %15.2f kg | %10.2f ton |\n", estado->masa_nave_kg, estado->masa_nave_kg / 1000.0);
    printf("| Altitud sobre superficie (h)      | %15.2f m  | %10.2f km  |\n", estado->altitud_m, altitud_km);
    printf("| Radio orbital total (r = RT + h)  | %15.2f m  | %10.2f km  |\n", estado->radio_total_m, radio_km);
    printf("| Velocidad orbital MCU (v)         | %15.2f m/s| %10.2f km/h|\n", estado->velocidad_orbital, velocidad_kmh);
    printf("| Periodo orbital completo (T)      | %15.2f s  | %10.2f min |\n", estado->periodo_segundos, periodo_min);
    printf("| Aceleracion centripeta (ac)       | %15.4f m/s2| %10.4f g   |\n", estado->aceleracion_centripeta, factor_g);
    printf("| Fuerza gravitatoria / centripeta  | %15.2f N  | %10.2f kN  |\n", fuerza_centripeta, fuerza_centripeta / 1000.0);
    printf("+-----------------------------------+--------------------+----------------+\n");
}

// Muestra el reporte tabular del pulso lateral y describe la trayectoria resultante
void mostrar_reporte_maniobra(const EstadoOrbital *estado, const ManiobraLateral *maniobra) {
    if (!estado || !maniobra) return;

    double v_total = sqrt((estado->velocidad_orbital * estado->velocidad_orbital) +
                          (maniobra->v_y * maniobra->v_y));

    printf("\n+-------------------------------------------------------------------------+\n");
    printf("|               REPORTE DE MANIOBRA DE PROPULSION LATERAL                 |\n");
    printf("+----------------------------------------+-------------------+------------+\n");
    printf("| PARAMETRO DE PERTURBACION              | VALOR CALCULADO   | UNIDAD     |\n");
    printf("+----------------------------------------+-------------------+------------+\n");
    printf("| Aceleracion lateral aplicada (a_y)     | %17.2f | m/s^2      |\n", maniobra->a_y);
    printf("| Duracion del pulso auxiliar (Delta t)  | %17.2f | s          |\n", maniobra->delta_t);
    printf("| Velocidad lateral adquirida (v_y)      | %17.2f | m/s        |\n", maniobra->v_y);
    printf("| Desviacion lateral instantanea (Dy)    | %17.2f | m          |\n", maniobra->delta_y);
    printf("| Nueva rapidez orbital resultante       | %17.2f | m/s        |\n", v_total);
    printf("+----------------------------------------+-------------------+------------+\n");
    printf("| ANALISIS FISICO DE TRAYECTORIA RESULTANTE (Consigna d):                 |\n");
    printf("| - Durante el pulso (%.1f s): La nave superpone su MCU tangencial con un |\n", maniobra->delta_t);
    printf("|   MRUV transversal, describiendo un ARCO PARABOLICO desviandose %.2f m.|\n", maniobra->delta_y);
    printf("| - Post-apagado: Por inercia (1ra Ley de Newton), mantiene la componente |\n");
    printf("|   lateral v_y = %.2f m/s, rotando levemente su plano de inclinacion.    |\n", maniobra->v_y);
    printf("+-------------------------------------------------------------------------+\n");
}

// Almacena una ejecucion en el arreglo de historial (maximo 50)
int guardar_en_historial(RegistroMision historial[], int *cant_actual,
                         const EstadoOrbital *estado, const ManiobraLateral *maniobra,
                         int hubo_maniobra) {
    if (!historial || !cant_actual || !estado) return 0;

    if (*cant_actual >= MAX_HISTORIAL) {
        printf("\n[AVISO]: Historial lleno (%d/%d). No se pueden registrar mas simulaciones.\n",
               *cant_actual, MAX_HISTORIAL);
        return 0;
    }

    int i = *cant_actual;
    historial[i].id_simulacion = i + 1;
    historial[i].orbita = *estado;
    historial[i].hubo_maniobra = hubo_maniobra;

    if (hubo_maniobra && maniobra != NULL) {
        historial[i].maniobra = *maniobra;
    } else {
        historial[i].maniobra.a_y = 0.0;
        historial[i].maniobra.delta_t = 0.0;
        historial[i].maniobra.v_y = 0.0;
        historial[i].maniobra.delta_y = 0.0;
    }

    (*cant_actual)++;
    return 1;
}

// Emite reporte final de auditoria
void mostrar_reporte_final_historial(const RegistroMision historial[], int cant_actual) {
    printf("\n=========================================================================================\n");
    printf("                    REPORTE FINAL DE AUDITORIA - HISTORIAL DE SIMULACIONES               \n");
    printf("=========================================================================================\n");

    if (!historial || cant_actual <= 0) {
        printf("  No se registraron simulaciones en el historial durante esta sesion.\n");
        printf("=========================================================================================\n");
        return;
    }

    printf("+----+-------------+-------------+-------------+-------------+------------+-------------+\n");
    printf("| ID | ALTITUD (m) | MASA (kg)   | VEL. (m/s)  | PERIODO (s) | MANIOBRA   | DESVIO (m)  |\n");
    printf("+----+-------------+-------------+-------------+-------------+------------+-------------+\n");

    int maniobras_realizadas = 0;

    for (int i = 0; i < cant_actual; i++) {
        if (historial[i].hubo_maniobra) {
            maniobras_realizadas++;
            printf("| %2d | %11.1f | %11.1f | %11.2f | %11.1f |     SI     | %11.2f |\n",
                   historial[i].id_simulacion,
                   historial[i].orbita.altitud_m,
                   historial[i].orbita.masa_nave_kg,
                   historial[i].orbita.velocidad_orbital,
                   historial[i].orbita.periodo_segundos,
                   historial[i].maniobra.delta_y);
        } else {
            printf("| %2d | %11.1f | %11.1f | %11.2f | %11.1f |     NO     |        0.00 |\n",
                   historial[i].id_simulacion,
                   historial[i].orbita.altitud_m,
                   historial[i].orbita.masa_nave_kg,
                   historial[i].orbita.velocidad_orbital,
                   historial[i].orbita.periodo_segundos);
        }
    }

    printf("+----+-------------+-------------+-------------+-------------+------------+-------------+\n");
    printf("  Total de ejecuciones auditadas: %d/%d | Con maniobra lateral: %d\n",
           cant_actual, MAX_HISTORIAL, maniobras_realizadas);
    printf("=========================================================================================\n");
}



// MODO DE JUEGO INTERACTIVO: CAMPANA DE SIMULACION POR TURNOS (5 ORBITAS)

void iniciar_campana_turnos(RegistroMision historial[], int *cant_historial) {
    EstadoOrbital nave;
    ManiobraLateral maniobra;
    inicializar_estado_base(&nave);

    double combustible_kg = 500.0;
    int integridad_casco = 100;
    int puntaje = 0;
    int mision_fallida = 0;
    int mision_abortada = 0;
    const int TOTAL_TURNOS = 5;

    srand((unsigned int)time(NULL));

    printf("\n=========================================================================\n");
    printf("       MODO MISION ARTEMIS: SUPERVIVENCIA EN ORBITA LEO (5 TURNOS)         \n");
    printf("=========================================================================\n");
    printf(" OBJETIVO DE MISION:\n");
    printf(" - Completar 5 orbitas manteniendo la nave en zona segura (> 160.0 km),\n");
    printf("   conservando la integridad del casco (100%%) y administrando 500.0 kg\n");
    printf("   de combustible.\n");
    printf(" - Evalua los sensores en cada orbita y elegi la maniobra adecuada.\n");
    printf("=========================================================================\n");

    int secuencia_eventos[5] = {1, 2, 3, 1, 2};
    for (int i = 1; i < TOTAL_TURNOS; i++) {
        int j = 1 + (rand() % (TOTAL_TURNOS - 1));
        int temp = secuencia_eventos[i];
        secuencia_eventos[i] = secuencia_eventos[j];
        secuencia_eventos[j] = temp;
    }

    for (int turno = 1; turno <= TOTAL_TURNOS; turno++) {
        nave.altitud_m -= 4000.0;
        recalcular_dinamica_orbital(&nave);

        printf("\n-------------------------------------------------------------------------\n");
        printf(" ORBITA %d de %d\n", turno, TOTAL_TURNOS);
        printf(" TELEMETRIA  -> Altitud: %.1f km (Limite critico: 160.0 km)\n", nave.altitud_m / 1000.0);
        printf(" RECURSOS    -> Combustible: %.1f kg | Integridad Casco: %d%%\n", combustible_kg, integridad_casco);
        printf("-------------------------------------------------------------------------\n");

        if (!nave.es_orbita_estable) {
            printf("\n[DERROTA]: La altitud cayo por debajo de 160.0 km. Reingreso atmosferico.\n");
            mision_fallida = 1;
            break;
        }

        int tipo_evento = secuencia_eventos[turno - 1];
        double desvio_objetivo = 0.0;

        if (tipo_evento == 1) {
            desvio_objetivo = 25.0 + (turno * 5.0);
            printf(" [SENSOR DE PROXIMIDAD]: Basura espacial en trayectoria de colision!\n");
            printf("  -> Desviacion lateral minima requerida para evadir: %.1f metros.\n", desvio_objetivo);
        } else if (tipo_evento == 2) {
            nave.altitud_m -= 14000.0;
            recalcular_dinamica_orbital(&nave);
            printf(" [ALERTA SOLAR]: Tormenta geomagnetica provoca decaimiento de 14.0 km!\n");
            printf("  -> Altitud actual tras la perturbacion: %.1f km.\n", nave.altitud_m / 1000.0);
            if (!nave.es_orbita_estable) {
                printf("\n[DERROTA]: Caiste debajo de 160.0 km tras la tormenta solar.\n");
                mision_fallida = 1;
                break;
            }
        } else {
            printf(" [RADAR ORBITAL]: Sector despejado. No se detectan amenazas ni anomalias.\n");
        }

        printf("\n ACCIONES DE MANDO:\n");
        printf("  1. Ejecutar pulso lateral RCS (Desvio: Dy = 0.5 * a_y * dt^2)\n");
        printf("  2. Encender motor principal (+15.0 km de altitud | Costo: 75.0 kg comb.)\n");
        printf("  3. Mantener orbita pasiva (Costo: 0.0 kg comb.)\n");
        printf("  4. Abortar mision y volver al menu principal\n");

        int accion = leer_entero_rango(" Seleccione una opcion (1-4): ", 1, 4);

        if (accion == 4) {
            printf("\n[MISION ABORTADA]: Retornando al centro de control principal...\n");
            mision_abortada = 1;
            break;
        }

        if (accion == 1) {
            printf("\n --- PARAMETROS DEL PROPULSOR LATERAL ---\n");
            printf(" Formulas: Dy = 0.5 * a_y * dt^2  |  Consumo = a_y * dt * 8.0 kg\n");

            double a_y = leer_double_rango("  -> Aceleracion lateral a_y [m/s^2] (0.5 a 20.0): ", 0.5, 20.0);
            double dt = leer_double_rango("  -> Duracion del pulso dt [s] (1.0 a 30.0): ", 1.0, 30.0);

            double consumo = (a_y * dt) * 8.0;
            if (consumo > combustible_kg) {
                printf("\n[DERROTA]: Combustible insuficiente para completar el encendido (requiere %.1f kg, disponible %.1f kg).\n",
                       consumo, combustible_kg);
                combustible_kg = 0.0;
                mision_fallida = 1;
                break;
            }

            combustible_kg -= consumo;
            ejecutar_pulso_lateral(&maniobra, a_y, dt);
            guardar_en_historial(historial, cant_historial, &nave, &maniobra, 1);

            printf("\n [TELEMETRIA PULSO]: vy = %.2f m/s | Desvio Dy = %.2f m | Combustible usado = %.1f kg\n",
                   maniobra.v_y, maniobra.delta_y, consumo);

            if (tipo_evento == 1) {
                if (maniobra.delta_y >= desvio_objetivo) {
                    printf(" [EXITO]: Evasion completada (%.2f m >= %.1f m). +200 puntos.\n",
                           maniobra.delta_y, desvio_objetivo);
                    puntaje += 200;
                } else {
                    integridad_casco -= 50;
                    printf(" [IMPACTO PARCIAL]: Desvio insuficiente (%.2f m < %.1f m). Casco -50%%.\n",
                           maniobra.delta_y, desvio_objetivo);
                    if (integridad_casco <= 0) {
                        printf("\n[DERROTA]: Integridad del casco en 0%%. Nave perdida.\n");
                        mision_fallida = 1;
                        break;
                    }
                }
            } else {
                printf(" [AVISO]: Pulso lateral innecesario en este sector (+50 puntos).\n");
                puntaje += 50;
            }

        } else if (accion == 2) {
            if (tipo_evento == 1) {
                printf("\n[DERROTA]: El cambio de altitud no evito la colision lateral con la basura espacial!\n");
                integridad_casco = 0;
                mision_fallida = 1;
                break;
            }
            if (combustible_kg < 75.0) {
                printf("\n[AVISO]: Combustible insuficiente para el motor principal (disponible %.1f kg, requiere 75.0 kg).\n", combustible_kg);
            } else {
                combustible_kg -= 75.0;
                nave.altitud_m += 15000.0;
                recalcular_dinamica_orbital(&nave);
                guardar_en_historial(historial, cant_historial, &nave, NULL, 0);
                printf("\n [EXITO]: Altitud elevada a %.1f km (Nueva vel: %.2f m/s). +200 puntos.\n",
                       nave.altitud_m / 1000.0, nave.velocidad_orbital);
                puntaje += 200;
            }

        } else {
            if (tipo_evento == 1) {
                printf("\n[DERROTA]: Impacto directo contra basura espacial por falta de maniobra!\n");
                integridad_casco = 0;
                mision_fallida = 1;
                break;
            }
            printf("\n [EXITO]: Orbita mantenida sin gasto de propelente. +150 puntos.\n");
            puntaje += 150;
        }
    }

    if (mision_abortada) {
        return;
    }

    if (!mision_fallida) {
        puntaje += (int)(combustible_kg * 0.5) + (integridad_casco * 2);
    }

    printf("\n=========================================================================\n");
    printf("               BOLETIN FINAL DE DESEMPENO - MISION ARTEMIS               \n");
    printf("=========================================================================\n");
    printf(" Estado final           : %s\n", mision_fallida ? "MISION FALLIDA" : "MISION CUMPLIDA (5 Orbitas completadas)");
    printf(" Altitud final          : %.2f km\n", nave.altitud_m / 1000.0);
    printf(" Combustible sobrante   : %.1f kg de 500.0 kg\n", combustible_kg);
    printf(" Integridad del casco   : %d%%\n", integridad_casco < 0 ? 0 : integridad_casco);
    printf(" Puntaje total          : %d pts\n", puntaje);
    printf(" Calificacion           : %s\n",
           mision_fallida ? "Cadete (Reintentar simulacion)" :
           (puntaje >= 900 ? "Comandante Artemis (Excelente)" : "Piloto Orbital (Aprobado)"));
    printf("=========================================================================\n");
}