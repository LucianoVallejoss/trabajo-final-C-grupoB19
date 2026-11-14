#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes físicas del problema
#define G_CONST 6.67430e-11        // Constante gravitacional
#define M_TIERRA 5.972e24          // Masa terrestre (kg)
#define R_TIERRA 6371000.0         // Radio terrestre medio (m)
#define G_SUPERFICIE 9.80665       // Aceleracion de la gravedad estandar (m/s^2)
#define LIMITE_ATMOSFERA 160000.0  // m (160 km: limite inferior seguro LEO)

// Constantes de auditoria e historial
#define MAX_HISTORIAL 50           // Capacidad maxima de simulaciones almacenadas

// Representacion del estado de la nave en orbita LEO
typedef struct {
    double altitud_m;              // h (m) sobre la superficie
    double radio_total_m;          // r = R_TIERRA + h (m)
    double masa_nave_kg;           // m_orion (kg)
    double velocidad_orbital;      // v (m/s)
    double periodo_segundos;       // T (s)
    double aceleracion_centripeta; // ac (m/s^2)
    int es_orbita_estable;         // 1 = Zona segura LEO, 0 = Riesgo de decaimiento
} EstadoOrbital;

// Representacion de la maniobra con propulsor auxiliar lateral
typedef struct {
    double a_y;                    // Aceleracion lateral constante (m/s^2)
    double delta_t;                // Duracion del pulso de encendido (s)
    double v_y;                    // Velocidad lateral adquirida (m/s)
    double delta_y;                // Desplazamiento transversal / desviacion (m)
} ManiobraLateral;

// Registro individual para el historial de auditoria
typedef struct {
    int id_simulacion;             // Numero correlativo de ejecucion (1 a 50)
    EstadoOrbital orbita;          // Estado orbital calculado en esa ejecucion
    ManiobraLateral maniobra;      // Datos del pulso lateral de esa ejecucion
    int hubo_maniobra;             // Bandera logica: 1 = se aplico pulso, 0 = solo orbita
} RegistroMision;

// Funciones
int verificar_estabilidad_orbital(const EstadoOrbital *estado);
void inicializar_estado_base(EstadoOrbital *estado);
void recalcular_dinamica_orbital(EstadoOrbital *estado);
void imprimir_demostracion_teorica(void);
void ejecutar_pulso_lateral(ManiobraLateral *maniobra, double a_y, double delta_t);
void mostrar_telemetria_detallada(const EstadoOrbital *estado);
void mostrar_reporte_maniobra(const EstadoOrbital *estado, const ManiobraLateral *maniobra);
int guardar_en_historial(RegistroMision historial[], int *cant_actual,
                         const EstadoOrbital *estado, const ManiobraLateral *maniobra,
                         int hubo_maniobra);
void mostrar_reporte_final_historial(const RegistroMision historial[], int cant_actual);

#endif
