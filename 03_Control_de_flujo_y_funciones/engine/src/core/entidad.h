// [CAP.3] entidad.h - Representacion basica de una entidad del juego
#pragma once
#include "../math/vector2.h" // [CAP.3]

// [CAP.3] Estados posibles de una entidad. Usar un enum en lugar de
// [CAP.3] numeros sueltos (0, 1, 2...) hace el codigo autoexplicativo
// [CAP.3] y evita "numeros magicos" dispersos por el motor.
typedef enum {
    ESTADO_IDLE,     // [CAP.3] La entidad existe pero no se mueve
    ESTADO_MOVIENDO,  // [CAP.3] La entidad se desplaza segun su velocidad
    ESTADO_MUERTO      // [CAP.3] La entidad ya no se actualiza ni se dibuja
} EstadoEntidad;

typedef struct {
    int id;                  // [CAP.3]
    Vector2 posicion;        // [CAP.3]
    Vector2 velocidad;       // [CAP.3]
    EstadoEntidad estado;    // [CAP.3]
} Entidad;

// [CAP.3] Declaraciones (prototipos): lo que otros ficheros pueden usar.
Entidad entidad_crear(int id, Vector2 posicion, Vector2 velocidad);
void entidad_actualizar(Entidad* entidad, float deltaTiempo);
const char* entidad_nombre_estado(EstadoEntidad estado);
