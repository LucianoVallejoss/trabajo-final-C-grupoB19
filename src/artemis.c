#include <stdio.h>
#include <math.h>
#include "artemis.h"

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

    // 1. Radio orbital total: r = RT + h
    estado->radio_total_m = R_TIERRA + estado->altitud_m;

    // 2. Velocidad orbital para MCU: v = sqrt(G * MT / r)
    estado->velocidad_orbital = sqrt((G_CONST * M_TIERRA) / estado->radio_total_m);

    // 3. Periodo orbital: T = (2 * pi * r) / v
    estado->periodo_segundos = (2.0 * M_PI * estado->radio_total_m) / estado->velocidad_orbital;

    // 4. Aceleracion centripeta: ac = v^2 / r
    estado->aceleracion_centripeta = (estado->velocidad_orbital * estado->velocidad_orbital) / estado->radio_total_m;

    // 5. Verificacion automatica de zona segura LEO
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
    
    // 1. Almacenar parametros de entrada en la estructura apuntada
    maniobra->a_y = a_y;
    maniobra->delta_t = delta_t;

    // 2. Velocidad lateral adquirida: vy = a * dt
    maniobra->v_y = maniobra->a_y * maniobra->delta_t;

    // 3. Desplazamiento transversal instantaneo: dy = (1/2) * a * dt^2
    maniobra->delta_y = 0.5 * maniobra->a_y * (maniobra->delta_t * maniobra->delta_t);
}
