#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes físicas del problema
#define G_CONST 6.67430e-11        // Constante gravitacional
#define M_TIERRA 5.972e24          // Masa terrestre (kg)
#define R_TIERRA 6371000.0         // Radio terrestre medio (m)
#define G_SUPERFICIE 9.80665       // Aceleracion de la gravedad estandar (m/s^2)

// Representacion del estado de la nave en orbita LEO
typedef struct {
    double altitud_m;              // h (m) sobre la superficie
    double radio_total_m;          // r = R_TIERRA + h (m)
    double masa_nave_kg;           // m_orion (kg)
    double velocidad_orbital;      // v (m/s)
    double periodo_segundos;       // T (s)
    double aceleracion_centripeta; // ac (m/s^2)
} EstadoOrbital;

// Funciones 
void inicializar_estado_base(EstadoOrbital *estado);
void recalcular_dinamica_orbital(EstadoOrbital *estado);
void imprimir_demostracion_teorica(void);

#endif