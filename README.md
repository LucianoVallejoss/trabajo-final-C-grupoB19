# Simulador de Misiones Artemis — Escenario 2: Órbita Terrestre Baja (LEO)

**Universidad Tecnológica Nacional - Facultad Regional Resistencia (UTN FRRe)**  
**Cátedra:** Algoritmos y Estructuras de Datos — Ingeniería en Sistemas de Información  
**Trabajo Práctico Integrador Final (Lenguaje C)**

---

## 1. Integrantes y Comisión

| Apellido y Nombre | Comisión | Rol en el Proyecto |
| :--- | :--- | :--- |
| *(Completar Integrante 1)* |1.2 | Dinámica Física Orbital y MCU (`artemis.h/c`) |
| *Gesto, Emiliano Joaquín* |1.2 | Maniobras de Propulsión e Historial (`artemis.h/c`) |
| *Miño, Juan Antonio* |1.2 | Módulo de Entrada Segura y Validaciones (`validaciones.h/c`) |
| *Melis Asoya, Álvaro Joel* |1.2 | Menú Principal, Integración, Makefile y Documentación (`main.c`) |

---

## 2. Descripción del Escenario Asignado y Reglas de Simulación

El proyecto modela la **Situación-Problema 2: Inserción y Estabilidad en Órbita Terrestre Baja - LEO (MCU y Gravitación)**. Tras el ascenso, la nave Orion es inyectada en una órbita circular de estacionamiento a una altitud nominal de $h = 192,0\text{ km}$ con una masa total $m_{\text{orion}} = 33.000,0\text{ kg}$.

### Modelos Físicos Implementados
* **Rapidez Orbital ($v$):** Se demuestra analíticamente y se calcula igualando la fuerza de atracción gravitatoria con la fuerza centrípeta ($F_g = F_c \implies v = \sqrt{\frac{G \cdot M_T}{r}}$).
* **Período Orbital ($T$):** Tiempo necesario para completar una revolución alrededor de la Tierra ($T = \frac{2\pi r}{v}$).
* **Aceleración Centrípeta ($a_c$):** Experimentada por la tripulación en órbita ($a_c = \frac{v^2}{r}$).
* **Perturbación por Propulsor Auxiliar Lateral:** Simulación de un encendido perpendicular a la velocidad orbital durante un intervalo $\Delta t$, calculando la velocidad transversal adquirida ($v_y = a_y \cdot \Delta t$) y el desplazamiento lateral instantáneo ($\Delta y = \frac{1}{2} a_y \Delta t^2$).

### Funcionalidades del Sistema
1. **Demostración Teórica:** Presenta en consola el desarrollo algebraico de la igualdad entre fuerza gravitatoria y centrípeta.
2. **Modificación de Parámetros:** Permite ingresar valores de altitud y masa para recalcular la órbita y verificar la estabilidad frente al límite atmosférico ($160\text{ km}$).
3. **Telemetría Detallada:** Muestra una tabla formateada con equivalencias en unidades del Sistema Internacional.
4. **Simulación de Maniobra Lateral:** Permite ensayar pulsos auxiliares y analiza la trayectoria resultante.
5. **Auditoría e Historial:** Permite registrar hasta 50 ejecuciones en memoria y emitir un reporte tabular consolidado.

---

## 3. Arquitectura y Modularización

El código fuente se encuentra estructurado en el directorio `src/` respetando la separación de responsabilidades:

* `src/main.c`: Punto de entrada del programa, bucle interactivo principal y coordinación entre módulos.
* `src/artemis.h`: Definición de constantes físicas (`#define`), estructuras de datos y prototipos públicos.
* `src/artemis.c`: Implementación de los cálculos físicos, cinemática de perturbaciones y gestión del historial mediante punteros.
* `src/validaciones.h` / `src/validaciones.c`: Funciones de captura segura de datos por teclado.
* `Makefile`: Script de automatización de compilación.

---

## 4. Instrucciones de Compilación y Ejecución

### Requisitos Previos
* Compilador `gcc` (con soporte para estándar C99).
* Utilidad `make` (Linux, macOS, WSL o MinGW en Windows).

### Compilación mediante Makefile (Recomendado)
Desde la raíz del repositorio, ejecutar:

```bash
make
